/**
 * : @author Mike Moser
 * : 
 * : @name Thread.hpp
 * :
 * : @brief Contains the class Thread which can be used for using threads
 * : 
*/

#ifndef MML_INCLUDE_MML_THREAD_HPP
#define MML_INCLUDE_MML_THREAD_HPP

#include <iostream>       // std::cout
#include <thread>         // std::thread, std::thread::id, std::this_thread::get_id
#include <chrono>         // std::chrono::seconds

namespace mml {
	namespace thread {
		class Thread {
		private:
			bool thread_writing_active = false;
			int i = 0;
			int max_i = 0;
		
		
		public:
			
			Thread() {};
					// Mit Initialisierung eines Vektors:
			Thread(const Thread &thread_copy) {thread_writing_active = thread_copy.thread_writing_active;}	// Kopierkonstruktor

			// Mit direkter Initialisierung der Argumenten:
			Thread(int max_i2){
						this->max_i = max_i2;
			}	// Aufruf mml::shell::arg arg(argc,argv);
					
			// Als Kopierkonstruktor:
			Thread &operator=(const Thread &thread_temp){
				this->max_i = thread_temp.max_i;		
				thread_writing_active = thread_temp.thread_writing_active;
				return *this;
			}
			
			/**
			* @note Die maximale Anzahl an vorhandenen Threads
			* 
			* @author Mike
			*/
			void set_max_i(int max_temp) { this->max_i = max_temp;}
			
			/**
			* @brief Set this thread to active writing
			*/
			void thread_writing_true();
		
			/**
			* @brief Set this thread to not actively writing
			*/
			void thread_writing_false();

			/**
			 * @brief Checks if the thread is writing
			 * @return true = is writing
			 */
			bool is_writing_active();
			
			/**
			* @brief Sleep for a while
			* @param second Sleep for so many seconds
			*/
			void thread_sleep(float second);

			/**
			* @brief Sleep for a while
			* @param millisecond Sleep for so many miliseconds
			*/
			void thread_sleep_millisecond(uint32_t millisecond);
			

			/**
			* @brief Waits if many threads are writing
			* 		if a not used, not always the same order of writing
			* @param a wait for so many miliseconds. if a = 0 => random number is created in milliseconds
			* @return true, when no thread is writing
			*/ 
			bool waiting(int a = 0);
		};

		/**
		 * @brief Stop actual thread for a specific time
		 * @param s Seconds to wait
		 */
		void sleep(float s);
	}
}
#endif