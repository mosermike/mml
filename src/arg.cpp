/**
 * @author Mike Moser
 * 
 * @file args.cpp
 * Contains functions for the class
 * 
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <limits>

#include "mml/shell.hpp"

std::size_t mml::shell::arg::begin(const std::string& str) noexcept {
	for(std::size_t i = 0; i < vec.size() ; ++i)
		for(std::size_t a = 0; a < (vec[i]).size() ; a++)
			if(vec[i].substr(0,a) == str)
				return i;
	return std::string::npos;
}

void mml::shell::arg::_init(std::vector<mml::string>& excepts) noexcept {
	std::vector<mml::string> temp = {};

	for(uint32_t i = 0; i < this->vec.size(); i++) {
		if(this->vec[i].exist("--")) {
			temp.push_back(vec[i]);
			continue;
		}

		if(this->vec[i][0] != '-') {
			temp.push_back(vec[i]);
			continue;
		}

		bool added = false; // to tell that the value is added as it is part of the exceptions
		for(mml::string s : excepts) {
			if(vec[i] == s) {
				temp.push_back(vec[i]);
				added = true;
				break;
			}
		}
		if(added)
			continue;
		// Now, separate the options
		else {
				for(char c : vec[i].substr(1)) {
					temp.push_back((mml::string) "-" + mml::to_string(c));
				}
		}
	}
	this->vec = temp;
	return;
}




std::size_t mml::shell::arg::pos(const std::string& str) noexcept {
	for(std::size_t i = 0; i < vec.size() ; ++i)
		if(vec[i].getValue() == str)
			return i;
	return std::string::npos;
}
	
std::size_t mml::shell::arg::pos(const std::string& str1, const std::string& str2) noexcept {
	std::size_t pos1 = pos(str1);
	return pos1 < vec.size() ?  pos1 : pos(str2);
}

