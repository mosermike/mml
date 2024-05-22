#include <chrono>
#include <cstdint>
#include <ostream>
#include <sstream>
#include <iomanip>


#include "mml/Timer.hpp"
#include "mml/standards.hpp"


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



