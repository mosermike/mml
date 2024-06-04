/**
 * @author Lucas, Mike
 * 
 * @file Timer.hpp 
 * @brief Contains different functions and a class concerning timing
 * 
*/

#ifndef MML_INCLUDE_MML_TIMER_HPP
#define MML_INCLUDE_MML_TIMER_HPP

#include <chrono>
#include <cstdint>
#include <string>

namespace mml {
	class Timer {
	private:
		/**
		 * Variables for begin and end of the time measurement
		 * microseconds for better precision for millisecond
		 */
		std::chrono::high_resolution_clock::time_point ticksStart;
		std::chrono::high_resolution_clock::time_point ticksEnd;
		std::chrono::high_resolution_clock::time_point ticksZwischenstart;
        std::chrono::high_resolution_clock::time_point _now() const noexcept;
		double break_time_mus = 0.0; // µs
        
	public:
		
		Timer() 
			: ticksStart(_now()), ticksEnd(), ticksZwischenstart()
		{}

		Timer(const Timer& t)
			: ticksStart(t.ticksStart), ticksEnd(t.ticksEnd), ticksZwischenstart()
		{}

		~Timer() {}

		//Timer() : ticksStart(), ticksEnd(), ticksZwischenstart(), break_time_mus() {};
        //Timer(const Timer& t);
		//~Timer();
		
		/**
		 * @note stop the time measurement
		 * @author Mike
		 */
		void break_start();
		/**
		 * @brief continue the time measurement
		 * @author Mike
		 */
		void break_stop();
		
		
		/**
		 * @note Pint time formatted or in ms
		 * @param text A text printed first without a newline
		 * @param format_print Print by using the function range (false : in ms)
		 * @param newline Print with a newline
		 * @author Mike
		 */
		void cout(std::string text = "", bool format_print = false, bool newline = true);
		/**
		 * @brief Start time measurement
		 * @author Lucas
		 */
		void start() noexcept;

		/**
		 * @brief Stops the time measurement
		 * @return passed time in ms
		 * @author Lucas
		 */
		double stop() noexcept;
		
		/**
		 * @brief get the time in µs
		 * @return time in µs
		 * @author Lucas
		 */
		uint64_t getUS(bool stop = true) noexcept;
				
		/**
		 * @brief Return time in ms without stopping
		 * @return time in ms
		 * @author Lucas
		 */
		double getMS(bool stop = true) noexcept;
        
		/**
		 * @brief Return time in s without stopping
		 * @return time in seconds
		 * @author Mike
		 */
		double getS(bool stop = true) noexcept;
		
        int toInt() noexcept;
        
        std::string toString() noexcept;
	
		/** 
		 * @brief Convert ticks to time format
		 * @return time in the format 'hh:mm:ss,ms'
		 * @author Mike
		 */
		struct time;
		std::string clock() noexcept;
	
		/** 
		 * @brief return the time depending on the time value itself
		 * @return returns the time in µs, ms, s or as a clock
		 * @author Mike
		 */
		std::string range() noexcept;
	};
}

std::ostream& operator<<(mml::Timer& t, std::ostream& os);


#endif
