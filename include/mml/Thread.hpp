/**
 * : @author Mike Moser
 * : 
 * : @name Thread.hpp
 * :
 * : @note Enthält verschiedene Funktionen für Threads, insbesonder eine Art Semaphore
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
			* @note aktuelles Schreiben aktiv oder nicht aktiv setzen und dessen Abfrage
			* 
			* @author Mike
			*/
			void thread_writing_true();
			void thread_writing_false();
			bool is_writing_active();
			
			/**
			* @note Versetzt den aktuellen Thread in den Sleep-Modus
			* 
			* @author Mike
			*/
			void thread_sleep(float second);
			void thread_sleep_millisecond(uint32_t millisecond);
			

			/**
			* @note Wartefunktion beim mehrfachen Schreiben
			* 		Nicht immer gleiche Reihenfolge, wenn a nicht verwendet.
			* 
			* @return true, wenn kein Thread mehr schreiben will
			* @author Mike
			*/ 
			bool waiting(int a = 0);

			/**
			* @note Wartefunktion beim mehrfachen Schreiben, nicht immer gleiche Reihenfolge
			* 
			* @return true, wenn kein Thread mehr schreiben will
			* @author Mike
			*/ 
			//bool waiting(int a);
		};

		/**
		 * @note Aktueller Thread eine bestimmte Zeit lang stoppen 
		 * 
		 * @arg Second
		 * @author Mike
		 */
		void sleep(float s);
	}
}
#endif
