/**
 * @file standards.cpp
 * @author Mike Moser
 * @brief Contains different standard functions of this library
 * @version 1.0
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>		// fsync(),stdin_fileno,getpass
#include <ctime>
#include <algorithm>	// std::replace
#include <signal.h>

//#include "mml/thread.hpp"
#include "mml/definitions.hpp"
#include "mml/Unix.hpp"
#include "mml/logger.hpp"


bool mml::check_root(std::string programme, mml::string logpath){
	static bool check = false;
	// für log und keine doppelte Überprüfung
	if(!check)
		check = true;
	else
		return 1;

	mml::Unix::User user;
	
	mml::log log;
	if(logpath != "") {
		log.set_path(logpath);
		log.open();
	}
	
	
	if ( user.get_user().str() != "root" ){
		if(logpath != "")
			log << ("[check_root] " + programme + " failed at " + mml::date(-1, "Date+Time") + ".") << std::endl;
		throw std::runtime_error("[check_root] This script must be run as root! Your actual user is " + user.get_user().str() + ".");
		
	}
	
	if(logpath != "")
		log << ("[check_root] " + programme  + " accepted at " + mml::date(-1, "Date+Time") + ".") << std::endl;

	log.close();
	
	return false;
}



// Uhrzeit:
uint32_t mml::date(int info, time_t time1) noexcept {
	switch(info) {
		case _sec:  logdebug("Get seconds of the time " + std::to_string(time1)); break;
		case _min:  logdebug("Get minutes of the time " + std::to_string(time1)); break;
		case _hour:  logdebug("Get hours of the time " + std::to_string(time1)); break;
		case _day:  logdebug("Get day of the time " + std::to_string(time1)); break;
		case _month:  logdebug("Get month of the time " + std::to_string(time1)); break;
		case _year:  logdebug("Get year of the time " + std::to_string(time1)); break;
		case _st1:  logdebug("Get summertime of the time " + std::to_string(time1)); break;
		case _weekday:  logdebug("Get days since sunday of the time " + std::to_string(time1)); break;
		case _yearday:  logdebug("Get days since New Year of the time " + std::to_string(time1)); break;
		case _kw:  logdebug("Get week number of the time " + std::to_string(time1)); break;
		default: logerror("Desired information option " + std::to_string(info) + " not defined"); break;
	}

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
    
	uint32_t time_info = 0;
	switch(info){
		case _sec:  time_info = (uint32_t) nun->tm_sec; break;
		case _min:  time_info = (uint32_t) nun->tm_min; break;	// Minute
		case _hour: time_info = (uint32_t) nun->tm_hour; break;	// Stunde
		case _day:  time_info = (uint32_t) nun->tm_mday; break;	// Tag
		case _month:time_info = (uint32_t) nun->tm_mon+1; break;	// Monat
		case _year: time_info = (uint32_t) nun->tm_year+1900; break;	// Jahr
		case _st1:  time_info = (uint32_t) nun->tm_isdst; break;	// Summertime
		case _weekday: time_info = (uint32_t) nun->tm_wday; break;	// Tage seit Sonntag
		case _yearday: time_info = (uint32_t) nun->tm_yday; break;	// Tage seit Neujahr
		case _kw:   time_info = (uint32_t) (nun->tm_yday + DAYS_PER_WEEK - delta ) / DAYS_PER_WEEK; break;	// week number
		default: time_info =  0; break;
	}
	logdebug("Determined value: " + std::to_string(time_info));

	return time_info;
}

std::string mml::date(time_t time1, mml::string value, std::string separator1, std::string separator2) noexcept {
		std::string year = std::to_string(mml::date(_year,time1)); // Get actual year

		uint32_t info = _month;
			std::string month = mml::date(info,time1) > 9		?	std::to_string(mml::date(info,time1)) : "0" + std::to_string(mml::date(info,time1));
		info = _day;
			std::string day = mml::date(info,time1) > 9 		?	std::to_string(mml::date(info,time1)) : "0" + std::to_string(mml::date(info,time1));
		info = _hour;
			std::string hour = mml::date(info,time1) > 9		?	std::to_string(mml::date(info,time1)) : "0" + std::to_string(mml::date(info,time1));
		info = _min;
			std::string minute = mml::date(info,time1) > 9	?	std::to_string(mml::date(info,time1)) : "0" + std::to_string(mml::date(info,time1));
		info = _sec;
			std::string second = mml::date(info,time1) > 9	?	std::to_string(mml::date(info,time1)) : "0" + std::to_string(mml::date(info,time1));	


		switch(mml::const_string_hash(value.c_str())) {
			
			case mml::const_string_hash("Date") :	// YY.MM.DD
				return year + separator2 + month + separator2 + day;
			
			case mml::const_string_hash("Time") :	// HH:MM:SS
				return hour + separator1 + minute + separator1 + second; 
			
			case mml::const_string_hash("Date+Time") :	// DD MM YYYY HH:MM:SS
				return day + separator2 + month + separator2 + year + " " + hour + separator1 + minute + separator1 + second;
			
			case mml::const_string_hash("Date1+Time") :	// YYYY MM DD HH:MM:SS
				return year + separator2 + month + separator2 + day + " " + hour + separator1 + minute + separator1 + second; 
			
			default:
				return year + separator2 + month + separator2 + day;
		}
		return "";
}

bool mml::isnum(char c) noexcept {return ((int) c >= 48 && (int) c <= 57) ? true : false;}

bool mml::range(std::size_t number) noexcept {
	return number < std::string::npos ? true : false;
}

bool mml::range(std::size_t number1, std::size_t number2) noexcept {
	return range(number1) || range(number2);
}

double mml::round(double number, uint16_t digit) noexcept {
    double temp = number*std::pow(10,digit);
    int64_t temp1 = (int) (number*(std::pow(10,digit+1)));
    if (temp1 % 10 > 4)
        return (double) (((int) (temp+1.0))/std::pow(10,digit));
    else
        return ((int) temp)/std::pow(10,digit);
}

std::string mml::declare_month(int month_nr) noexcept {
	switch(month_nr) {
		case(1) :	return "January";
		case(2) :	return "February";
		case(3) :	return "March";
		case(4) :	return "April";
		case(5) :	return "Mai";
		case(6) :	return "June";
		case(7) :	return "July";
		case(8) :	return "August";
		case(9) :	return "September";
		case(10) :	return "Oktober";
		case(11) :	return "November";
		case(12) :	return "December";
		default  :	return "";
	}
}

std::size_t mml::digits(double number) noexcept {
	mml::string temp = mml::to_string(number);

	// Correction if number is an integer
	if(temp[temp.size()-1]== '.')
		temp = temp.sub(0,temp.size()-2);
	
	return temp.size();
}



template <typename templ> templ mml::get_random(templ min, templ max) noexcept {
	
	std::random_device rd;     // only used once to initialise (seed) engine
	
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	
	std::uniform_int_distribution<templ> uni(min,max); // guaranteed unbiased

	return uni(rng);
}

/*
std::vector<double> Get_Values( std::string filepath, double min_value) {
	
	std::vector<double> values;
	std::string 		value 	= "";
	std::size_t			pos		= 0;
	double 				value1	= 0;
	//Öffne die Datei:
	std::fstream input(filepath);
    
	
    // Check if the file was opened
    if ( !input ){
		throw std::runtime_error("file not found");
	}
    
	// Read the text line by line
	while (! input.eof()){
		std::getline(input, value );
		
		pos = value.find("=");
		
		value = value.substr (pos+1);
		value1 = std::atof(value.c_str());
	
		if (abs(value1) >= abs(min_value) )	// Minmum this value
			values.push_back(value1);
    }
    
    return values;
}

std::string mml::lower(std::string input) noexcept {

	for(uint16_t i = 0; i < (uint16_t) input.size(); i++)
		input[i] = tolower(input[i]);
	return input;

}

*/

mml::string operator+(const char* lhs, const mml::string& rhs) noexcept {
        std::string temp(lhs); // Convert lhs (const char*) to std::string
        temp += rhs.str();     // Concatenate with the internal string of rhs
        return mml::string(temp); // Return a new mml::string
}

std::string mml::random_str(size_t letters, std::string start) noexcept {
	
	for(uint32_t i = 0; i < letters; i++)
		start += static_cast<char> (mml::get_random(97,122));
	
	return start;
}

template <typename templ> templ mml::smallest_num(std::vector<templ> values, std::size_t pos) {
	if(!std::is_arithmetic_v<templ>)
		throw std::logic_error("[smallest_num] Vector type is not arithmetic!");
		
	std::sort(values.begin(), values.end());
	return values[pos];
}

mml::string mml::timeformat(time_t time1, mml::string format) noexcept {
	logdebug("Convert time " + std::to_string(time1) + " into the format " + format.str());
	
	std::string year = "";
	std::string month = "";
	std::string day = "";
	std::string hour = "";
	std::string minute = "";
	std::string second = "";

	if (format.exist("$YY"))
		year = std::to_string(mml::date(_year,time1)); // Get actual year

	if (format.exist("$MM"))
		month = mml::date(_month,time1) > 9		?	std::to_string(mml::date(_month,time1)) : "0" + std::to_string(mml::date(_month,time1));
	if (format.exist("$DD"))
		day = mml::date(_day,time1) > 9 		?	std::to_string(mml::date(_day,time1)) : "0" + std::to_string(mml::date(_day,time1));
	if (format.exist("$hh"))
		hour = mml::date(_hour,time1) > 9		?	std::to_string(mml::date(_hour,time1)) : "0" + std::to_string(mml::date(_hour,time1));
	if (format.exist("$mm"))
		minute = mml::date(_min,time1) > 9	?	std::to_string(mml::date(_min,time1)) : "0" + std::to_string(mml::date(_min,time1));
	if (format.exist("$ss"))
		second = mml::date(_sec,time1) > 9	?	std::to_string(mml::date(_sec,time1)) : "0" + std::to_string(mml::date(_sec,time1));	


	format = format.replace("$YYYY",year);
	format = format.replace("$YY",year.substr(2));
	format = format.replace("$MM",month);
	format = format.replace("$DD",day);
	format = format.replace("$hh",hour);
	format = format.replace("$mm",minute);
	format = format.replace("$ss",second);

	loginfo("Time " + std::to_string(time1) + " converted to the time " + format.str() + " UTC");
	return format;
}