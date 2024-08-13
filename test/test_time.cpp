/**
 * Performing test for tthe class arguments
*/
#include <iostream>
#include <unistd.h> // for sleep function
#include <chrono>
#include <thread>
#include <cassert>


#include "mml/time.hpp"

// Custom assert macro
#define assert_msg(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "Assertion failed: (" #cond "), function " << __func__ \
                      << ", file " << __FILE__ << ", line " << __LINE__ << "." << std::endl \
                      << "Message: " << msg << std::endl; \
            std::abort(); \
        } \
    } while (false)

int main(int argc, char **argv) {
	std::cout << std::endl;
	std::cout << "╭──────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for time.hpp │" << std::endl;
	std::cout << "╰──────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	mml::time::Timer time;
	std::cout << "Start a timer with a total duration of 5.5s including a break of 2s" << std::endl;

	time.start();
	time.break_start();
	std::cout << "------> Sleep for 2 seconds" << std::endl;
	time.break_stop();
	sleep(2);
                
    // Performing a break for 2 seconds
    time.break_start();
	std::cout << "------> Timebreak for 2 seconds" << std::endl;
    sleep(2);
    std::cout << "------> Sleep for 1.5 seconds" << std::endl;
    time.break_stop();

    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                
	double ms = time.stop();
	std::cout << std::endl;
    std::cout << "Measured time " << time.clock() << std::endl;
    std::cout << std::endl;
    assert_msg((abs(ms - 3500) < 500), (std::to_string(ms) + " ms passed but 3500 ms expected.").c_str());
	std::cout << ms << " ms passed but 3500 ms expected." << std::endl;
	

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	
	return 0;
}
