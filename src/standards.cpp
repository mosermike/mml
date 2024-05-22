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
#include <ctime>
#include <algorithm>	// std::replace
#include <sys/mount.h>
#include <signal.h>

#include "mml/standards.hpp"
#include "mml/functions.hpp"
#include "mml/definitions.hpp"
#include "mml/Unix.hpp"

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

bool mml::check_root(std::string programme){
	static bool check = false;
	// für log und keine doppelte Überprüfung
	if(!check)
		check = true;
	else
		return 1;

	mml::Unix::User user;
	mml::log log(_check_root_log);
	
	
	if ( user.get_user().str() != "root" ){
		pid_t parent_pid = getppid();
		
		// call from another c++ programme
		if(mml::Unix::get_process_name_by_pid(parent_pid) == "bash"){
			log.cout("[check_root] " + programme + " failed at " + mml::date("Date+Time") + ".", true);
			

			shell::warn_opt("[check_root] This script must be run as root! Your actual user is " + user.get_user().str() + ".",true);
			exit(EXIT_FAILURE);
		}
		
		// Call from the terminal
		else {
			log.cout("[check_root] " + programme  + " failed at " + mml::date("Date+Time") + ".", true);
			shell::warn_opt("[check_root] This script must be run as root! Your actual user is " + user.get_user().str() + ".",true);
			exit(EXIT_FAILURE);
		}
	}
	log.cout("[check_root] " + programme  + " accepted at " + mml::date("Date+Time") + ".", true);
	return false;
}



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

 std::string mml::date(mml::string value, std::string separator1, std::string separator2){
		std::string year = std::to_string(mml::date(_year)); // Get actual year

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


		switch(mml::functions::const_string_hash(value.c_str())) {
			
			case mml::functions::const_string_hash("Date") :	// YY.MM.DD
				return year + separator2 + month + separator2 + day;
			
			case mml::functions::const_string_hash("Time") :	// HH:MM:SS
				return hour + separator1 + minute + separator1 + second; 
			
			case mml::functions::const_string_hash("Date+Time") :	// DD MM YYYY HH:MM:SS
				return day + separator2 + month + separator2 + year + " " + hour + separator1 + minute + separator1 + second;
			
			case mml::functions::const_string_hash("Date1+Time") :	// YYYY MM DD HH:MM:SS
				return year + separator2 + month + separator2 + day + " " + hour + separator1 + minute + separator1 + second; 
			
			default:
				return year + separator2 + month + separator2 + day;
		}
		return "";
}

bool mml::is_num(char c) {return ((int) c >= 48 && (int) c <= 57) ? true : false;}

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

