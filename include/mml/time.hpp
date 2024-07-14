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
	namespace time {
		struct time{
			uint64_t hour;
			uint64_t minute;
			uint64_t second;
			uint64_t milliseconds;
			uint64_t microseconds;
		};

		class Timer {
		private:
			/**
			 * Variables for begin and end of the time measurement
			 * microseconds for better precision for millisecond
			 */
			//std::chrono::high_resolution_clock::time_point ticksZwischenstart;
			std::chrono::high_resolution_clock::time_point ticksStart;
			std::chrono::high_resolution_clock::time_point ticksEnd;
			std::chrono::high_resolution_clock::time_point _now() const noexcept;
			double break_time_mus = 0.0; // µs

			bool timebreak = false; // Time measurement on a hold

		public:
			bool stopped = false; // Time measurement was stopped (final stop)
			/**
			 * @brief Constructor which sets the start time to now
			 */
			Timer() 
				: ticksStart(_now()), ticksEnd()
			{}

			/**
			 * @brief Constructor which sets the start and end time to a specific time
			 * @param time Timer which has a start and end time
			 */
			Timer(const Timer& time)
				: ticksStart(time.ticksStart), ticksEnd(time.ticksEnd)
			{}

			~Timer() {}
			
			/**
			 * @brief Stop the time measurement temporarily
			 */
			void break_start () noexcept;

			/**
			 * @brief Continue the time measurement after a temporary break
			 */
			void break_stop() noexcept;
			
			/** 
			 * @brief Convert ticks to time format
			 * @return Time in the format 'hh:mm:ss,ms'
			 * @note Prints a warning if the timer was not stopped before
			 */
			std::string clock() noexcept;

			/**
			 * @brief Get a time point
			 * @param option which time point is returned (options are: "start" or "end")
			 * @return time point
			 * @throw runtime_error : if timer was not stopped before
			 * @throw invalid_argument : if option is not defined
			 */
			std::chrono::high_resolution_clock::time_point get_ticks(std::string option);
			
			/**
			 * @brief Get actual passed time in ms
			 * @return time in ms
			 * @author Lucas
			 */
			double getMS() noexcept;

			/**
			 * @brief Get actual passed time in s
			 * @return time in seconds
			 */
			double getS() noexcept;

			/**
			 * @brief Get actual passed time in µs
			 * @return time in µs
			 * @author Lucas
			 */
			uint64_t getUS() noexcept;

			/**
			 * @brief Output the time as a string via a stream in ms
			 * @param out output stream
			 * @param time Timer
			 * @return ostream
			*/
			friend std::ostream& operator<< (std::ostream &out, mml::time::Timer &time) noexcept {
				out << time.str();
				return out;
			}

			/**
			 * @brief Pint time formatted or in ms
			 * @param text A text printed first without a newline
			 * @param format_print Print by using the function range (false : in ms)
			 * @param newline Print with a newline
			 */
			void print(std::string text = "", bool format_print = false, bool newline = true) noexcept;

			/** 
			 * @brief return the time depending on the time value itself
			 * @return returns the time in µs, ms, s or as a clock
			 * @author Mike
			 */
			std::string range() noexcept;

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
			 * @brief Returns the milliseconds between start and end as a string
			 * @return Time with the unit "ms"
			 * @throw runtime_error : if timer is still running
			 */
			std::string str();
		
			/**
			 * @brief Get a structure with the meantime
			 * @return Structure with the meantime in µs, ms, s, min and hours
			 * @note The structure is not in the format of a time. If the meantime is 1 ms, the structure will have s=0, ms = 1 and µs = 1000
			 * @throw runtime_error : if timer is still running
			 */
			mml::time::time strct();

			/**
			 * @brief Get a structure with the meantime in the format of a clock hh:mm::ss,ms
			 * @return Structure with the meantime in µs, ms, s, min and hours
			 * @throw runtime_error : if timer is still running
			 */
			mml::time::time strct_clock();

			/**
			 * @brief Convert ticks to double
			 * @param ticks Time point to which the passed time is computed
			 * @param f Factor which determines the unit (1.0 = µs, 1000.0 = ms, 1.0e6 = s)
			 * @return Return time passed between start and end
			 */
			double ticks_to_double(std::chrono::high_resolution_clock::time_point ticks, double f = 1.0) noexcept;

			/**
			 * @brief Returns the milliseconds between start and end.
			 * @return milliseconds as an integer
			 * @throw runtime_error : if timer is still running
			 */		
			int toInt();
			
		};
	}
}


#endif
