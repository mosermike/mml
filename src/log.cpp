/**
 * @author Mike Moser
 * 
 * @file args.cpp
 * @brief Different functions for the class log
 * 
*/

#include <iostream>

#include "mml/log.hpp"
#include "mml/standards.hpp"
#include "mml/file.hpp"
#include "mml/shell.hpp"

mml::log &mml::log::operator=(std::string value) noexcept {
	mml::log temp(value);
	return *this;	
}

void mml::log::backup(bool verbose, bool Reset) noexcept {
	if(verbose)
		std::cout << "| Backup logfile...";
	
	// Write into log that a backup is executed
	this->output << "[check_root] backup is executed at " + mml::date("Date+Time") + "." << std::endl;

	// Execute backup
	for(int32_t i = 4; i >= 0; i--) {
		// NOTE 0 is for logpath.bak and logpath.bak1
		if(i == 0) {
			if(mml::Unix::exist(logpath.str() + ".bak"))
				file::copy((mml::string) logpath + ".bak",(mml::string) logpath + ".bak1","","", _1MB,false,false, false, false, true);
			file::copy(logpath,logpath + ".bak","","", _1MB,false,false, false, false, true);
		}
		else if(mml::Unix::exist(logpath.str() + ".bak" + std::to_string(i)))
			file::copy(logpath + ".bak"+ mml::to_string(i),logpath + ".bak" + mml::to_string((i+1)),"","", _1MB,false,false, false, false, true);
	}
	if(verbose)
		std::cout << std::endl;
	
	// Reset first file to have a new file if wished
	if(Reset)
		reset(verbose);
}
	
void mml::log::close() noexcept {
	this->output.close();
}

/*
template <typename T> void mml::log::cout(T value,bool newline) noexcept {
	this->output << value;
	if(newline)
}*/
	
mml::string mml::log::getline(size_t line) noexcept {
	mml::string value;
		
	value.getline(logpath.str(), line);
		
	return value;
}
	
mml::string mml::log::getline_back(size_t line) {
	std::vector<std::streampos>		lines	;
	std::string						value	= "";
	std::ifstream					input	(this->logpath.c_str());
		
	// Determine line position
	while(!input.eof()) {
		lines.push_back(input.tellg());	// Zeilenposition speichern
		std::getline(input,value);		// zur nächsten Zeile
	}
		
	// letzte Zeile eine newline => Zeilenposition entfernen
	if(value == "")
		lines.pop_back();
		
	// Machbarkeit prüfen
	if(line > lines.size())
		throw std::runtime_error("[getline_back] Line number exceeds file (" + std::to_string(line) + "vs." + std::to_string(lines.size()) + ")!");
		
	// Position setzen
	input.clear();	// error state zurücksetzen, sonst bei seekg und tellg error
	input.seekg(lines[lines.size() - 1 - line]);
	
	std::getline(input,value);
	return value;
		
}
	
mml::string mml::log::lastline() noexcept {
	std::string value;
		
	value = getline_back(0).str();
		
	return value;
}
	
void mml::log::header() noexcept {
	output << "| Log-File " << logpath << std::endl;
	output << "| Timestamp: " << date("Date+Time") << std::endl;
}

void mml::log::open(mml::string path) noexcept {
	if(path == "")
		path = this->logpath;
	
	this->output.close();
	this->output.open(path.c_str(),std::ios::out | std::ios::app);
	this->logpath = path;
}
	
void mml::log::print(bool linenumber) noexcept {
	output.close();
	std::ifstream input(logpath.c_str());
	uint32_t lines = 1;
	while(!input.eof()) {
		
		mml::string value;
		value.getline(input);
		
		// verbose: Print linenumber
		if(linenumber) {
			if(lines < 10)
				std::cout << "0";
			std::cout << lines << ": ";
		}
		mml::shell::cout(value,true);
		lines++;
	}
}

void mml::log::reset(bool verbose) noexcept {
	if(verbose)
		std::cout << "| Reset logfile...";
	this->output.close();
	this->output.open(this->logpath.c_str());
	header();
	if(verbose)
		std::cout << std::endl;
}

	