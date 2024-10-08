/**
 * @file string.cpp
 * @author Mike Moser
 * @brief Function definitions of the class string
 * @version 1.0
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
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

#include "mml/standards.hpp"
#include "mml/string.hpp"
#include "mml/shell.hpp"
#include "mml/file.hpp"
#include "mml/Unix.hpp"


char &mml::string::operator[](int index) {		// bestimmte Position ausgeben
		if (index < 0 && abs(index) < value.size())
			index = value.size() + index;
		
		if(index >= (int) value.size())
			throw std::logic_error("[operator[]] Out of range");

		return value[index];
}

const char &mml::string::operator[](int index) const {		// bestimmte Position ausgeben
		if (index < 0 && abs(index) < value.size())
			index = value.size() + index;
		
		if(index >= (int) value.size())
			throw std::logic_error("[operator[]] Out of range");

		return value[index];
}


std::string &mml::string::operator()() noexcept{		// value zurückgeben, wenn in Klammern
	return value;
}

const std::string &mml::string::operator()() const noexcept{		// value zurückgeben, wenn in Klammern
	return value;
}

double mml::string::atof() const  noexcept{
	return std::atof(this->value.c_str());
}

int mml::string::atoi() const noexcept {
	return std::atoi(this->value.c_str());
}


void mml::string::log(std::string logpath) const {
	
	mml::Unix::User user;
	std::size_t		folder = 0;
	
	if(!mml::Unix::exist(logpath)) {
		// determine directory of the log file
		for(uint32_t i = logpath.size(); i > 0; i--) {
			if(logpath[i] == '/') {
				folder = i;
				break;
			}
		}
		// check permission
		if(!user.check("uid",0) && !user.check("uid",mml::Unix::getFileUID(logpath.substr(0,folder).c_str()))) {
			throw std::runtime_error("[log]: Creation of the log file '" + logpath + "' is not possible: Permission denied");
		}
	}
	
	std::ofstream output;
	output.open(logpath.c_str(),std::ios::out | std::ios::app); // going to the end
	output << value << std::endl;
}

std::string mml::string::lower() noexcept {
	for(uint16_t i = 0; i < (uint16_t) value.size(); i++){
			temp[i] = tolower(value[i]);
	}
	return temp;
}

std::vector<std::string> mml::string::ls(std::string name_include, std::string name_exclude, std::vector<std::string> &directories, bool recursive, bool all) const {
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
		throw std::runtime_error("[ls] Given string does not exist!");
	}

	// If file is not a directory, only add path and return it (it must exists as checked before)
	if (!mml::Unix::isdir(path)) {
		LS.push_back(path);
		return LS;
	}

	// Go through the directory and add the desired directories and files
	for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{path}) {
		// Remove leading and ending '"'
		temp1 = mml::to_string(dir_entry).sub(1,-2);
		
		// Don't add files recursively
		if (!recursive && temp1.substr(path.size()+2).exist("/"))
			continue;
		// Don't add hidden files
		if (!all && (temp1.exist("/.")))
			continue;
		// Exclude a string
		if (name_exclude != "" && temp1.exist(name_exclude))
			continue;
		
		// Correction for backslashes being read as two backslashes
		if(temp1.exist("\\")) {
			for (uint32_t i = 0; i < temp1.size();i++) {
				if(temp1[i] == '\\' && temp1[i] == '\\')
					temp1 = temp1.sub(0,i-1) + temp1.substr(i+1);
			}
		}

		// Object is a directory
		if (mml::Unix::isdir(temp1)) {
			temp1 += "/";
			if (save_dirs) {
				temp2 = temp1.replace(path,""); // Check if name_include exists in the part after the path
				if (temp2.substr(0,temp2.find('/')).exist(name_include))
					directories.push_back(temp1.str());
			}
					
		}

		// If directory in path does not contain include => skip everything
		temp2 = temp1.replace(path,"");
		if (temp2.substr(0,temp2.find('/')).exist(name_include))
			LS.push_back(temp1.str());
		// List if include exists
		//if (temp1.exist(name_include))
		//	LS.push_back(temp1.str());
	}

	return LS;
}

std::vector<std::string> mml::string::ls(std::string name_include, std::string name_exclude, bool recursive, bool all) const {
	std::vector<std::string> directories = {"---"};
	std::vector<std::string> LS = ls(name_include, name_exclude, directories, recursive, all);
	return LS;
}

	
mml::string mml::string::substr(std::size_t pos1, std::size_t length1) const noexcept {
	return value.substr(pos1,length1);
}

mml::string mml::string::substr(std::size_t pos1) const noexcept{
	
	return value.substr(pos1);
}

mml::string mml::string::sub(std::size_t beg, std::size_t end) const noexcept {
	// beg is a negative number (negative means here very big)
	if (beg > value.size() && (std::string::npos - beg < value.size()))
		beg = value.size() - (std::string::npos - beg) -1;
	// End is negative
	if (end > value.size() && (std::string::npos - end < value.size()))
		end = value.size() - (std::string::npos - end) -1;
		
	return value.substr(beg,end-(beg-1));
}

bool mml::string::mkdir_p() noexcept {

	std::string make_dir = "";	// string to create the directories
	temp=value;					// Save the value to create directories step by step
	std::size_t pos;			// Position of '/'
	pos = temp.find("/",1);
	
	// Check if the directory exists already to save computing time
	if (mml::Unix::exist(value) && mml::Unix::isdir(value))
		return 0;
	
	do{
		make_dir += temp.substr(0,pos);
		temp = temp.substr(pos,temp.size()-pos);

		// Check if the dir exists as a non-directory, otherwise create it
		if(mml::Unix::exist(make_dir.c_str()) && !mml::Unix::isdir( make_dir ))
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

bool mml::string::remove() const noexcept {
	return mml::Unix::isfile(this->value) ? std::remove(this->value.c_str()) : false;
	
}


std::string mml::string::getValue() const noexcept {
	return this->value;
}

std::size_t mml::string::size() const noexcept {
	return value.size();
}

std::string mml::string::str() const noexcept {
	return this->value;
}

void mml::string::writeline(std::ofstream& output) const noexcept {
	output << this->value << std::endl;
}

void mml::string::writeline(std::string file) const noexcept {
	std::ofstream output(file);
	output << this->value << std::endl;
	output.close();
}

const char* mml::string::c_str() const noexcept {
	return this->value.c_str();
}


int mml::string::stoi() const noexcept {
	return std::stoi(this->value);
}

uint32_t mml::string::hash() const noexcept {
	return mml::const_string_hash(this->value.c_str());
}


void mml::string::getline(std::ifstream& input) noexcept {
	std::getline(input,this->value);
}


std::string mml::string::getline(const mml::string input, const std::size_t line, bool back) {
	if (!mml::Unix::exist(input)) {
		std::error_code ec = std::make_error_code(std::errc::no_such_file_or_directory);
        throw std::filesystem::filesystem_error("[getline] File" + input.str() + " does not exist", ec);
	}


	std::ifstream input_stream(input.str());
	std::string del;
	std::vector<std::string> lines = {};

	// Look from backwards => Need to read all the lines
	if(back) {
		while(input_stream.eof()) {
			std::getline(input_stream,del);
			lines.push_back(del);
		}
		this->value = lines[lines.size() - 1 - line];
	}
	// Line start from 0 => Not necessary to read all lines to save computation time
	else {
		for(uint32_t i = 0; i < line; i++) {
			std::getline(input_stream,del);
		}
		std::getline(input_stream,value);
	}
	// Close the stream
	input_stream.close();
	
	return value;
}

std::string mml::string::getlastline(const mml::string input) {
	if (!mml::Unix::exist(input)) {
		std::error_code ec = std::make_error_code(std::errc::no_such_file_or_directory);
        throw std::filesystem::filesystem_error("[getline] File" + input.str() + " does not exist", ec);
	}
	std::ifstream input_stream(input.str());
	while(!input_stream.eof())
		std::getline(input_stream,this->value);
	
	input_stream.close();
	
	return value;
}

uint32_t mml::string::count(mml::string name) const noexcept {
	int count = 0;
    size_t pos = value.find(name.str());

    while (pos != std::string::npos) {
        ++count;
        pos = value.find(name.str(), pos + name.size());
    }

	return count;
}
void mml::string::cout(bool newline, std::string text) const noexcept {
	std::cout << text << this->value;
	if(newline)
		std::cout << std::endl;
	return;
}
std::string mml::string::del_letter(bool save) noexcept {
	std::string temp = "";
	for(uint32_t i = 0; i < this->value.length(); i++) {
		if(value[i] < 65 || value[i] > 122)
			temp += value[i];
	}
	if(save)
		this->value = temp;
	return temp;
}

std::string mml::string::del_number(bool save) noexcept {
	std::string temp = "";
	for(uint32_t i = 0; i < this->value.length(); i++) {
		if(value[i] < 48 || value[i] > 57)
			temp += value[i];
	}
	if(save)
		this->value = temp;
	return temp;
}

std::string mml::string::del_space(bool save) noexcept {
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

bool mml::string::_exist(std::string search) const noexcept {
	return value.find(search) < std::string::npos ? true : false;
}






