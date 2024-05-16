#include <chrono>
#include <cstdint>
#include <ostream>
#include <sstream>
#include <iomanip>

#include "mml.hpp"
#include "Timer.hpp"



std::chrono::high_resolution_clock::time_point mml::Timer::_now() const noexcept {
    return std::chrono::high_resolution_clock::now();
}

void mml::Timer::break_start() {
			ticksEnd = _now();
			break_time_mus = std::chrono::duration_cast<std::chrono::microseconds>(ticksEnd - ticksStart).count() - break_time_mus;
}

void mml::Timer::break_stop() {
			ticksEnd = _now();
			break_time_mus = std::chrono::duration_cast<std::chrono::microseconds>(ticksEnd - ticksStart).count() - break_time_mus;
}

void mml::Timer::cout(std::string text, bool format_print, bool newline) {
	ticksEnd = _now();
	std::cout << text;
	
	if(format_print)
		std::cout << range();
	else
		std::cout << stop() << " ms";
	if(newline)
		std::cout << std::endl;
	
}

/**
 * Beginnt die Zeitmessung.
 * 
 * @author Lucas
 */
void mml::Timer::start() noexcept {
    ticksStart = _now();
}

/**
 * Stoppt die Zeitmessung.
 * 
 * @return Vergangene Zeit in Millisekunden
 * @author Lucas
 */
double mml::Timer::stop() noexcept {
    ticksEnd = _now();
    
    return std::chrono::duration_cast<std::chrono::microseconds>(ticksEnd - ticksStart).count() / 1000.0 - break_time_mus / 1000;
}

/**
 * Direkten Wert in Mikrosekunden zurückgegeben.
 * 
 * @return Vergangene Zeit in Mikrosekunden (uint64_t)
 * @author Lucas
 */
uint64_t mml::Timer::getUS(bool stop) noexcept {
	if(stop)
		ticksEnd = _now();
    return std::chrono::duration_cast<std::chrono::microseconds>(ticksEnd - ticksStart).count() - break_time_mus;
}

/**
 * Zwischenergebnis in ms zurückgegeben. (stop muss vorher aufgerufen werden)
 * 
 * @return Zwischenergebnis
 * @author Lucas
 */
double mml::Timer::getMS(bool stop) noexcept {
	if(stop)
		ticksEnd = _now();
	
	return std::chrono::duration_cast<std::chrono::microseconds>(ticksEnd - ticksStart).count() / 1000.0  - break_time_mus / 1000;
}

/**
 * Zwischenergebnis zurückgegeben.
 * 
 * @return Zwischenergebnis
 * @author Mike
 */
double mml::Timer::getS(bool stop) noexcept {
	if(stop)
		ticksEnd = _now();
	
    return std::chrono::duration_cast<std::chrono::microseconds>(ticksEnd - ticksStart).count() / 1000000.0 -  - break_time_mus / 1000000.0;
}

std::string mml::Timer::toString() noexcept {
    return std::to_string(stop()) + "ms";
}

int mml::Timer::toInt() noexcept {
    return (int)(stop() + 0.5);
}

struct mml::Timer::time{
	int hour;
	int minute;
	int second;
	int miliseconds;
	int microseconds;
};

std::string mml::Timer::clock() noexcept{
	double	ticks = stop();
	time 	time;
	std::string ret = "";
	
	time.hour = ticks / (1000*60*60);
	time.minute = ticks / (1000*60) - time.hour * 60;
	time.second = ticks / (1000) - time.minute * 60 - time.hour * 60 * 60;
	time.miliseconds = ticks -time.second * 1000 - time.minute *1000 * 60 - time.hour *1000 * 60 * 60; 
	
	// Formatierungen zur Form 00:00:00,000
	if(time.hour < 10)
		ret += "0" + std::to_string(time.hour);
	else
		ret += std::to_string(time.hour);
	ret += ":";
	
	if(time.minute < 10)
		ret += "0" + std::to_string(time.minute);
	else
		ret += std::to_string(time.minute);
	ret += ":";
	if(time.second < 10)
		ret += "0" + std::to_string(time.second);
	else
		ret += std::to_string(time.second);
	ret += "," + std::to_string(time.miliseconds);
	
	return ret;
}

std::string mml::Timer::range() noexcept {
	time time;
	time.miliseconds	= getMS();
	time.microseconds	= getUS(false);
	double second		= getS(false);
	
	if(time.microseconds < 10000)
		return std::to_string(time.microseconds) + " mus";
	if(time.miliseconds < 1000)
		return std::to_string(time.miliseconds) + " ms";
	if(second < 60 )
		return std::to_string(second).substr(0,5) + " s";
	else
		return clock();
}


		

std::ostream& operator<<(mml::Timer& t, std::ostream& os) {
    os << t.toString();
    
    return os;
}

mml::string mml::Time::to_date(time_t time) {
// 	tm* nun = gmtime(&time); // in UTC
	tm* nun = std::localtime(&time); // in localtime
	
	uint32_t u_year = (uint32_t) nun->tm_year+1900;	// Jahr
	uint32_t u_month = (uint32_t) nun->tm_mon+1;	// Monat
	uint32_t u_day = (uint32_t) nun->tm_mday;	// Tag
	uint32_t u_hour = (uint32_t) nun->tm_hour;	// Stunde
	uint32_t u_minute = (uint32_t) nun->tm_min;	// Minute
	uint32_t u_second = (uint32_t) nun->tm_sec;
	
	std::string year = std::to_string(u_year);
	std::string month = u_month > 9		?	std::to_string(u_month) : "0" + std::to_string(u_month);
	std::string day = u_day > 9 		?	std::to_string(u_day) : "0" + std::to_string(u_day);
	std::string hour = u_hour > 9		?	std::to_string(u_hour) : "0" + std::to_string(u_hour);
	std::string minute = u_minute > 9	?	std::to_string(u_minute) : "0" + std::to_string(u_minute);
	std::string second = u_second > 9	?	std::to_string(u_second) : "0" + std::to_string(u_second);
	
	mml::string date = day + "." + month + "." + year + " " + hour + ":" + minute + ":" + second;
	
	return date;
}

// NOTE TODO BETA
time_t mml::Time::to_time(std::string date) {
	std::istringstream date1(date);
	tm tm;
	date1 >> std::get_time(&tm,"%d.%m.%Y %H:%M:%S");
	double hour = std::atof(date.substr(date.find(' ')+1 , date.find(':')-date.find(' ')).c_str());
	if(tm.tm_hour != hour)
		tm.tm_hour = hour;
	time_t time = mktime(&tm);
	return time;
}

/*c
mml::EverySecTimer::EverySecTimer() : _prev(0) {
    _timer.start();
}

mml::EverySecTimer::~EverySecTimer() {
}

bool mml::EverySecTimer::run() {
    if(_timer.stop() > _prev + 1000.0) {
        _prev = _timer.getMS();
        
        return true;
    }
    else
        return false;
}
*/


