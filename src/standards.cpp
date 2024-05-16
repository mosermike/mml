/**
 * @author Mike Moser
 * 
 * @name standards.cpp
 * Enthält verschiedene Standardfunktionen
 * 
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>		// fsync(),stdin_fileno,getpass
#include <definitions.hpp>
#include <algorithm>	// std::replace
#include <sys/mount.h>
#include <signal.h>

#include <mml.hpp>
#include "standards.hpp"


// bool mml::atob(const char* a) {
// 	 return (std::atoi(a) > 0) ? true : false;
// }
// 
// bool mml::atob(int a) {
// 	 return (a == 0) ? false : true;
// }

// double mml::atof(std::string value)  {
// 	return std::atof(value.c_str());
// }

// int mml::atoi(std::string value)  {
// 	return std::atoi(value.c_str());
// }

//ROOT ÜBERPRÜFEN
bool mml::check_root(mml::shell::arg args){
	static bool check = false;
	// für log und keine doppelte Überprüfung
	if(!check)
		check = true;
	else
		return 1;
	mml::Unix::User user;
	mml::log log(_check_root_log);
	mml::string programm = args[0];
	
	if ( user.get_user().str() != "root" ){
		pid_t parent_pid = getppid();
		
		// bei Aufruf aus einem anderen C++ Programm
		if(mml::Unix::get_process_name_by_pid(parent_pid) == "bash"){
			if(programm.str() != "./a.out")
				log.cout("[check_root] " + programm.str() + " failed at " + mml::date("Datum+Uhrzeit") + ".", true);
			else
				log.cout("[check_root] " + user.get_pwd().str() + "/a.out failed at " + mml::date("Datum+Uhrzeit") + ".", true);

			shell::warn_opt("ERROR: this script must be run as root! Your actual user is " + user.get_user().str() + ".",true);
			kill(getpid(),SIGTERM);
		}
		
		// bei Aufruf aus Konsole oder von bash Skript
		else {
			log.cout("[check_root] " + programm.str() + " failed at " + mml::date("Datum+Uhrzeit") + ".", true);
			shell::warn_opt("ERROR: this script must be run as root! Your actual user is " + user.get_user().str() + ".",true);
			kill(parent_pid,SIGTERM);
		}
	}
	log.cout("[check_root] " + programm.str() + " accepted at " + mml::date("Datum+Uhrzeit") + ".", true);
	return false;
}

template <typename T> void mml::cout (std::vector<T> const& vec){
	for(uint32_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << std::endl;    //Ausgabe aller Werte
	}
template void mml::cout<int> (std::vector<int> const& vec);
template void mml::cout<double> (std::vector<double> const& vec);
template void mml::cout<float> (std::vector<float> const& vec);
template void mml::cout<uint32_t> (std::vector<uint32_t> const& vec);
template void mml::cout<uint64_t> (std::vector<uint64_t> const& vec);
template void mml::cout<mml::string> (std::vector<mml::string> const& vec);
template void mml::cout<std::string> (std::vector<std::string> const& vec);

// Uhrzeit:
uint32_t mml::date(int info, time_t time1){
	
	std::tm*		nun;
	if(time1 == -1) {
		std::time_t t = std::time(0);   // get time now
		nun = std::localtime(&t);
	}
    else
		nun = std::gmtime(&time1);
	
	constexpr int DAYS_PER_WEEK = 7 ;

    const int wday = nun->tm_wday ;
    const int delta = wday ? wday-1 : DAYS_PER_WEEK-1 ;
    
	
	switch(info){
		case _sec:  return (uint32_t) nun->tm_sec;
		case _min:  return (uint32_t) nun->tm_min;	// Minute
		case _hour:  return (uint32_t) nun->tm_hour;	// Stunde
		case _day:  return (uint32_t) nun->tm_mday;	// Tag
		case _month:  return (uint32_t) nun->tm_mon+1;	// Monat
		case _year:  return (uint32_t) nun->tm_year+1900;	// Jahr
		case _st1:  return (uint32_t) nun->tm_isdst;	// Summertime
		case _weekday:  return (uint32_t) nun->tm_wday;	// Tage seit Sonntag
		case _yearday:  return (uint32_t) nun->tm_yday;	// Tage seit Neujahr
		case _kw:  return (uint32_t) (nun->tm_yday + DAYS_PER_WEEK - delta ) / DAYS_PER_WEEK;	// week number
		default: return 0;
	}
}

std::string mml::date(mml::string value, std::string trennzeichen1, std::string trennzeichen2) {


	std::string year = std::to_string(mml::date(_year)); // Get actual year
	// Da ansonsten zum Beispiel 2 anstatt 02 ausgegeben wird
	// Werte bilden
	uint32_t info = _month;
		std::string month = mml::date(info) > 9		?	std::to_string(mml::date(info)) : "0" + std::to_string(mml::date(info));
	info = _day;
		std::string day = mml::date(info) > 9 		?	std::to_string(mml::date(info)) : "0" + std::to_string(mml::date(info));
	info = _hour;
		std::string hour = mml::date(info) > 9		?	std::to_string(mml::date(info)) : "0" + std::to_string(mml::date(info));
	info = _min;
		std::string minute = mml::date(info) > 9	?	std::to_string(mml::date(info)) : "0" + std::to_string(mml::date(info));
	info = _sec;
		std::string second = mml::date(info) > 9	?	std::to_string(mml::date(info)) : "0" + std::to_string(mml::date(info));	

	switch(value.hash()) {
		
		case mml::functions::const_string_hash("Datum") :	// YY.MM.DD
			return year + trennzeichen2 + month + trennzeichen2 + day;
		
		case mml::functions::const_string_hash("Uhrzeit") :	// HH:MM:SS
			return hour + trennzeichen1 + minute + trennzeichen1 + second; 
		
		case mml::functions::const_string_hash("Datum+Uhrzeit") :	// DD MM YYYY HH:MM:SS
			return day + trennzeichen2 + month + trennzeichen2 + year + " " + hour + trennzeichen1 + minute + trennzeichen1 + second;
		
		case mml::functions::const_string_hash("Datum1+Uhrzeit") :	// YYYY MM DD HH:MM:SS
			return year + trennzeichen2 + month + trennzeichen2 + day + " " + hour + trennzeichen1 + minute + trennzeichen1 + second; 
		
		default:
			return year + trennzeichen2 + month + trennzeichen2 + day;
	}
}

bool mml::range(std::size_t number) {
	return number < std::string::npos ? true : false;
}

bool mml::range(std::size_t number1, std::size_t number2) {
	return range(number1) || range(number2);
}

double mml::round(double number, uint16_t digit) {
    double temp = number*std::pow(10,digit);
    int64_t temp1 = (int) (number*(std::pow(10,digit+1)));
    if (temp1 % 10 > 4)
        return (double) (((int) (temp+1.0))/std::pow(10,digit));
    else
        return ((int) temp)/std::pow(10,digit);
}
// mml::string mml::to_string(char value) {
// 	return ((mml::string) (std::to_string(value)));
// }
// mml::string mml::to_string(char* value) {
// 	return ((mml::string) (std::to_string(*value)));
// }
// mml::string mml::to_string(double value) {
// 	return ((mml::string) (std::to_string(value)));
// }
// mml::string mml::to_string(float value) {
// 	return ((mml::string) (std::to_string(value)));
// }
// mml::string mml::to_string(int value) {
// 	return ((mml::string) (std::to_string(value)));
// }
// mml::string mml::to_string(std::string value) {
// 	return ((mml::string) (value));
// }
// mml::string mml::to_string(uint value) {
// 	return ((mml::string) (std::to_string(value)));
// }
// 
// // mml::string mml::to_string(mml::string value) {
// // 	return value;
// // }
// 
// mml::string mml::to_string(uint64_t value) {
// 	return ((mml::string) (std::to_string(value)));
// }
