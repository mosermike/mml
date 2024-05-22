/**
 * @author Mike Moser
 * 
 * @file file.hpp
 * @description This file includes functions regarding the files. It might only work on linux as some
 *              commands might be os-dependent. The main function of here is to copy files. It also has
 *              other functions such as checking if a file exists
 * 
*/

#ifndef MML_INCLUDE_MML_FILE_HPP
#define MML_INCLUDE_MML_FILE_HPP

#include <functional>
#include "mml/functions.hpp"
#include <iostream>

namespace mml{
	namespace file{
		
		/**
		 * @note Zwei Dateien zu einer zusammenfügen
		 * 
		 * @author Mike
		 */ 
		void add_twofiles( std::string filepath_input1 , std::string filepath_input2 , std::string filepath_output);
		
		/**
		 * @note Kopiervorgang einer Datei mit/ohne Fortschrittsanzeige
		 * 
		 * @return Länge von Gesamtgröße
		 * @author Mike, Lucas
		 */ 
		std::size_t byteCopy(const std::string& src, const std::string& dest, std::size_t num, std::size_t blockSize, bool progress = false, std::string fullsize = "");
		
		/**
		 * @note Kopiert einen Quellpfad zu einem Quellpfad
		 * 
		 * @author Mike
		 */
		uint32_t copy (shell::arg args, mml::string src, mml::string dst, std::string name_in = "", std::string name_ex = "");

		/**
		 * @note Copy a file with determining the block size from the arguments
		 * 
		 * @param arg Arguments from the shell
		 * @param string Source
		 * @param string Destination
		 * @param string Copy only files where this string exists
		 * @param string Copy only files where this string does not exist
		 *
		 * @author Mike
		 */
		std::size_t copyFile(shell::arg args,std::string src, std::string dst);
		
		/**
		 * @note Compare two files by using the SHA256 algorithm. Only works for linux.
		 * 
		 * @author Mike
		 */
		bool equal(std::string src, std::string dst);
		
		/**
		 * @note Determine the type of an object (directory, file, etc.)
		 * @param string Path to the object
		 * @return Returns a number. For interpretation look at definitions.hpp
		 * @author Mike
		*/
		int32_t  filetype(std::string filepath);
		
		/**
		 * @note Convert number into human readable number
		 * @param size_t A number to be converted
		 * @return std::string
		 * @author Mike
		 */
		std::string humanread(std::size_t number);

		/**
		 * @note Determine number of lines in a file
		 * @param string Path to the file
		 * @return size_t Number of lines
		 * @author Mike
		 */
		std::size_t num_lines(std::string path);
		
		// TODO ERROR DOES NOT WORK
		/**
		 * @note Exisiert das Programm
		 * 
		 * @author Mike
		 */
		int Program_exist( std::string program );
		
		
		/**
		 * @note Delete a single file
		 * @param string path to the file
		 * @author Mike
		 */
		void remove(std::string file);
		
		/**
		 * @note Convert date of pictures.
		 * @param arg Arguments from shell
		 * @param string Source path
		 * @param string Destination path
		 * @param bool Check extended endings. False => Only NEF and HEIC
		 * @param bool Verbose output.
		 * 
		 * @author Mike
		*/
		void set_date(mml::shell::arg args, mml::string src, mml::string dst, bool extend = true, bool verbose = false);

		/**
		 * @note Calculates the size of a file
		 * @param string Path to the file
		 * @return size_t Size of the file
		 * @author Lucas
		 */
		std::size_t size(const std::string& filename);
		
		/**
		 * @note Calculates the size of a file
		 * @param string Path to the file
         * @param bool Print out
		 * @return Returns the size of a file in a readable form as a string
		 * @author Mike
		 */
		std::string size_human(const std::string& filename, bool ausgabe = true);
		
		/**
		 * @note Calculates the size of a directory structure
		 * @param arg Arguments from the shell
         * @param string Path to the directory
         * @param bool print out
         * @param string Include only count objects having this string in its name
         * @param string Exclude objects with this name from the count
		 * @attention Arguments must be correct!
		 * 
		 * @return Gibt die Größe des Ordners zurück
		 * @author Mike
		 */
		std::string size_dir(mml::shell::arg args, mml::string& dir, bool ausgabe = false, std::string include = "", std::string exclude = "");
		
		/**
		 * @note Returns the last modified time of a file in seconds
		 * @param string Path to the file
		 * @return Seconds since 1970
		 * @author Mike
		 */
		time_t time_mod(const std::string& filename);
	}
}
#endif
