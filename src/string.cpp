/**
 * @author Mike Moser
 * 
 * @file string.cpp
 * Enthält verschiedene Funktionen
 * 
*/ 


#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>

#include <sys/stat.h>
#include <stdlib.h>	//atoi()

#include <string.h>
#include <fstream>
#include <sstream>

#include <filesystem> // for ls function

#include "mml/functions.hpp"
#include "mml/shell.hpp"
#include "mml/file.hpp"
#include "mml/Unix.hpp"


char &mml::string::operator[](int index){		// bestimmte Position ausgeben
		if (index < 0 && abs(index) < value.size())
			index = value.size() + index;
		
		if(index >= (int) value.size())
			throw std::logic_error("[operator[]] Out of range");

		return value[index];
}

std::string &mml::string::operator()(){		// value zurückgeben, wenn in Klammern
	return value;
}

double mml::string::atof() {
	
	
	return std::atof(this->value.c_str());
}

int mml::string::atoi() {
	return std::atoi(this->value.c_str());
}
// Funktionen:

std::size_t mml::string::find_back(mml::string name, std::size_t pos, std::size_t low) {
	// pos is defined as the position where to start. If pos is too close to the size of the string
	// it should be reset
	if(pos == 0 || (value.size() - name.size()) < pos)
		pos = this->value.size() - name.size() - pos;
	for(std::size_t i = pos; i >= low; i--) {
		if(value.substr(i,name.size()) == name.str())
			return i;
	}
	return std::string::npos;
}

void mml::string::log(std::string logpath) {
	
	mml::Unix::User user;
	std::size_t		folder = 0;
	
	if(!mml::Unix::exist(logpath)) {
		// Ordner der Logdatei bestimmen
		for(uint32_t i = logpath.size(); i > 0; i--) {
			if(logpath[i] == '/') {
				folder = i;
				break;
			}
		}
		// Überprüfen der vorhandenen Berechtigung für den Zielpfad
		if(!user.check("uid",0) && !user.check("uid",mml::Unix::getFileUID(logpath.substr(0,folder).c_str()))) {
		
			std::cout << "log: Die Erstellung der Logdatei '" << logpath << "' ist nicht möglich: Keine Berechtigung" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	
	std::ofstream output;
	output.open(logpath.c_str(),std::ios::out | std::ios::app);   // mit ans Ende springen
	output << value << std::endl;
}

std::string mml::string::lower(){
	for(uint16_t i = 0; i < (uint16_t) value.size(); i++){
			temp[i] = tolower(value[i]);
	}
	return temp;
}

std::vector<std::string> mml::string::ls(std::string name_include, std::string name_exclude, std::vector<std::string> &directories, bool recursive, bool all) {
	std::vector<std::string> 	LS;
	mml::string 				temp1;
	mml::string 				temp2; // for name_include used
	bool					save_dirs = false; // Save directories separately

	// Check if the vector is actually defined as a parameter => otherwise do not change it to save memory.
	if (directories.size() > 0) {
		if(directories[0] != "---")
			save_dirs = true;
	}
	else
		save_dirs = true;

	std::string path = this->value;

	// Add ./ to make it more clear, if needed
	if (path[0] != '/' && path.substr(0,2) != "./" && path.substr(0,3) != "../")
		path = "./" + path;

	// If path does not exists => Print error
	if (!mml::Unix::exist(path)) {
		mml::shell::error("[ls] Given string does not exist!");
	}

	// If file is not a directory, only add path and return it (it must exists as checked before)
	if (mml::Unix::filetype(path) != S_DIR) {
		LS.push_back(path);
		return LS;
	}

	// Go through the directory and add the desired directories and files
	for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{path}) {
		// Remove leading and ending '"'
		temp1 = mml::to_string(dir_entry).sub(1,-2);

		// Don't add files recursively
		if (recursive && temp1.substr(path.size()+2).exist("/"))
			continue;
		// Don't add hidden files
		if (all && (temp1.exist("/.")))
			continue;
		// Exclude a string
		if (name_exclude != "" && temp1.exist(name_exclude))
			continue;
		// Object is a directory
		if (mml::Unix::filetype(temp1.str()) == S_DIR) {
			temp1 += "/";
			if (save_dirs) {
				temp2 = temp1.replace(path.c_str(),""); // Check if name_include exists in the part after the path
				if (temp2.substr(0,temp2.find('/')).exist(name_include))
					directories.push_back(temp1.str());
			}
					
		}
		// If directory in path does not contain include => skip everything
		temp2 = temp1.replace(path.c_str(),"");
		if (temp2.substr(0,temp2.find('/')).exist(name_include))
			LS.push_back(temp1.str());
		// List if include exists
		//if (temp1.exist(name_include))
		//	LS.push_back(temp1.str());
	}

	return LS;
}

std::vector<std::string> mml::string::ls(std::string name_include, std::string name_exclude, bool recursive, bool all) {
	std::vector<std::string> directories = {"---"};
	std::vector<std::string> LS = ls(name_include, name_exclude, directories, recursive, all);
	return LS;
}



	
mml::string mml::string::substr(std::size_t pos1, std::size_t length1){
	return value.substr(pos1,length1);
}

mml::string mml::string::substr(std::size_t pos1){
	
	return value.substr(pos1);
}

mml::string mml::string::sub(std::size_t beg, int32_t end) {
	// beg is a negative number (negative means here very big)
	if (beg > value.size() && (std::string::npos - beg < value.size()))
		beg = value.size() - (std::string::npos - beg) -1;
	// End is negative
	if (end < 0)
		end = value.size() + end;
		
	return value.substr(beg,end-(beg-1));
}

bool mml::string::mkdir_p() {

	std::string make_dir = "";	// string to create the directories
	temp=value;					// Save the value to create directories step by step
	std::size_t pos;			// Position of '/'
	pos = temp.find("/",1);
	
	// Check if the directory exists already to save computing time
	if (mml::Unix::exist(value) && mml::Unix::filetype(value) == S_DIR)
		return 0;
	
	do{
		make_dir += temp.substr(0,pos);
		temp = temp.substr(pos,temp.size()-pos);

		// Check if the dir exists as a non-directory, otherwise create it
		if(mml::Unix::exist(make_dir.c_str()) && mml::Unix::filetype( make_dir ) != S_DIR)
			mml::shell::error("[mkdir_p] Cannot create directory " + make_dir + " as it already exists as a non-directory!");
		else
			mkdir(make_dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);

		// Determine new position for the new directory if not at the end
		pos = temp.find("/",1);
	} while(pos < std::string::npos);

	// Now create the last directory
	if(!mml::Unix::exist(value.c_str()))
				mkdir(value.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH | S_IWOTH);

	return 0;
}

bool mml::string::remove() {
	return mml::file::filetype(this->value) == S_FILE ? std::remove(this->value.c_str()) : false;
	
}


std::string mml::string::getValue() {
	return this->value;
}

std::size_t mml::string::size() {
	return value.size();
}

std::string mml::string::str() {
	return this->value;
}

void mml::string::writeline(std::ofstream& output) {
	output << this->value << std::endl;
}

void mml::string::writeline(std::string file) {
	std::ofstream output(file);
	output << this->value << std::endl;
	output.close();
}

const char* mml::string::c_str() {
	return this->value.c_str();
}


int mml::string::stoi() {
	return std::stoi(this->value);
}

uint32_t mml::string::hash() {
	return functions::const_string_hash(this->value.c_str());
}

/*
std::string mml::string::getline(std::ifstream& input) {
	std::getline(input,this->value);
	return this->value;
}*/

void mml::string::getline(std::ifstream& input) {
	std::getline(input,this->value);
}


std::string mml::string::getline(std::string input, std::size_t line){
	std::ifstream input1(input);
	std::string del;
	for(uint32_t i = 0; i < line; i++)
		std::getline(input1,del);
	std::getline(input1,value);
	input1.close();
	
	return value;
}

uint32_t mml::string::count(mml::string name) {
	uint32_t counts = 0;
	std::size_t pos = value.find(name.str());
	if(range(pos)) {
			counts++;
	}
	do {
		pos = value.find(name.str(),pos+1);
		if(range(pos)) {
			counts++;
		}
		
	} while(pos < name.size());
	
	return counts;
}
void mml::string::cout(bool newline, std::string text) {
	std::cout << text << this->value;
	if(newline)
		std::cout << std::endl;
	return;
}
std::string mml::string::del_letter(bool save) {
	std::string temp = "";
	for(uint32_t i = 0; i < this->value.length(); i++) {
		if(value[i] < 65 || value[i] > 122)
			temp += value[i];
	}
	if(save)
		this->value = temp;
	return temp;
}

std::string mml::string::del_number(bool save) {
	std::string temp = "";
	for(uint32_t i = 0; i < this->value.length(); i++) {
		if(value[i] < 48 || value[i] > 57)
			temp += value[i];
	}
	if(save)
		this->value = temp;
	return temp;
}

std::string mml::string::del_space(bool save) {
	std::string temp = "";
	for(uint32_t i = 0; i < this->value.length(); i++) {
		temp += value[i];
		if(value[i] == ' ')
			break;
	}
	if(save)
		this->value = temp;
	return temp;
}

bool mml::string::exist(std::string search) {
	return value.find(search) < std::string::npos ? true : false;
}


bool mml::string::exist(std::string name1, std::string name2, std::string name3, std::string name4) {
	return exist(name1) || exist(name2) || exist(name3) || exist(name4);
}

