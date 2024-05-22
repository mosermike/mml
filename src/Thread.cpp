/**
 * @author Mike Moser
 * 
 * Programm: Thread.cpp
 * 
 * Enthält verschiedene Funktionen für Threads
 * 
*/
#include <iostream>
#include "mml/Thread.hpp"
#include "mml.hpp"


void mml::thread::Thread::thread_writing_true() {
	this->thread_writing_active = true;
}

void mml::thread::Thread::thread_writing_false() {
	this->thread_writing_active = false;
}

bool mml::thread::Thread::is_writing_active() { 
	return this->thread_writing_active;
}
	
	
void mml::thread::Thread::thread_sleep(float second) {
		std::this_thread::sleep_for(std::chrono::milliseconds((int) second * 1000));
}

void mml::thread::Thread::thread_sleep_millisecond(uint32_t millisecond) {
	std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));
}
	
bool mml::thread::Thread::waiting(int a) {
		
	while(this->is_writing_active()) {this->thread_sleep(0.1);}

	if( a == 0)
		this->thread_sleep_millisecond(i + mml::functions::get_random(1, max_i * 4) + mml::functions::get_random(1, max_i * 4));
	else
		this->thread_sleep_millisecond(a);
	
	while(this->is_writing_active()) { this->thread_sleep_millisecond(10 * mml::functions::get_random(1, max_i * 2)); }
	
	this->thread_writing_true();
	if( a == 0) {
		i++;
		if((i % max_i) == 0)
			i = 0;
	}
	return true;
}

/*bool waiting(int a) {
	
	while(this->is_writing_active()) {this->thread_sleep(0.1);}
	
	this->thread_sleep_millisecond(a);
			
	while(this->is_writing_active()) {this->thread_sleep(0.01);}
			
	this->thread_writing_true();
	
	return true;
}*/

// sleep function
void mml::thread::sleep(float s) {
	std::this_thread::sleep_for(std::chrono::milliseconds((int)(s * 1000)));
}
