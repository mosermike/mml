/**
 * @author Mike Moser
 * 
 * @file: file.cpp
 * Enthält verschiedene Funktionen für Dateien
 * 
*/
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <sys/stat.h>	// struct stat
#include <dirent.h>
#include <bits/local_lim.h>	// Limits für Hostname und Loginname
#include <string.h>
#include <functional>	// std::function
#include <sys/ioctl.h>	// winsize
#include <iomanip>      // std::setfill, std::setw
#include <thread>
#include <limits.h>
#include <filesystem>

#include "mml.hpp"
#include "mml/file.hpp"

mml::thread::Thread mml_thread;
mml::string mml_actual_file = "";
bool mml_progressing = false;


void mml::file::add_twofiles( std::string filepath_input1 , std::string filepath_input2 , std::string filepath_output){
	
	std::string value;
	
	//Öffne die Dateien:
	std::ifstream input1(filepath_input1);
	std::ifstream input2(filepath_input2);
	std::ofstream output(filepath_output);
	
	// Checks whether both files are opened
    if ( !input1 || !input2 ){
        throw std::runtime_error("[add_twofiles] file not found");
    }
	
	// Read the first data
	while (! input1.eof()) {
        std::getline(input1, value );	// Get content of the file
		output << value;				// Write the line into the output
		output << "\n";					// Write new line
    }
    
	// Read the second data
	while (! input2.eof()) {
        std::getline(input2, value );	// Get content of the file
		output << value;				// Write the line into the output
		output << "\n";					// Write new line
    }
    
    return;
}

bool mml::file::byteCopy(const std::string& src, const std::string& dest, std::size_t blockSize, bool progress) {
	if(!mml::Unix::exist(src))
		throw std::runtime_error("[byteCopy] Source file" + src +  "does not exist!");
	
	std::ifstream ifile(src, std::ifstream::binary);
	FILE* ofile = fopen(dest.c_str(), "wb");

	std::size_t fileSize = mml::file::size(src);
	char* buffer         = new char[blockSize];

	mml::Timer	time;
	mml_progressing		= true;
	bool		gigabit				= false;
	bool		megabit				= false;
	
	if(fileSize >= _1G)
		gigabit = true;
	else if(fileSize > _1M)
		megabit = true;
	

	std::thread first([&](){
		// ************************************************
		// *		Prints out the PROGRESS				  *
		// ************************************************
		if(progress) {
			while(mml_progressing) {
				struct stat dst;
				stat(dest.c_str(), &dst);
				double actual_size = static_cast<double>(dst.st_size);

				if(gigabit)
					printf("\rPercent: %6.2f%%   Time: %7.3fs  Speed: %7.3f MBit/s  Size: %6.2f GBit", 100 * (actual_size / fileSize), time.getS(), actual_size /_1M/time.getS(), (double) fileSize /_1G);
				else if (megabit)
					printf("\rPercent: %6.2f%%   Time: %7.3fs  Speed: %7.3f MBit/s  Size: %6.2f MBit", 100 * (actual_size / fileSize), time.getS(), actual_size /_1M/time.getS(), (double) fileSize /_1M);
				else
					printf("\rProzent: %6.2f%%   Time: %7.3fs  Speed: %7.3f MBit/s  Size: %6.2f KBit", 100 * (actual_size / fileSize), time.getS(), actual_size /_1M/time.getS(), (double) fileSize /_1K);
				std::cout.flush();
			}
		}
	});

	// ************************************************
	// *		COPYING FILE TO DESTINATION			  *
	// ************************************************
	while(!ifile.eof()) {
		
		ifile.read(buffer, blockSize);
		
		std::size_t num = ifile.gcount();
		
		fwrite(buffer, 1, num, ofile);
		
		fsync(fileno(ofile));

	}

	mml_progressing = false; // Stop the output of the progress
	first.join();
	
	// ************************************************
	// *			PRINT OUT FINAL PROGRESS		  *
	// ************************************************
	if(progress) {
		
		if(gigabit)
			printf("\rPercent: 100.00%%   Time: %7.3fs  Speed: %7.3f MBit/s  Size: %6.2f GBit", time.stop()/1000, (double) (fileSize/_1M)/time.stop()*1000 ,(double) fileSize/_1G);
		else if(megabit)
			printf("\rPercent: 100.00%%   Time: %7.3fs  Speed: %7.3f MBit/s  Size: %6.2f MBit", time.stop()/1000, (double) (fileSize/_1M)/time.stop()*1000,  (double) fileSize/_1M);
		else
			printf("\rPercent: 100.00%%   Time: %7.3fs  Speed: %7.3f MBit/s  Size: %6.2f KBit", time.stop()/1000, (double) (fileSize/_1M /time.stop()),  (double) fileSize/_1K);
		std::cout.flush();
	}
        
    delete[] buffer;
    
    // Close the final data
    fclose(ofile);
	
    // if in linux OS, set date of the destination file as the source file
#ifdef __linux__
	return mml::Unix::set_date(src, dest, false);
#else
	return 0;
#endif
	
    //return ifile.tellg();
}

// Überprüfe, ob zwei Dateien identisch sind

bool mml::file::equal(std::string src, std::string dst){
		
	std::string sha_src = mml::random_str();
	std::string sha_dst = mml::random_str();
	
	std::string s_command = "sha256sum " + src + " >> " + sha_src;
	std::string d_command = "sha256sum " + dst + " >> " + sha_dst;
		
	std::string src_sha256;
	std::string dst_sha256;
		
	int16_t sys = 0;
		
	sys = system(s_command.c_str());
	sys = system(d_command.c_str());
	
	std::ifstream input_src (sha_src);
	std::ifstream input_dst (sha_dst);
		
	std::getline(input_src,src_sha256);
	std::getline(input_dst,dst_sha256);
		
	uint32_t position_src = src_sha256.find("  ");
	uint32_t position_dst = dst_sha256.find("  ");

	src_sha256 = src_sha256.substr(0,position_src);
	dst_sha256 = dst_sha256.substr(0,position_dst);
	sys = 0;
		
	return src_sha256 == dst_sha256 && sys == 0 ? true : false;
	
}

int32_t mml::file::filetype(std::string filepath){
	struct stat sb;
	
	if (stat(filepath.c_str(), &sb) == -1) {
		throw std::runtime_error("[stat] No such file or directory (" + filepath + ")");
		exit(EXIT_FAILURE);
	}

    switch (sb.st_mode & S_IFMT) {
		case S_IFBLK:	return S_DEVICE;		// device or partition
		case S_IFCHR:	return S_CHARDEV;		// mouse, serial connected device
		case S_IFDIR:	return S_DIR;			// directory
		case S_IFIFO:	return S_FIFO;
		case S_IFLNK:	return S_SYMLNK;		// symbolic link
		case S_IFREG:	return S_FILE;			// normall file
		case S_IFSOCK:	return S_SOCK;  		// Socket
		default:		throw std::runtime_error("[stat] Type of " + filepath + " unknown."); // unknown type
    }
}

std::size_t mml::file::num_lines(std::string path) {
	
	int num = 0;
	std::ifstream input(path.c_str());
	
	while(!input.eof()) {
		input.ignore( INT_MAX, '\n' );
		num++;
	}
	
	return num;
}


int mml::file::copy(mml::string src, mml::string dst, std::string name_in, std::string name_ex, size_t blocksize, bool verbose, bool verbose_debug, bool all, bool recursive, bool force, bool progress, bool falsewrite){

	mml::string				actual_src_dir		= "";	// aktueller Pfad
	mml::string				actual_dst_dir		= "";   // aktueller Zielpfad
	mml::string				actual_dst_check	= "";
	mml::Unix::User			user;
	uint32_t				filesize_correct	= 0;	// Korrektur für Ausgabe Ok
	std::size_t				fileSize			= 0;	// Dateigröße
	int						status				= 0;	// Drei Punkte anzeigen bei Überspringen
	std::size_t				temp_size			= 0;	// For temporary positions
	mml::string				temp_string			= "";	// Temporary string
	uint32_t				num_of_files		= 0; 	// how many files are to be copied
	uint32_t				copied_files		= 0; 	// how many files are already copied
	uint32_t				copied_files_print	= 0; 	// file number for the print
	if(verbose_debug)
		std::cout << "[copy] Start of function 'copy'!" << std::endl;
	/*
	 * ***********************************
	 * * 		COPYING SINGLE FILE      *
	 * ***********************************
	 *	Determine destination directory
	 *					|
	 *					v
	 *	Check whether file exists and ask how to proceed
	 *					|
	 *					v
	 *	Determine permission to write
	 *					|
	 *					v
	 *	Create folders to the point needed
	 *					|
	 *					v
	 *	Copy file
	 *					|
	 *					v
	 *	Print out information and compute console width
	*/
	if(name_in == "" && name_ex == ""){
		actual_src_dir = src;
		actual_dst_dir = dst;

		// Checking the file sizes and compares it if the file already exists, it asks how to proceed
        if(mml::file::filetype(actual_src_dir.getValue()) == S_FILE){
        	if(actual_dst_dir[-1] == '/'){
        		// Search last part from source to determine the name of the goal path
        		temp_size = actual_src_dir.find_back("/",0,0);
        		if(temp_size == std::string::npos)
        			dst += src;
        		else {
        			dst += src.substr(temp_size+1);
        		}
        		actual_dst_dir = dst;
        	}
        	else if(mml::Unix::exist(dst.str()) && mml::file::filetype(dst.str()) == S_DIR) {
        		throw std::logic_error("[copy] Destination file is a directory");
        	}

			fileSize = mml::file::size(actual_src_dir.str());
			if(mml::Unix::exist(actual_dst_dir.str()) && !force){	// If the destination exists and the force mode isn't active, stops and first ask the user
				if(fileSize > _1GB)
					std::cout << "| Size of source file: " << mml::file::size(actual_src_dir.str())/_1GB << " GB and size of destionation file: " << mml::file::size(actual_dst_dir.str())/_1GB << " GB!" << std::endl;
				else if(fileSize > _1MB)
					std::cout << "| Size of source file: " << mml::file::size(actual_src_dir.str())/_1MB << " MB and size of destionation file: " << mml::file::size(actual_dst_dir.str())/_1MB << " MB!" << std::endl;
				else
					std::cout << "| Size of source file: " << mml::file::size(actual_src_dir.str())/_1KB << " KB and size of destionation file: " << mml::file::size(actual_dst_dir.str())/_1KB << " KB!" << std::endl;
				
				std::cout << actual_dst_dir << " exists. Overwrite? [y|n|A] ";
				char input = std::cin.get();
				
				if((int) input != 10)	std::cin.ignore(256,10);	// falls kein Enter(10) am Anfang eingeben wurde, ignoriere alle nachfolgenden Zeichen bis zum Enter
				
				if(input == 'n'){
					return 1;
				}
			}
			
			/*
			 * **************************************
			 * *	Determine permission to write	*
			 * **************************************
			 */
			// Determine deepest directory which exists
			actual_dst_check = actual_dst_dir;
			if(!actual_dst_check.exist("/"))
				actual_dst_check = "./";
			else {
				temp_size = 0;
				do {
					temp_size = actual_dst_check.find_back("/",0,1);
					actual_dst_check = actual_dst_check.substr(0,temp_size);
				} while(temp_size < std::string::npos && (!mml::Unix::exist(actual_dst_check.str())));

			}

			// Checks whether the user has write permissions on the destination
			if(!mml::Unix::perm_to_write(actual_dst_check.str()))
				throw std::runtime_error("[copy] Copying to '" + actual_dst_check.str() + "' is not possible: Permission denied");


            // **************************************************
            // *	Create the directory to the point needed	*
            // **************************************************
			temp_size = dst.find_back("/",0,0);
			if(!mml::Unix::exist(dst.substr(0,temp_size).str()))
            	dst.substr(0,temp_size).mkdir_p();
			else if(mml::file::filetype(dst.substr(0,temp_size).str()) != S_DIR)
				throw std::runtime_error("[copy] Last to-be directory is not a directory!");

			if(verbose)	// verbose Ausgabe
				std::cout << src << " -> " << dst;

			fileSize = mml::file::size(src.str());

			mml::file::byteCopy(actual_src_dir.str(),actual_dst_dir.str(),blocksize,progress);			

 			// **********************************************************
 			// *	Determination of the width to print out [ ok ]		*
 			// **********************************************************
			if(verbose){	// verbose Ausgabe
				
				// Get information from the console
				struct winsize console;
				ioctl(STDOUT_FILENO, TIOCGWINSZ, &console);

				// Depending if progress is shown, the output_size is different
				std::size_t output_size = 0;
				if(!progress) {
					output_size =  dst.size() + src.size() - 17;
					std::cout << std::setw(console.ws_col - output_size) << "\e[34m\[\e[1;32m ok\e[0m\e[34m ]" << "\e[0m" << std::endl;
				}
				else {
					filesize_correct = -3; // Correction for the progress bar
					output_size =  73-22;
					std::cout << std::setw(console.ws_col - output_size + filesize_correct) << "\e[34m\[\e[1;32m ok\e[0m\e[34m ]" << "\e[0m" << std::endl;
				}
				std::cout.flush();
			}

			return 0;
        }
	}
	
	/* 
	 * ************************************
	 * * 		COPYING DIRECTORY	      *
	 * ************************************
	 *	Determine the files and directory structure to be copied
	 *					|
	 *					v
	 *	Determine permission to write
	 *					|
	 *					v
	 *	Create all directories
	 *					|
	 *					v
	 *	Copy files and ask if it already exists
	 *					|
	 *					v
	 *	Print out information and compute console width
	 */
	
	// When dst ends with / => add the last directory of the source
	if(dst[-1] == '/' && src[-1] != '/')
		dst = dst + src.substr(src.rfind('/')+1);

	// Add backslash to source and destionation if it does not end with it
	if(src[src.size()-1] != '/')
			src = src + "/";
	if(dst[dst.size()-1] != '/')
			dst = dst + "/";
	
	/*
	 * ******************************************************************
	 * *	Determine the files and directory structure to be copied	*
	 * ******************************************************************
	 */
	if(verbose_debug)
		std::cout << "[copy] Reading directory structure ..." << std::endl;
	
	// Save directories separately and additionally to save time when creating directories.
	std::vector<std::string> directories;
	std::vector<std::string> structure = src.ls(name_in, name_ex, directories, recursive, all); // list dir. tree
	
	num_of_files = structure.size() - directories.size(); // Number of files to be copied
	
	if(verbose_debug)
		std::cout << "[copy] Create the destination ..." << std::endl;

	// For debugging of the ls function
	//for(uint32_t i = 0; i < structure.size(); i++){
	//	std::cout << structure[i] << std::endl;		
	//}
	
		
	// Make the destination
	if(mml::Unix::exist(dst.str()) && mml::file::filetype(dst.str()) == S_FILE) {
	    throw std::logic_error("[copy] Destination exists as a file");
	}
	else
		dst.mkdir_p();
	
	if(verbose_debug)
		std::cout << "[copy] Check Permissions ..." << std::endl;
	/*
	 * **********************************
	 * *	Check permission to write	*
	 * **********************************
	 */
	// Determine deepest directory which exists
	actual_dst_check = dst;
	if(!actual_dst_check.exist("/"))
		actual_dst_check = "./";
	else {
		temp_size = 0;
		do {
			temp_size = actual_dst_check.find_back("/",0,1);
			actual_dst_check = actual_dst_check.substr(0,temp_size);
		} while(temp_size < std::string::npos && (!mml::Unix::exist(actual_dst_check.str())));

	}

	// Checks whether the user has write permissions on the destination
	if(!mml::Unix::perm_to_write(actual_dst_check.str()))
		throw std::runtime_error("[copy] Copying to '" + actual_dst_check.str() + "' is not possible: Permission denied");
	
	if(verbose_debug)
		std::cout << "[copy] Create directory structure ..." << std::endl;
	/*
	 * **********************************
	 * *	Create all the directories	*
	 * **********************************
	 */
	for(int32_t i = directories.size()-1; i >= 0; i--){
		
		temp_string = directories[i];
		
		actual_src_dir = temp_string.sub(0,-2);

		actual_dst_dir = actual_src_dir.replace(src.str(),dst.str()); 
		
		actual_dst_dir.mkdir_p();
		
	}

	if(verbose_debug) {
		std::cout << "[copy] Copy files ..." << std::endl;
	} 	
	/*
	 * ******************
	 * *	Copy files 	*
	 * ******************
	 */

	static bool				overwrite			= false;								// Zur Überprüfung, ob eine Datei schon vorhanden
	static bool				overwrite_anyway	= false;								// Zur Überprüfung, ob eine Datei schon vorhanden nach ask_anyway	
	bool					status_active		= false;
	uint32_t				actual_file			= 1;									// shows which file is copied for printout below
	
	overwrite_anyway = force;
	
	for(uint32_t i = 0; i < structure.size(); i++){

		mml::string	value		= structure[i];								// Eintrag aus der Datei
		mml::string	goal_src	= "";									// Quellpfad des Eintrages
		mml::string	goal_dst	= "";									// Zielpfad des Eintrages
		//std::size_t				output_size = goal_src.size() + goal_dst.size();	// Ausgangsgröße: Zur Ausgabe von [ ok ]
		//std::size_t				correction	= 17;									// Korrekturfaktor
		
		bool					ask_anyway	= false;								// bei unterschiedlicher Größe
		char					input		= '\0';
		
		// Skip if value is a directory
		if(value[-1] == '/'){
			continue;
		}

		goal_src = value;
		goal_dst = dst + value.substr(src.size());
		//goal_dst = value.replace(src, dst);
		
		if(!mml::Unix::exist(goal_src.getValue())){		// Quelldatei existiert nicht
			std::cout << "The source file "<< goal_src.str() << " doesn't exist" << std::endl;
			return 1;
		}

		/*
		 * **************************************
		 * *	Check things if file exists		*
		 * **************************************
		 */
		if (mml::Unix::exist(goal_dst.str())) {
			// Größe unterschiedlich von beiden Dateien nochmals nachfragen
			if((mml::file::size(goal_src.str()) != mml::file::size(goal_dst.str()) || mml::file::time_mod(goal_src.str()) < mml::file::time_mod(goal_dst.str())) && !overwrite && mml::Unix::exist(goal_dst.str()) && !falsewrite)
				ask_anyway = true;
			
			copied_files_print++; // One file will be copied
			// Nicht überschreiben, show three points while skipping
			if(falsewrite && mml::Unix::exist(goal_dst.str()) && !ask_anyway) {
				status++;
				
				status_active = true;
				if(status % (256*4) == 0) {
					printf("\r   ");
					status = 0;
				}
				else if(status % (256*3) == 0)
					printf("\r...");
				else if(status % (256*2) == 0)
					printf("\r.. ");
				else if(status % (256) == 0)
					printf("\r.  ");
				std::cout.flush();
				continue;
				
			}
			else if(status_active) {
				printf("\r");
				status_active = false;
			}
			
			// Check file size and ask if it is different
			fileSize = mml::file::size(goal_src.str());
			
			
			if(!falsewrite) {
				if((mml::Unix::exist(goal_dst.str()) && !force && !overwrite) || (ask_anyway && !overwrite_anyway)){
					// Different Size					
					if(mml::file::size(goal_src.str()) != mml::file::size(goal_dst.str())) {
						if(fileSize > _1GB)
							std::cout << "| Size of source file is " << ((double) mml::file::size(goal_src.str()))/_1GB << " GB and size of destination file is " << ((double) mml::file::size(goal_dst.str()))/_1GB << " GB!";
						else if(fileSize > _1MB)
							std::cout << "| Size of source file is " << ((double) mml::file::size(goal_src.str()))/_1MB << " MB and size of destination file is " << ((double) mml::file::size(goal_dst.str()))/_1MB << " MB!";
						else
							std::cout << "| Size of source file is " << ((double) mml::file::size(goal_src.str()))/_1KB << " KB and size of destination file is " << ((double) mml::file::size(goal_dst.str()))/_1KB << " KB!";
						if(mml::file::size(goal_src.str()) != mml::file::size(goal_dst.str()))
							std::cout << " Size different!" << std::endl;
						else
							std::cout << std::endl;
					}

					// Different modifed size
					if(mml::file::time_mod(goal_src.str()) != mml::file::time_mod(goal_dst.str())) {
						std::cout << "| Modified time of source file is " << mml::date(mml::file::time_mod(goal_src.str())) << " and of destination file is " << mml::date(mml::file::time_mod(goal_dst.str())) << "!";
						if(mml::file::time_mod(goal_src.str()) < mml::file::time_mod(goal_dst.str()))
							std::cout << " Destination is more recent!" << std::endl;
						else
							std::cout << std::endl;
					}
					
					
					std::cout << "| " << goal_dst << " exists. Overwrite? [y|n|A|N] ";
					input = std::cin.get();
					
					if((int) input != 10)	std::cin.ignore(256,10);	// falls kein Enter(10) am Anfang eingeben wurde, ignoriere alle nachfolgenden Zeichen bis zum Enter
					
					if(input == 'n')
						continue;
					else if(input == 'N')	// overwrite never
						falsewrite = true;
					else if(input == 'A' && !ask_anyway)	// immer überschreiben, aber nur wenn Größe gleich und Zieldatei nicht neuer => nur force adden, damit trotzdem noch bei diesen Fällen gefragt wird
						force = true;
					
					if(input == 'A' && ask_anyway && !overwrite) {	// always overwrite no matter what
						overwrite_anyway = true;
						overwrite = true;
					}
				}
			}
			
			// Bei Eingabe 'N':
			if(falsewrite && mml::Unix::exist(goal_dst.str()) && !(ask_anyway && input == 'y') && !(overwrite_anyway && ask_anyway))
				continue;
		}
		
		copied_files++; // One file will be copied
		// Copy stuff
		if(verbose)	// verbose Ausgabe
			std::cout << "[" << copied_files_print << "/" << num_of_files << "] " << goal_src << " -> " << goal_dst;
		
		if(progress)
			std::cout << std::endl;
		
		mml_actual_file = goal_dst;
		
		mml::file::byteCopy(goal_src.str(),goal_dst.str(),blocksize,progress);
		
		mml_actual_file = "";
		
		// Korrekturfaktor für Ausgabe bei Dateigröße
		if(fileSize > _1G)
			filesize_correct = std::to_string((int) fileSize/_1G).size();
		else if(fileSize > _1M)
			filesize_correct = std::to_string((int) fileSize/_1M).size();
		else
			filesize_correct = std::to_string((int) fileSize/_1K).size();

		// **********************************************************
 		// *	Determination of the width to print out [ ok ]		*
 		// **********************************************************
		if(verbose){	// verbose Ausgabe
				
			// Get information from the console
			struct winsize console;
			ioctl(STDOUT_FILENO, TIOCGWINSZ, &console);

			// Depending if progress is shown, the output_size is different
			std::size_t output_size = 0;
			if(!progress) {
				output_size =  goal_dst.size() + goal_src.size() - 17;
				output_size += std::to_string(copied_files).size() + 4 + std::to_string(num_of_files).size(); // add the infos about how many files are copied
				// Correct if the print out is bigger than the console width (21 by testing out)
				if ((int) output_size > console.ws_col-22)
					output_size = output_size % (console.ws_col-22) - 22;
				std::cout << std::setw(console.ws_col - output_size) << "\e[34m\[\e[1;32m ok\e[0m\e[34m ]" << "\e[0m" << std::endl;
			}
			else {
				filesize_correct = -3; // Correction for the progress bar
				output_size =  73-22;
				std::cout << std::setw(console.ws_col - output_size + filesize_correct) << "\e[34m\[\e[1;32m ok\e[0m\e[34m ]" << "\e[0m" << std::endl;
				}
			std::cout.flush();
		}
		//else {
		//	std::cout << "\rFiles copied [" << copied_files <<  "/" << num_of_files << "]";
		//}
		
		actual_file++;

	}
	
	if(verbose || verbose_debug) {
		std::cout << "[copy] " << directories.size() << " directories created and " << copied_files << " files copied." << std::endl;
	}
	else if(verbose_debug)
		std::cout << "[copy] End of function!" << std::endl;
	else
		std::cout << std::endl;

	return 0;
}

// TODO Verknüpfungen werden ignoriert
int mml::file::Program_exist( std::string program ){
	
	mml::string					path_string		= std::getenv("PATH");
	mml::shell::arg				path			= {};
	std::vector<std::string>	files			= {};
	std::size_t					pos				= path_string.find(":");
	
	// Wegen Speicherzugriffsfehler, Vektor sicher leer:
	path.del();
	
	do{
		path.push_back(path_string.substr(0, pos));
		
		path_string = path_string.substr(pos + 1);
		
		pos = path_string.find(":");
	
		
	} while(pos < std::string::npos);
	
	for(uint32_t i = 0; i < path.size(); i++){
		files = path[i].ls("","");
	
		for(uint32_t a = 0; a < files.size(); a++){
			if(files[a] == program)
				return true;
		}
	}
	
	mml::shell::letter("red");
	mml::shell::formation("blink");
	
	std::cout << "The program " + program + " doesn't exist in the PATH!" << std::endl;
	
	mml::shell::normal();
		
	return false;
}

void mml::file::remove(std::string file) {
	std::filesystem::remove(file);
}

void mml::file::set_date_dir(mml::string src, mml::string dst, std::vector<std::string> ends, bool recursive, bool all, bool verbose) {
	// Only for linux defined systems
	#ifdef __linux__
	std::vector<std::string> files = src.ls("","",recursive, all); // Files in source

	for(uint32_t i = 1; i < files.size(); i++) {
		for(uint32_t j = 0; j < ends.size(); j++) {
			mml::string end = ends[j];
			if(((mml::string) files[i]).exist(end.str())) {
			
				std::string dest = dst.str() + files[i];
					
				// Special behaviour for NEF and HEIC as it could have been converted
				if(end == "NEF" || end == "HEIC") {
					std::string dest1 = dst.str() + files[i].substr(0,files[i].length()-end.size()) + "JPG";
					std::string dest2 = dst.str() + files[i].substr(0,files[i].length());
					if(mml::Unix::exist(dest1))
						mml::Unix::set_date(src.str() + files[i],dest1,verbose);
					if(mml::Unix::exist(dest2))
						mml::Unix::set_date(src.str() + files[i],dest2,verbose);
					continue;
				}
				
				if(mml::Unix::exist(dest)) {
					if(verbose)
						std::cout << src + files[i] << " ->" << dest << std::endl;
					mml::Unix::set_date(src.str() + files[i],dest,verbose); // set the date
					continue;
				}
			}
		}
	}
	#else
	std::cout << "[set_date] Not defined for non-linux systems" << std:::endl;
	#endif
	return;
}

std::size_t mml::file::size(const std::string& filename) {
	// if file is not a file  or does not exists => return 0
    if(!mml::Unix::exist(filename))
		throw std::runtime_error("[size] File " + filename + " does not exist.");
	if (mml::Unix::filetype(filename) != S_FILE) {
		std::cout << "[size] " << filename << " is not a file => Return size=0" << std::endl;
        return 0;
	}
    
    std::ifstream ifile(filename, std::ifstream::ate | std::ifstream::binary);

    return ifile.tellg();    
}

std::string mml::file::humanread(std::size_t number) {
	if(number > _1GB)
		return std::to_string(number/_1GB) + " GB";
	else if(number > _1MB)
		return std::to_string(number/_1MB) + " MB";
	else if(number > _1KB)
		return std::to_string(number/_1KB) + " KB";
	else if(number > _1B)
		return std::to_string(number/ _1B) + " B";
	else
		return std::to_string(number) + " b";
	
}
std::string mml::file::size_human(const std::string& filename, bool verbose) {

	if(!mml::Unix::exist(filename))
		throw std::runtime_error("[size_human] File " + filename + " does not exist!");
	
	
	std::size_t		fileSize	= size(filename);
	std::string		file		= "";
	
	file = humanread(fileSize);
	
	if(verbose)
		std::cout << "| Size of the file: " << file << std::endl;
	
	return file;
}

std::string mml::file::size_dir(mml::string& dir, std::string include, std::string exclude, bool verbose, bool recursive, bool all, bool human_readable) noexcept {
	std::size_t						size		= 0;
	std::string						size_str	= "";
	const std::vector<std::string>	ls			= dir.ls(include, exclude, recursive, all);
	
	for(uint32_t i = 0; i < ls.size(); i++) {
		if(ls[i][ls[i].size()-1] != '/')
			size += mml::file::size(ls[i]);
	}
	if(human_readable)
		size_str = humanread(size);
	else
		size_str = std::to_string(size);
	
	if(verbose)
		std::cout << "| Size of the directory: " << size_str << std::endl;
	
	return size_str;
}

time_t mml::file::time_mod(const std::string& filename) {
	struct stat sb;
	stat(filename.c_str(), &sb);
	return sb.st_mtime;
}
