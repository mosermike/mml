/**
 * @author Lucas, Mike
 * 
 * @file Timer.hpp 
 * @note Enthält verschiedene Timerfunktionen
 * 
*/

#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <chrono>
#include <cstdint>

#include "mml.hpp"

namespace mml {
	/**
	 * Timer mit std::chrono (anstatt SDL_GetPerformanceCounter())
	 */
	class Timer {
	private:
		/**
		 * Variablen für Beginn und Ende der Zeitmessung.
		 * 
		 * microseconds für bessere genauigkeit bei Millisekunden
		 * (Teilen durch 1000.0)
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
		 * @note Pause starten
		 * 
		 * @author Mike
		 */
		void break_start();
		/**
		 * @note Pause stoppen
		 * 
		 * @author Mike
		 */
		void break_stop();
		
		
		/**
		 * @note Zeit ausgeben (formatiert oder in Millisekunden)
		 * 
		 * @author Mike
		 */
		void cout(std::string text = "", bool format_print = false, bool newline = true);
		/**
		 * @note Beginnt die Zeitmessung.
		 * 
		 * @author Lucas
		 */
		void start() noexcept;

		/**
		 * @note Stoppt die Zeitmessung.
		 * 
		 * @return Vergangene Zeit in Millisekunden
		 * @author Lucas
		 */
		double stop() noexcept;
		
		/**
		 * @note Direkten Wert in Mikrosekunden zurückgegeben.
		 * 
		 * @return Vergangene Zeit in Mikrosekunden (uint64_t)
		 * @author Lucas
		 */
		uint64_t getUS(bool stop = true) noexcept;
				
		/**
		 * @note Zwischenergebnis zurückgegeben.
		 * 
		 * @return Zwischenergebnis
		 * @author Lucas
		 */
		double getMS(bool stop = true) noexcept;
        
		/**
		 * @note Zwischenergebnis zurückgegeben in s.
		 * 
		 * @return Zwischenergebnis
		 * @author Mike
		 */
		double getS(bool stop = true) noexcept;
		
        int toInt() noexcept;
        
        std::string toString() noexcept;
	
		/** 
		 * @note ticks in Zeitformat ändern
		 * 
		 * @return Ausgabe der Zeit im Format 'hh:mm:ss,ms'
		 * @author Mike
		 */
		struct time;
		std::string clock() noexcept;
	
		/** 
		 * @note Zeit abhängig von der Größe zurückgeben
		 * 
		 * @return Ausgabe der Zeit
		 * @author Mike
		 */
		std::string range() noexcept;
	};

	namespace Time {
		/**
		* @note time_t in Datumformat
		* 
		* @return string
		* @author Mike
		*/
		mml::string to_date(time_t time);
		/**
		* @note Datumformat (DD.MM.YYYY HH:MM.SS) in time_t 
		* 
		* @return time_t
		* @author Mike
		*/
		time_t to_time(std::string date);
	}
}

std::ostream& operator<<(mml::Timer& t, std::ostream& os);


#endif
