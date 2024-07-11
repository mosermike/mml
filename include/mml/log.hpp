/**
 * @author Mike Moser
 * 
 * @file log.hpp
 * @brief Contains different functions for logging
 * 
*/

#ifndef MML_INCLUDE_MML_LOG_HPP
#define MML_INCLUDE_MML_LOG_HPP

#include <iostream>
#include <fstream>
#include <string>

#include "mml/standards.hpp"

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
			
			/**
			 * @brief Constructor
			 * @param path Path to the logfile
			 * @throw runtime_error : if log file is not created
			*/
			log(mml::string path) : logpath(path), output() {
				logpath = path;
				if(!mml::Unix::exist(logpath.str())) {
					output.open(logpath.c_str(),std::ios::out | std::ios::app);
					header();
					if(!mml::Unix::exist(logpath.str()))
						throw std::runtime_error("[LOG] Creation of logfile '" + logpath.str() + "' not possible. Check permissions!");
				}
				else
					output.open(logpath.c_str(),std::ios::out | std::ios::app);
			}

			/**
			 * @brief Empty constructor
			*/
			log() : logpath(""), output() {}
		
			/**
			 * @brief Deconstructor
			*/
			~log() noexcept {output.close();}
			
 			/**
			 * @brief  Open new log file;
			 * @param value Path to the logfile
			 */
			mml::log &operator=(std::string value) noexcept;
			
			/** 
			 * @brief Writes a value into the logfile
			 * @param log Instance of the class to be used
			 * @param String Value to be written into the log file
			*/
			template <typename T> friend log& operator<< (mml::log &log, const T &String) noexcept{
				log.output << String;
				return log;
			}

			/**
			 * @brief Output special characters like std::endl
			 * @param manip to be printed
			 * @return ostream
			*/
            friend log& operator<<(mml::log &log, std::ostream& (*manip)(std::ostream&)) noexcept {
                log.output << manip;
                return log;
            }
			
			/**
			 * @brief Backups the log file by copying it to [filename].bak 
			 * @param verbose Verbose output
			 * @param Reset reset the actual log file so that it is empty
			 */
			void backup(bool verbose = true, bool Reset = true) noexcept;
			
			/**
			 * @brief Close log file
			 */
			void close() noexcept;
			
			/**
			 * @brief Write sth. into the log file
			 * @param value
			 * @param newline Write a newline after the value
			 */
			//template <typename T> void cout(T value,bool newline=false) noexcept;
			template <typename T> void cout(T value,bool newline) noexcept {
				this->output << value;
				if(newline)
					this->output << std::endl;
			}
			
			/**
			 * @brief Return a specific line form the log file
			 * @param line Line Number
			 * @return string
			 */
			mml::string getline(size_t line) noexcept;
			
			/**
			 * @brief Get a specific line from the log file
			 * @param line Line number from the last line
			 * @return string
			 * @throw runtime_error : if line number exceeds lines
			 */
			mml::string getline_back(size_t line);
			
			/**
			 * @brief Get the last line of a logfile
			 * @return string
			 */
			mml::string lastline() noexcept;

			/**
			 * @note Neuen Kopf erstellen
			 * 
			 */
			void header() noexcept;

			/**
			 * @brief open a logfile
			 * @param path Path to log file
			 */
			void open(mml::string path = "") noexcept;
			
			/**
			 * @brief Print log file
			 * @param linenumber Print the linenumber
			 */
			void print(bool linenumber = false) noexcept;
			
			/**
			 * @brief Reset logfile
			 * @param verbose Verbose output what is performed
			 */
			void reset(bool verbose = true) noexcept;
			
			
		};
		
}
#endif // __LOG_HPP__
