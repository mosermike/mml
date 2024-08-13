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
	class log{
		private:
			mml::string logpath = "";
			std::ofstream output;
			int num_backups = 4; // Number of backups

		public:
			
			/**
			 * @brief Constructor
			 * @param path Path to the logfile
			*/
			log(const mml::string path) : logpath(path), output() {
				logpath = path;
				open();
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
			 * @note that if the last line is a new line, the result will be a new line
			 */
			mml::string lastline() noexcept;

			/**
			 * @brief Create new header
			 * 
			 */
			void header() noexcept;

			/**
			 * @brief Open a logfile
			 * @param path Path to log file
			 * @throw runtime_error : if logpath is not set
			 */
			void open();
			
			/**
			 * @brief Print log file
			 * @param linenumber Print the linenumber
			 */
			void print(const bool linenumber = false) noexcept;
			
			/**
			 * @brief Reset logfile
			 * @param verbose Verbose output what is performed
			 */
			void reset(const bool verbose = true) noexcept;
			
			/**
			 * @brief Set number of backup files
			 * @param num Number of backup files
			 */
			void set_num(const int num) noexcept {
				this->num_backups = num;
				return;
			}

			/**
			 * @brief Set path of the logfile
			 * @param path New path of the logfile
			 */
			void set_path(const mml::string path) noexcept {
				this->logpath = path;
				return;
			}
		};
		
}

#endif