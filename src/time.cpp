#include <chrono>
#include <cstdint>
#include <ostream>
#include <sstream>
#include <iomanip>


#include "mml/time.hpp"
#include "mml/standards.hpp"
#include "mml/shell.hpp"

std::chrono::high_resolution_clock::time_point mml::time::Timer::_now() const noexcept {
    return std::chrono::high_resolution_clock::now();
}

void mml::time::Timer::break_start() noexcept {
	// Check whether the timer is on a break
	if(this->timebreak) {
		mml::shell::warn_opt("[Timer::break_start] Timer already temporarily stopped!");
		return;
	}
	this->timebreak = true;
	break_time_mus = std::chrono::duration_cast<std::chrono::microseconds>(_now() - ticksStart).count() - break_time_mus;
	return;
}

void mml::time::Timer::break_stop() noexcept {
	// Check whether the timer is on a break
	if(!this->timebreak) {
		mml::shell::warn_opt("[Timer::break_stop] Timer is not temporarily stopped!");
		return;
	}
	this->timebreak = false;
	break_time_mus = std::chrono::duration_cast<std::chrono::microseconds>(_now() - ticksStart).count() - break_time_mus;
	return;
}

void mml::time::Timer::print(std::string text, bool format_print, bool newline) noexcept {
	ticksEnd = _now();
	std::cout << text;
	
	if(format_print)
		std::cout << range();
	else
		std::cout << stop() << " ms";
		
	if(newline)
		std::cout << std::endl;
	return;
}

void mml::time::Timer::start() noexcept {
	this->stopped = false;
    ticksStart = _now();
}

double mml::time::Timer::stop() noexcept {
    ticksEnd = _now();
    this->stopped = true;
    return ticks_to_double(this->ticksEnd, 1000.0);
}

std::chrono::high_resolution_clock::time_point mml::time::Timer::get_ticks(std::string option) {
	if(option == "start")
		return this->ticksStart;
	else if(option == "end") {
		if(!this->stopped)
			throw std::runtime_error("[Timer::get_ticks] Timer is still running");
		return this->ticksEnd;
	}
	else
		throw std::invalid_argument("[Timer::get_ticks] Type of time point undefined. Options are: \"start\" or \"end\"");

}

uint64_t mml::time::Timer::getUS() noexcept {
	std::chrono::high_resolution_clock::time_point ticks = _now();
	if(this->stopped)
		ticks = this->ticksEnd;
    return ticks_to_double(ticks);
}

double mml::time::Timer::getMS() noexcept {
	std::chrono::high_resolution_clock::time_point ticks = _now();
	if(this->stopped)
		ticks = this->ticksEnd;
	
	return ticks_to_double(ticks, 1000.0);
}

double mml::time::Timer::getS() noexcept {
	std::chrono::high_resolution_clock::time_point ticks = _now();
	if(this->stopped)
		ticks = this->ticksEnd;
    return ticks_to_double(ticks, 1.0e6);
}

std::string mml::time::Timer::str() {
	if(!this->stopped) {
		throw std::runtime_error("[Timer::str] Timer is still running");
	}
    return std::to_string(ticks_to_double(this->ticksEnd,1000.0)) + "ms";
}

int mml::time::Timer::toInt() {
	if(!this->stopped)
		throw std::runtime_error("[Timer::toInt] Timer is still running");
    return (int)(ticks_to_double(this->ticksEnd) + 0.5);
}


std::string mml::time::Timer::clock() noexcept{
	mml::time::time time = strct_clock();
	std::string ret = "";
	
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
	ret += "," + std::to_string(time.milliseconds);

	return ret;
}

std::string mml::time::Timer::range() noexcept {
	mml::time::time time = strct();
	
	if(time.microseconds < 10000)
		return std::to_string(time.microseconds) + " mus";
	if(time.milliseconds < 1000)
		return std::to_string(time.milliseconds) + " ms";
	if(time.second < 60 )
		return std::to_string(time.second).substr(0,5) + " s";
	else
		return clock();
}

mml::time::time mml::time::Timer::strct() {
	if(!this->stopped) {
		throw std::runtime_error("[Timer::strct] Timer is still running");
	}
	time time;

	// Compute how many seconds, µs, ms, ... are passed
	time.microseconds	= uint64_t(ticks_to_double(this->ticksEnd,1.0));
	time.milliseconds	= uint64_t(time.microseconds/1000);
	time.second			= uint64_t(time.milliseconds/1000);
	time.minute			= uint64_t(time.microseconds / (1000*60));
	time.hour			= uint64_t(time.microseconds / (1000*60*60));

	return time;
}

mml::time::time mml::time::Timer::strct_clock() {
	if(!this->stopped) {
		throw std::runtime_error("[Timer::strct_clock] Timer is still running");
	}

	mml::time::time time;

	// Convert the time in a clock format
	time.microseconds	= uint64_t(ticks_to_double(this->ticksEnd,1.0));
    time.milliseconds   = uint64_t(time.microseconds/1000);
	time.hour			= uint64_t(time.milliseconds / 1000 / 60 / 60);
	time.minute			= uint64_t(time.milliseconds / (1000*60) - time.hour * 60);
	time.second			= uint64_t(time.milliseconds / (1000) - time.minute * 60 - time.hour * 60 * 60);
	time.milliseconds	= uint64_t(time.milliseconds - time.second * 1000 - time.minute *1000 * 60 - time.hour *1000 * 60 * 60);
	time.microseconds	= uint64_t(time.microseconds - time.milliseconds*1000 - time.second * 1000000 - time.minute *1000000 * 60 - time.hour *1000000 * 60 * 60); 

	return time;
}

double mml::time::Timer::ticks_to_double(std::chrono::high_resolution_clock::time_point ticks, double f) noexcept {
	return std::chrono::duration_cast<std::chrono::microseconds>(ticks - this->ticksStart).count() / f - this->break_time_mus / f;
}



