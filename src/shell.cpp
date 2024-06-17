/**
 * @author Mike Moser
 * 
 * Programm shell.cpp
 * Enthält verschiedene Funktionen
 * 
*/ 

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unistd.h> // getpass
#include <chrono>  //sleep function
#include <thread>

#include "mml/definitions.hpp"
#include "mml/shell.hpp"
#include "mml.hpp"

//FORMATIERUNGEN DER SHELL ÄNDERN:
/*
namespace functions{
	class string;
}*/
void mml::shell::letter(mml::string colour) {
//DEFINITION
    std::map<std::string , std::string > letter;
    
//BUCHSTABENFARBEN
	letter[ "black" ] = "30";
	letter[ "darkgray" ] = "1;30";
	letter[ "red" ] = "31";
	letter[ "lightred" ] = "1;31";
	letter[ "green" ] = "32";
	letter[ "lightgreen" ] = "1;32";
	letter[ "brown" ] = "33";
	letter[ "yellow" ] = "1;33";
	letter[ "blue" ] = "34";
	letter[ "lightblue" ] = "1;34";
	letter[ "purple" ] = "35";
	letter[ "lightpurple" ] = "1;35";
	letter[ "cyan" ] = "36";
	letter["lightcyan" ] = "1;36";
	letter[ "white" ] = "37";
	letter[ "lightgray" ] = "1;37";
	letter[ "normal" ] = "0";

	if ( letter[colour.getValue()] == "" ){
		std::cout << "Your colour doesn't exist or something went wrong." << "\nPlease check the uncompiled file, if available. Otherwise use another code for the colour!" << std::endl;
		return;
	}
	
	std::cout << "\e[" << letter[colour.getValue()] << "m";
}

void mml::shell::formation(mml::string format1) {

	//DEFINITION
	std::map < std::string , int > format;

	//Options
    format [ "normal" ] = 0;
	format [ "fat" ] = 1;
	format [ "cursive" ] = 2;          //Kursiv
    format [ "underline"] = 4;
    format[ "blink" ] = 5;
    //format[ "rblink" ] = 25;
    format[ "reverse" ] = 7;
   // format[ "rreverse" ] = 27;
	
	if ( format[format1.getValue()] == 0 && format1 != "normal" ) {
		std::cout << "Your colour doesn't exist or something went wrong." << "\nPlease check the uncompiled file, if available. Otherwise use another code for the colour!" << std::endl;
		return;
	}
	std::cout << "\e[" << format[format1.getValue()] << "m";
}
void mml::shell::background(mml::string colour) {

	//DEFINITION
    std::map < std::string , uint32_t > background;

	//HINTERGRUNDFARBEN
	background[ "black" ] = 40;
    background[ "red" ] = 41;
    background[ "green" ] = 42;
    background[ "brown" ] = 43;
    background[ "blue" ] = 44;
    background[ "purple" ] = 45;
    background[ "cyan" ] = 46;
    background[ "gray" ] = 47;		//=^weiß
    background[ "normal" ] = 49;
	
	if ( background[colour.getValue()] == 0 ){
		std::cout << "Your colour doesn't exist or something went wrong." << "\nPlease check the uncompiled file, if available. Otherwise use another code for the colour!" << std::endl;
		return;
	}
	std::cout << "\e[" << background[colour.getValue()] << "m";
}

// Kapitel hinzufügen bei einer Hilfeseite
void mml::shell::chapter(std::string text,bool newline){
	mml::shell::letter("lightgray");
	std::cout << text;
	if(newline)
		std::cout << std::endl;
	mml::shell::normal();
}

void mml::shell::cout(mml::string text, bool newline, std::string colour) {
	mml::string output = "";
	// kein [ vorhanden => normale Ausgabe
	if(!text.exist("["))
		std::cout << text;
	else {
		// Wert vor [ finden und ausgeben
		std::size_t temp = text.find("[");
		if(temp != 0) {
			output = text.sub(0,temp-1);
			text = text.replace(output, "");
			std::cout << output;
		}
		// Farbe ändern
		mml::shell::letter(colour);
		
		// Ende der Klammer finden
		temp = text.find("]");
		output = text.sub(0,temp+1);
		text = text.replace(output,"");
		std::cout << output;
		mml::shell::normal();
		std::cout << text;
	}
	
	if(newline)
		std::cout << std::endl;
}

void mml::shell::normal(){
	std::cout << "\e[0m";
}

void mml::shell::note(std::string text, bool newline) {
	mml::shell::letter("lightgray");
	std::cout << text;
	mml::shell::normal();
	if(newline)
		std::cout << std::endl;
	mml::shell::normal();
}



// Eine Option hinzufügen bei einer Hilfeseite
void mml::shell::option(std::string chapter,std::string option){
	mml::shell::letter("lightgray");
	std::cout << "\t" << chapter << std::endl;
	mml::shell::normal();
	std::cout << "\t\t" << option << std::endl;
}

// Warnungen für Programme, wenn etwas nicht geht
void mml::shell::warn(std::string text,bool newline){
	mml::shell::letter("red");
	std::cout << text;
	if(newline)
		std::cout << std::endl;
	mml::shell::normal();
	exit(EXIT_FAILURE);
}

// Warnungen um Hinweise weiterzugeben/ auszugeben
void mml::shell::warn_opt(std::string text,bool newline){
	mml::shell::letter("red");
	std::cout << text;
	mml::shell::normal();
	if(newline)
		std::cout << std::endl;
	mml::shell::normal();
}

void mml::shell::error(std::string text){
	mml::shell::letter("red");
	std::cout << text<< std::endl;
	mml::shell::normal();
	exit(EXIT_FAILURE);
}

extern mml::string mml_pass;

// Passwort von der Shell lesen
std::string mml::shell::password(std::string print, std::string add){
	std::string data = print + add + ": ";
	mml_pass = getpass(data.c_str());
	return mml_pass.str();
}








