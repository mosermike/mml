#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <thread>
#include <cassert>

#include "mml/thread.hpp"

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

/**
 * @brief Testing threading if they run
 * @param threadId Id of the thread
 * @param threads the class with the threads for printout
 * @return int with no real information
 */
int exampleTaskWithMultipleParams(int threadId, mml::thread::Threads<int> &threads) {
    // Put thread 0 and 1 to sleep
	if(threads.size > 2) {
		threads.sleep(threadId, 0,5000);
		threads.sleep(threadId, 1,100);
	}
	
	threads << "Thread " + std::to_string(threadId) + " is running.\n";
    
	
	// Simulate some work with sleep
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

    threads << "Thread " + std::to_string(threadId) + " has finished.\n";
	
    return 1;
}

/**
 * @brief Checks if a number is a prime number
 * @param number Number to be checked
 * @return bool
 */
bool isPrime(int number) {
    if (number <= 1) return false;
    if (number == 2) return true;
    if (number % 2 == 0) return false;
    for (int i = 3; i <= std::sqrt(number); i += 2) {
        if (number % i == 0) return false;
    }
    return true;
}

/**
 * @brief Search prime numbers in a range
 * @param threadId Id of the thread
 * @param start Start Value
 * @param end End Value
 * @return Number of Prime Numbers
 */
int search_prime(int threadId, int start, int end) {        
	int primeCount = 0;

	for (int i = start; i <= end; ++i) {
		if (isPrime(i))
        	primeCount++;
    }

	return primeCount;
    }

int main() {
	std::cout << "╭────────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for thread.hpp │" << std::endl;
	std::cout << "╰────────────────────────────────╯" << std::endl;
    
	// Parameters
	const int n = std::thread::hardware_concurrency();  // Number of threads (maximum of the hardware)
    const int rangeStart = 1;
    const int rangeEnd = 12500000; // Range for prime numbers per thread
	const int rangePerThread = rangeEnd/n;

	std::cout << "Start Example Task" << std::endl;
	if(n > 2)
		std::cout << "Task 0 should finish last" << std::endl;

    mml::thread::Threads<int> threads(n);

    // Use a lambda to bind the additional parameters to the task function
    auto task = [&threads](int threadId) -> int {
        return exampleTaskWithMultipleParams(threadId, threads);
    };

    // Start the threads
	threads.start(task);
	
    // Join all threads
    threads.join();

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;
	
	std::cout << "Start Searching Prime Numbers" << std::endl;

	auto task1 = [&threads, &rangeStart, &rangePerThread, &rangeEnd](int threadId) -> int {
		int start = rangeStart + threadId * rangePerThread;
        int end = (threadId == threads.size - 1) ? rangeEnd : start + rangePerThread - 1;
		threads << std::to_string(threadId) + " from " + std::to_string(start)  + " to " + std::to_string(end) << std::endl;
        return search_prime(threadId, start, end);
    };

	// Start the threads
	threads.start(task1);
	
    // Join all threads
    threads.join();
    
	// Get the results from all threads
    std::vector<int> results = threads.getResults();
    for (int i = 0; i < n; i++) {
		int start = rangeStart + i * rangePerThread;
        int end = (i == threads.size - 1) ? rangeEnd : start + rangePerThread - 1;
		std::cout << "Thread " << i << " found " << results[i] << " primes in range " << start << " to " << end << std::endl;
    }
	int res = 0;
	for (int i : results)
		res += i;
	
	assert_msg(res == 818703, ("Found " + std::to_string(res) + " primes in range " + std::to_string(rangeStart) +
	" to " + std::to_string(rangeEnd) + " but 818703 were expected."));

	std::cout << "Found " << res << " primes in range " << rangeStart << " to " << rangeEnd << " as expected." << std::endl;
	
	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	
    return 0;
}
