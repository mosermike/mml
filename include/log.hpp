/**
 * @author Mike Moser
 * 
 * @file log.hpp
 * @note Enthält verschiedene Funktionen fürs logging
 * 
*/

#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <iostream>
#include <fstream>
#include <string>

#include <standards.hpp>

// TODO an letzter Zeile etwas anhängen
// TODO bei Ausgabe anhand von Dateigröße entscheiden wie viele führende Nullen
// TODO backup => verschieben der Logdatei und nicht einfach löschen
// TODO Ordner erstellen, Berechtigung prüfen Ausgabe prüfen => als root bei pi geht nicht, Ordner auch nicht vorhanden
namespace mml{
	
	namespace Unix{
		extern bool exist(std::string path);
	}
	
	namespace file {
		extern void remove(std::string file);
	}
	
	namespace shell {
		void error(std::string text);
	}
	
	class log{
		private:
			mml::string logpath = "";
			std::ofstream output;
			
		public:
			
			// Constructor
			log(mml::string path) : logpath(path), output() {
				logpath = path;
				if(!mml::Unix::exist(logpath.str())) {
					output.open(logpath.c_str(),std::ios::out | std::ios::app);
					header();
					if(!mml::Unix::exist(logpath.str()))
						mml::shell::error("[LOG] Erstellung der Logdatei nicht möglich. Berechtigung prüfen!");
				}
				else
					output.open(logpath.c_str(),std::ios::out | std::ios::app);
			}
			log() : logpath(""), output() {}
		
			// Deconstructor
			~log(){output.close();}
			
 			/**
			 * @note Neue Logfile öffnen;
			 * 
			 * @author Mike
			 */
			mml::log &operator=(std::string value);
			
// 			friend void operator<< (mml::log &log, const char* &String){
// 				log.output << String << std::endl;
// 				return;
// 			}
			
// 			friend void operator<< (mml::log &log, const std::string &String){
// 				log.output << String << std::endl;
// 				return;
// 			}
			
			friend void operator<< (mml::log &log, const mml::string &String){
				log.output << String << std::endl;
				return;
			}

			
			friend void operator<< (mml::log &log, const double &String){
				log.output << String << std::endl;
				return;
			}
			
			/**
			 * @note Logdatei sichern
			 * 
			 * @author Mike
			 */
			void backup(bool verbose = true, bool Reset = true);
			
			/**
			 * @note Logdatei schließen
			 * 
			 * @author Mike
			 */
			void close();
			
			/**
			 * @note in Logdatei schreiben
			 * 
			 * @author Mike
			 */
			void cout(mml::string value,bool newline=false);
// 			void cout(std::string value,bool newline=false);
			void cout(double value,bool newline=false);
			void cout(int value,bool newline=false);
			//void compress(std::size_t filesize);
			
			/**
			 * @note Eine bestimmte Zeile aus der Logdatei zurückgeben
			 * 
			 * @return string
			 * @author Mike
			 */
			mml::string getline(uint32_t line);
			
			/**
			 * @note Eine bestimmte Zeile aus der Logdatei zurückgeben, dabei vom Ende aus Rechnen
			 * 
			 * @return string
			 * @author Mike
			 */
			mml::string getline_back(uint32_t line);
			
			/**
			 * @note Die letzte Zeile aus der Logdatei zurückgeben
			 * 
			 * @return stirng
			 * @author Mike
			 */
			mml::string lastline();
			/**
			 * @note Neuen Kopf erstellen
			 * 
			 * @author Mike
			 */
			void header();
			/**
			 * @note Logdatei öffnen
			 * 
			 * @author Mike
			 */
			void open(mml::string path = "");
			
			/**
			 * @note Logdatei ausgeben
			 * 
			 * @author Mike
			 */
			void print(bool linenumber = false);
			
			/**
			 * @note Logdatei neu erstellen
			 * 
			 * @author Mike
			 */
			void reset(bool verbose = true);
			
			
		};
		
}
#endif // __LOG_HPP__
