/**
 * @author Mike Moser
 * 
 * @file file.hpp
 * @brief This file includes functions regarding the files. It might only work on linux as some
 *              commands might be os-dependent. The main function of here is to copy files. It also has
 *              other functions such as checking if a file exists
 * 
*/

#ifndef MML_INCLUDE_MML_FILE_HPP
#define MML_INCLUDE_MML_FILE_HPP

#include <functional>
#include <iostream>

#include "mml/standards.hpp"

namespace mml{
	namespace file{
		
		/**
		 * @brief Opens two textfiles and writes it in another
		 * @param filepath_input1 First file name to be written into a new one
		 * @param filepath_input2 First file name to be written into a new one
		 * @param filepath_output where the content is written to
		 * @throw runtime_error : if input1 or input2 cannot be read
		 */ 
		void add_twofiles( std::string filepath_input1 , std::string filepath_input2 , std::string filepath_output);
		
		/**
		 * @brief Copy a file
		 * @param src Source File
		 * @param dest Destination file
		 * @param blockSize Size of the block to be copied at once
		 * @param progress Print out a progress bar
		 * @return bool
		 * @throw runtime_error : if source file does not exist
		 * @author Mike, Lucas
		 */ 
		bool byteCopy(const std::string& src, const std::string& dest, std::size_t blockSize, bool progress = false);
		
		/**
		 * @brief Copy the content of the path to a new one
		 * @param src Source Path
		 * @param dst Destination path
		 * @param name_in Copy only files including this string in depth = 1
		 * @param name_ex Exclude all files and directories with this name
		 * @param blocksize Blocksize to be copied at once
		 * @param verbose Verbose output
		 * @param verbose_debug Debugging output
		 * @param all Copy also hidden files
		 * @param recursive Copy recursive
		 * @param force Overwrite everything without asking
		 * @param progress Print out the progress while copying
		 * @param falsewrite Do not overwrite files in the destination
		 * @return 0 if successfull
		 * @throw logic_error : If a file is to be copied but dst is a directory
		 * @throw logic_error : If destination exists as a file if a directory is copied
		 * @throw runtime_error : If user is not permitted to write into the destination
		 * @throw runtime_error : If last directory in destionation is not a directory
		 * @todo Copy symbolic and hard link file by creating them
		 */
		int copy (mml::string src, mml::string dst, std::string name_in = "", std::string name_ex = "", size_t blocksize = _100MB, bool verbose=false, bool verbose_debug=false, bool all=false, bool recursive=false, bool force=false, bool progress=false, bool falsewrite = false);
		
		/**
		 * @brief Compare two files by using the SHA256 algorithm. Only works for linux.
		 * @param src Source file
		 * @param dst Destination file
		 * @return bool if sha256 is the same
		 */
		bool equal(std::string src, std::string dst);
		
		/**
		 * @brief Determine the type of an object (directory, file, etc.)
		 * @param filepath Path to the object
		 * @return Returns a number to identify the type of the object
		 * @note The numbers have the following meaning:
		 * -  1: DT_FIFO
		 * -  2: Serial connected device, mouse, etc.
		 * -  4: Directory
		 * -  6: Device or partition
		 * -  8: normal file
		 * - 10: symbolic link
		 * - 12: Socket
		 * @todo use library to detect what it is and also then use hard link and symbolic link
		*/
		int32_t  filetype(std::string filepath);
		
		/**
		 * @brief Convert number into human readable number
		 * @param number A number to be converted
		 * @return std::string
		 */
		std::string humanread(std::size_t number);

		/**
		 * @brief Determine number of lines in a file
		 * @param path Path to the file
		 * @return size_t Number of lines
		 */
		std::size_t num_lines(std::string path);
		
		// TODO ERROR DOES NOT WORK
		/**
		 * @brief Checks if a program exists
		 * @param program Program to be checked
		 */
		int Program_exist( std::string program );
		
		
		/**
		 * @note Delete a single file
		 * @param file path to the file
		 * @author Mike
		 */
		void remove(std::string file);
		
		/**
		 * @note Convert the date of files with specific endings in a directory
		 * @param src Source path
		 * @param dst Destination path
		 * @param ends Endings to be checked
		 * @param recursive Recursive check
		 * @param all Also check hidden files
		 * @param verbose Verbose output
		 * @note This function is only defined for linux systems
		*/
		void set_date_dir(mml::string src, mml::string dst, std::vector<std::string> ends={"NEF","tif","JPG","jpg","MP4","MOV","PNG","HEIC","JPEG","jpeg","pdf", "PDF"}, bool recursive= false, bool all = false, bool verbose = false);

		/**
		 * @brief Calculates the size of a file
		 * @param filename Path to the file
		 * @return Size of the file
		 * @author Lucas
		 * @throw runtime_error : if file does not exist
		 */
		std::size_t size(const std::string& filename);
		
		/**
		 * @brief Calculates the size of a file
		 * @param filename Path to the file
         * @param verbose Print out
		 * @return Returns the size of a file in a readable form as a string
		 * @throw runtime_error : if file does not exist
		 */
		std::string size_human(const std::string& filename, bool verbose = true);
		
		/**
		 * @brief Calculates the size of a directory structure
         * @param dir Path to the directory
         * @param include Include only count objects having this string in its name
         * @param exclude Exclude objects with this name from the count
		 * @param verbose Verbose print out
		 * @param recursive Recursive check
		 * @param all Also count hidden files
		 * @param human_readable Print out in human readable form
		 * @return Returns the size of the directory
		 */
		std::string size_dir(mml::string& dir, std::string include = "", std::string exclude = "", bool verbose=false, bool recursive=false, bool all=false, bool human_readable=false) noexcept;
		
		/**
		 * @brief Returns the last modified time of a file in seconds
		 * @param filename Path to the file
		 * @return Seconds since 1970
		 */
		time_t time_mod(const std::string& filename);
	}
}
#endif
