/**
 * Performing test for tthe class arguments
*/
#include <iostream>
#include <unistd.h> // for sleep function
#include <chrono>
#include <thread>



#include "mml/time.hpp"

int main(int argc, char **argv) {
	std::cout << "╭──────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for time.hpp │" << std::endl;
	std::cout << "╰──────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	try {
		
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
                if(abs(ms - 3.5) < 0.5)
                        std::cout << ms << " ms passed as expected." << std::endl;
                else
                        std::cout << ms << " ms passed but 3.5 ms expected." << std::endl;

				std::cout << std::endl;
				std::cout << "─────────────────────────────────────────────────────" << std::endl;
				std::cout << std::endl;

				std::cout << std::endl;
				std::cout << std::endl;
				std::cout << std::endl;

	}
	catch (const std::invalid_argument& e) {
        std::cerr << "Detected Error: " << e.what() << std::endl;
	}
	
	return 0;
}
