/**
 * @author Mike Moser
 * 
 * Quelldatei args.cpp
 * Enthält verschiedene Funktionen für die Klasse arg
 * 
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "mml/functions.hpp"
#include "mml/shell.hpp"
#include <limits>

// Überprüfen, ob ein Argument mit einem bestimmten String anfängt
std::size_t mml::shell::arg::beginArg(const std::string& str) {
	for(std::size_t i = 0; i < vec.size() ; ++i)
		for(std::size_t a = 0; a < (vec[i]).size() ; a++)
			if(vec[i].substr(0,a) == str)
				return i;
	return std::string::npos;
}

bool mml::shell::arg::exist(std::string search) {
	bool exist = false;
	for(uint32_t i = 0; i < vec.size(); i++) {
		exist = vec[i].exist(search);
		if(exist)
			return true;
	}
	return false;
}

bool mml::shell::arg::exist(std::string search1, std::string search2) {
	return exist(search1) || exist(search2);
}

bool mml::shell::arg::exist(std::string search1, std::string search2, std::string search3) {
	return exist(search1) || exist(search2) || exist(search3);
}

bool mml::shell::arg::exist(std::string search1, std::string search2, std::string search3, std::string search4) {
	return exist(search1) || exist(search2) || exist(search3) || exist(search4);
}

bool mml::shell::arg::exist(std::size_t pos, std::string search) {
	if(pos >= vec.size() || pos == 0)		// wenn nicht vorhanden
		return false;
	return vec[pos].find(search) < std::string::npos ? true : false;
}

bool mml::shell::arg::findArg(const std::string& str) {
	//if (vec.size() < 2)
	//	mml::shell::warn_opt("[findArg] Arguments only consists of the executioning program");
	for(uint32_t i = 0; i < vec.size() ; ++i)
		if(vec[i].getValue() == str)
			return true;
	return false;
}

bool mml::shell::arg::findArg(const std::string& str1,const std::string& str2) {
	return findArg(str1) || findArg(str2); 
}

bool mml::shell::arg::findArg(const std::string& str1,const std::string& str2, const std::string& str3) {
	return findArg(str1) || findArg(str2) || findArg(str3);
}

bool mml::shell::arg::findArg(const std::string& str1,const std::string& str2, const std::string& str3, const std::string& str4) {
	return findArg(str1) || findArg(str2) || findArg(str3) || findArg(str4);
}

void mml::shell::arg::getArg(std::string except1, std::string except2, std::string except3, std::string except4, std::string except5, std::string except6, std::string except7) {
	
	std::vector<mml::string> temp;
	
	mml::functions::erase(temp);

	// - entfernen
	except1 = except1.substr(1);
	except2 = except2.substr(1);
	except3 = except3.substr(1);
	except4 = except4.substr(1);
	except5 = except5.substr(1);
	except6 = except6.substr(1);
	except7 = except7.substr(1);
	
	
	static bool ex1 = false;
	static bool ex2 = false;
	static bool ex3 = false;
	static bool ex4 = false;
	static bool ex5 = false;
	static bool ex6 = false;
	static bool ex7 = false;
	
	if(except1 == "xxxxx")
		ex1 = true;
	if(except2 == "xxxxx")
		ex2 = true;
	if(except3 == "xxxxx")
		ex3 = true;
	if(except4 == "xxxxx")
		ex4 = true;
	if(except5 == "xxxxx")
		ex5 = true;
	if(except6 == "xxxxx")
		ex6 = true;
	if(except7 == "xxxxx")
		ex7 = true;

	// alle excepts bearbeiten:
	if(!ex1 || !ex2 || !ex3 || !ex4 || !ex5 || !ex6 || !ex7) {
		for(uint32_t i = 1; i < this->vec.size(); i++) {
			if(this->vec[i].exist("--"))
				continue;
			if(this->vec[i][0] != '-')
				continue;
			if(!ex1 && this->vec[i].exist(except1)) {
				replace(except1,"");
				push_back("-" + except1);
				ex1 = true;
			}
			if(!ex2 && this->vec[i].exist(except2)) {
				replace(except2,"");
				push_back("-" + except2);
				ex2 = true;
			}
			if(!ex3 && this->vec[i].exist(except3)) {
				replace(except3,"");
				push_back("-" + except3);
				ex3 = true;
			}
			if(!ex4 && this->vec[i].exist(except4)) {
				replace(except4,"");
				push_back("-" + except4);
				ex4 = true;
			}
			if(!ex5 && this->vec[i].exist(except5)) {
				replace(except5,"");
				push_back("-" + except5);
				ex5 = true;
			}
			if(!ex6 && this->vec[i].exist(except6)) {
				replace(except6,"");
				push_back("-" + except6);
				ex6 = true;
			}
			if(!ex7 && this->vec[i].exist(except7)) {
				replace(except7,"");
				push_back("-" + except7);
				ex7 = true;
			}
			if(ex1 && ex2 && ex3 && ex4 && ex5 && ex6 && ex7)
				break;
		}

	}
	
	// Befehl speichern(0. Parameter):
	temp.push_back(this->vec[0]);
	
	// alle Parametern trennen:
	for(uint32_t i = 1; i < size(); i++) {
		// Langform angegeben:
		if(this->vec[i].exist("--")) {
			temp.push_back(this->vec[i]);
			continue;
		}
		
		// Args nur ein Minus => Nicht verwendbar
		else if(this->vec[i] == "-")
			continue;
		
		// nur ein Zeichen:
		else if(this->vec[i].size() < 2) {
			temp.push_back(this->vec[i]);
			continue;
		}
		
		// Ist ein except => am Ende angekommen:
		else if(this->vec[i] == "-" + except1 || this->vec[i] == "-" + except2 || this->vec[i] == "-" + except3 || this->vec[i] == "-" +  except4 || this->vec[i] == "-" +  except5 || this->vec[i] == "-" +  except6 || this->vec[i] == "-" +  except7) {
				for(uint32_t a = i; a < size(); a++)
					temp.push_back(this->vec[a]);
				break;
		}
				
		else if(this->vec[i][0] == '-' && this->vec[i][1] != '-' && this->vec[i].size() > 2) {
			for(uint32_t a = 1; a < this->vec[i].size(); a++)
				temp.push_back("-" + this->vec[i].substr(a,1).str());
		}
		else
			temp.push_back(this->vec[i]);
		
	}

	this->vec = temp;
		
}

void mml::shell::arg::init(std::string except1, std::string except2, std::string except3, std::string except4, std::string except5, std::string except6, std::string except7) {
	getArg(except1, except2, except3, except4, except5,except6, except7);
}

bool mml::shell::arg::notArg (const std::string& str1){
	for(uint32_t i = 0; i < vec.size() ; ++i)
		if(vec[i].getValue() == str1)
			return false;
	return true;
}

bool mml::shell::arg::notArg(const std::string& str1,const std::string& str2) {
	return notArg(str1) && notArg(str2);
}

bool mml::shell::arg::notArg(const std::string& str1,const std::string& str2, const std::string& str3) {
	return notArg(str1) && notArg(str2) && notArg(str3);
}

bool mml::shell::arg::notArg(const std::string& str1,const std::string& str2, const std::string& str3, const std::string& str4) {
	return notArg(str1,str2) && notArg(str3, str4);
}

std::size_t mml::shell::arg::positionArg(const std::string& str) {
	for(std::size_t i = 0; i < vec.size() ; ++i)
		if(vec[i].getValue() == str)
			return i;
	return std::string::npos;
}
	
std::size_t mml::shell::arg::positionArg(const std::string& str, const std::string& str2) {
	std::size_t pos = positionArg(str);
	return pos < vec.size() ?  pos : positionArg(str2);
}


std::vector<mml::string> mml::shell::arg::replace (char sign_old, char sign_new){

	for(uint32_t i = 0; i < vec.size(); i++)
		vec[i] = vec[i].replace(sign_old,sign_new);

	return vec;
}
    
std::vector<mml::string> mml::shell::arg::replace(std::string str_old, std::string str_new){

	for(uint32_t i = 0; i < vec.size(); i++)
		vec[i] = vec[i].replace(str_old,str_new);

	return vec;
}

void  mml::shell::arg::sort(){
	
	std::vector<std::string> temp = str_change();
	std::sort(temp.begin(),temp.end());
	tostr(temp);
	
}

std::vector<mml::string> mml::shell::arg::str(){
	return this->vec;
}

std::vector<std::string> mml::shell::arg::str_change(){

	std::vector<std::string> temp;
	
	for(uint32_t i = 0; i < vec.size(); i++)
			temp.push_back(vec[i].str());
	return temp;
}

std::vector<mml::string> mml::shell::arg::tostr(std::vector<std::string> temp){
	if(!empty())
		del();
	for(uint32_t i = 0; i < temp.size(); i++)
		push_back(temp[i]);
	return vec;
}


std::vector<mml::string> &mml::shell::arg::operator()(int argc1, char **argv1, bool getarg) {

	std::vector<mml::string> vec_temp(argv1,argv1 + argc1);	
	vec = vec_temp;
	
	if(getarg)
		getArg();
	
	return vec;
}

std::vector<mml::string> &mml::shell::arg::operator()(char **argv1, int argc1, bool getarg) {

	std::vector<mml::string> vec_temp(argv1,argv1 + argc1);	
	vec = vec_temp;

	if(getarg)
		getArg();
	
	return vec;
}
