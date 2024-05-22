/**
 * @author Mike Moser
 * 
 * Quelldatei args.cpp
 * Enthält verschiedene Funktionen für die Klasse args
 * 
*/

#include <iostream>

#include "mml/log.hpp"
#include "mml/standards.hpp"
#include "mml/file.hpp"
#include "mml/shell.hpp"

	mml::log &mml::log::operator=(std::string value){
		mml::log temp(value);
		return *this;
		
	}

	void mml::log::backup(bool verbose, bool Reset) {
		mml::shell::arg Empty;
		
		Empty.push_back("-f");
		if(verbose)
			std::cout << "| Backup logfile...";
		
		// Write into log that a backup is executed
		cout("[check_root] backup is executed at " + mml::date("Date+Time") + ".", true);
		
		// Execute backup
		for(int32_t i = 4; i >= 0; i--) {
			// NOTE 0 is for logpath.bak and logpath.bak1
			if(i == 0) {
				if(mml::Unix::exist(logpath.str() + ".bak"))
					file::copy(Empty, logpath + ".bak",logpath + ".bak1");
				file::copy(Empty, logpath ,logpath + ".bak");
			}
			else if(mml::Unix::exist(logpath.str() + ".bak" + std::to_string(i)))
				file::copy(Empty, logpath + ".bak"  + std::to_string(i) ,logpath + ".bak" + std::to_string((i+1)));
		}
		if(verbose)
			std::cout << std::endl;
		
		// Reset first file to have a new file if wished
		if(Reset)
			reset(verbose);
	}
	
	void mml::log::close() {
		this->output.close();
	}
	
	void mml::log::cout(mml::string value,bool newline) {
		this->output << value;
		if(newline)
			this->output << std::endl;
	}
// 	void mml::log::cout(std::string value,bool newline) {
// 		this->output << value;
// 		if(newline)
// 			this->output << std::endl;
// 	}
	void mml::log::cout(double value,bool newline) {
		this->output << value;
		if(newline)
			this->output << std::endl;
	}
	void mml::log::cout(int value,bool newline) {
		this->output << value;
		if(newline)
			this->output << std::endl;
	}
	
	mml::string mml::log::getline(uint32_t line) {
		mml::string value;
		
		value.getline(logpath.str(), line);
		
		return value;
	}
	
	mml::string mml::log::getline_back(uint32_t line) {
		std::vector<std::streampos>		lines	;
		std::string						value	= "";
		std::ifstream					input	(this->logpath.c_str());
		
		// Zeilenpositionen bestimmen
		while(!input.eof()) {
			lines.push_back(input.tellg());	// Zeilenposition speichern
			std::getline(input,value);		// zur nächsten Zeile
		}
		
		// letzte Zeile eine newline => Zeilenposition entfernen
		if(value == "")
			lines.pop_back();
		
		// Machbarkeit prüfen
		if(line > lines.size())
			mml::shell::error("[getline_back] Wrong line number!");
		
		// Position setzen
		input.clear();	// error state zurücksetzen, sonst bei seekg und tellg error
		input.seekg(lines[lines.size() - 1 - line]);
		
		std::getline(input,value);
		return value;
		
	}
	
	mml::string mml::log::lastline() {
		std::string value;
		
		value = getline_back(0).str();
		
		return value;
	}
	
	void mml::log::header() {
		output << "| Log-File " << logpath << std::endl;
		output << "| Timestamp: " << date("Date+Time") << std::endl;
	}

	void mml::log::open(mml::string path) {
		// Logdatei öffnen
		if(path == "")
			path = this->logpath;
		
		this->output.close();
		this->output.open(path.c_str(),std::ios::out | std::ios::app);
		this->logpath = path;
	}
	
	void mml::log::print(bool linenumber) {
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
// 			if(value[0] == '[' && value[value.size()-1] == ']')
// 				mml::shell::letter("lightgreen");
			mml::shell::cout(value,true);
// 			mml::shell::normal();
			lines++;
		}
	}
	
	void mml::log::reset(bool verbose) {
		if(verbose)
			std::cout << "| Reset logfile...";
		this->output.close();
		this->output.open(this->logpath.c_str());
		header();
		if(verbose)
			std::cout << std::endl;
	}


	

