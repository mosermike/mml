
#ifndef MML_INCLUDE_MML_LOGGER_HPP
#define MML_INCLUDE_MML_LOGGER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <ctime>
#include <filesystem>

//#include "mml/standards.hpp"
//#include "mml/Unix.hpp"

namespace mml{

	// Enum for log levels
	enum LogLevel {
		DEBUG,
		INFO,
		WARNING,
		ERROR
	};

	/**
	 * @brief Get the Log Level Name object
	 * 
	 * @param level Loglevel
	 * @return std::string 
	 */
	std::string getLogLevelName(LogLevel level);

	// Logger class
	class logger {
	private:
		LogLevel currentLevel;
		std::ofstream logFile;
		bool logToConsole = false;
		std::mutex logMutex;
		bool log_active = false;
		std::string timestamp_format = "%Y-%m-%d %H:%M:%S";

		std::string getTimestamp() {
			std::time_t now = std::time(nullptr);
			char buf[20];
			std::strftime(buf, sizeof(buf), this->timestamp_format.c_str(), std::localtime(&now));
			return std::string(buf);
		}

		std::string levelToString(LogLevel level) {
			switch (level) {
				case DEBUG:   return "DEBUG   ";
				case INFO:    return "INFO    ";
				case WARNING: return "WARNING ";
				case ERROR:   return "ERROR   ";
				default:      return "UNKNOWN ";
			}
		}

	public:
	/**
	 * @brief Construct a new Logger object
	 * 
	 * @param level lowest loglevel to be printed
	 * @param consoleOutput print to console 
	 * @param filename filename of the log file
	 */
		logger(LogLevel level, bool consoleOutput = true, const std::string& filename = "")
			: currentLevel(level), logToConsole(consoleOutput) {
			open(filename);
		}

		/**
		 * @brief Construct a new Logger object
		 * 
		 */
		logger() {}

		/**
		 * @brief Destroy the Logger object
		 */
		~logger() {
			close();
		}

		/**
		 * @brief Close the logfile
		 */
		void close() {
			if (logFile.is_open()) {
				logFile.close();
			}
		}

		/**
		 * @brief Deactivate logging
		 * 
		 * @param verbose Log the deactivation
		 */
		void deactivate(bool verbose=true) {
			if(verbose)
				this->info("Logging is deactived", __FILE__, __LINE__);
			log_active = false;
		}

		/**
		 * @brief Log a debug
		 * @param message Message to be logged
		 * @param file name of the file executing this function (e.g. __FILE__)
		 * @param line Line number (e.g. __LINE__)
		 */
		void debug(const std::string& message, const std::string& file, int line) {
			log(DEBUG, message, file, line);
		}

		/**
		 * @brief Log an error
		 * 
		 * @param message Message to be logged
		 * @param file name of the file executing this function (e.g. __FILE__)
		 * @param line Line number (e.g. __LINE__)
		 */
		void error(const std::string& message, const std::string& file, int line) {
			log(ERROR, message, file, line);
		}

		/**
		 * @brief Get the loglevel object
		 * 
		 * @return Current loglevel
		 */
		LogLevel get_loglevel() {
			return this->currentLevel;
		}

		/**
		 * @brief Get the logstatus to see if logging is active or not
		 * 
		 * @return true if logging is active
		 * @return false if logging is deactivated
		 */
		bool get_logstatus() {
			return this->log_active;
		}

		/**
		 * @brief Log a info
		 * 
		 * @param message Message to be logged
		 * @param file name of the file executing this function (e.g. __FILE__)
		 * @param line Line number (e.g. __LINE__)
		 */
		void info(const std::string& message, const std::string& file, int line) {
			log(INFO, message, file, line);
		}

		/**
		 * @brief Log a line
		 * 
		 * @param level Level of logging
		 * @param message The message to be logged
		 * @param file The file executing this function
		 * @param line in which line the function is executed
		 * 
		 */
		void log(LogLevel level, const std::string& message, const std::string& file, int line) {
			
			// Only print if logging active
			if (!log_active)
				return;

			if (level < currentLevel) {
				return; // Skip logs below the current level
			}

			std::lock_guard<std::mutex> lock(logMutex);
			
			std::string file_str = file.substr(file.rfind('/')+1);
			
			for(int16_t i = file_str.size(); i <= 20; i++)
				file_str = " " + file_str;

			std::string line_str = std::to_string(line);

			for(int16_t i = line_str.size(); i <= 3; i++)
				line_str += " ";
			
			std::string logMessage =  file_str + ":" + line_str + "| " + levelToString(level) + " | "
									+ message;
			if (logToConsole) {
				std::cout << logMessage << std::endl;
			}
			if (logFile.is_open()) {
				logFile << "[" << getTimestamp() + "]  " << logMessage << std::endl;
			}
		}

		/**
		 * @brief Open a file to log things to
		 * @param filename log file name
		 */
		void open(std::string filename) {
			if(logFile.is_open()) {
				std::cout << "Logfile already opened" << std::endl;
				return;
			}

			if (!filename.empty()) {
				bool logfile_exist = false; // shows if the logfile exists already
				if(std::filesystem::exists(filename))
					logfile_exist = true;

				logFile.open(filename, std::ios::app);
				if (!logFile.is_open()) {
					error("Unable to open log file: " + filename, __FILE__, __LINE__);
					throw std::runtime_error("Unable to open log file: " + filename);
				}

				// Save logfile name at the start
				if(!logfile_exist){
					log(INFO, "Create logfile " + filename + " at " + getTimestamp(), __FILE__, __LINE__);
					log(INFO, "Current loglevel is " + getLogLevelName(currentLevel), __FILE__, __LINE__);
				}
			}
			else
				log(ERROR, "Filename '" + filename + "' is empty", __FILE__, __LINE__);
		}

		/**
		 * @brief Set the output console boolean
		 * @param value determines whether infos are put to console
		 */
		void set_output_console(bool value) {
			this->logToConsole = value;
			if(value)
				info("Print log to console is active", __FILE__, __LINE__);
			else
				info("Print log to console is deactived", __FILE__, __LINE__);
		}

		/**
		 * @brief Set the level object
		 * @param level 
		 */
		void set_level(LogLevel level) {
			currentLevel = level;
			log(INFO, "Set loglevel to " + getLogLevelName(level), __FILE__, __LINE__);
		}

		/**
		 * @brief Set the logging object true
		 * 
		 * @param verbose Log the deactivation
		 */
		void set_logging(bool verbose=true) {
			log_active = true;
			if(verbose)
				this->info("Logging is active", __FILE__, __LINE__);
		}

		/**
		 * @brief Set the timeformat object
		 * @param format format to the time is put to (i.e. "%Y-%m-%d %H:%M:%S")
		 */
		void set_timeformat(std::string format) {
			this->timestamp_format = format;
			info("Log timeformat set to " + format, __FILE__, __LINE__);
		}

		/**
		 * @brief Setup the logging
		 * 
		 * @param level Loglevel to be printed
		 * @param filename where to be logged
		 * @param logToConsole log to console
		 */
		void setup(LogLevel level, std::string filename, bool logToConsole) {
			set_output_console(logToConsole);
			set_logging();
			set_level(level);
			open(filename);
			
		}

		/**
		 * @brief Log a warning
		 *
		 * @param message Message to be logged
		 * @param file name of the file executing this function (e.g. __FILE__)
		 * @param line Line number (e.g. __LINE__)
		 */
		void warning(const std::string& message, const std::string& file, int line) {
			log(WARNING, message, file, line);
		}
	};


	// Global logger instance
	logger& Logger();
}

// Macro to simplify logging
#define LOGMSG(level, message) mml::Logger().log(level, message, __FILE__, __LINE__)
#define LOGWARNING(message) mml::Logger().warning(message, __FILE__, __LINE__)
#define LOGINFO(message) mml::Logger().info(message, __FILE__, __LINE__)
#define LOGERROR(message) mml::Logger().error(message, __FILE__, __LINE__)
#define LOGDEBUG(message) mml::Logger().debug(message, __FILE__, __LINE__)
#define LOGLEVEL(level) mml::Logger().set_level(level)
#define LOGSETUP(level, logfile, logToConsole) mml::Logger().setup(level, logfile, logToConsole)
#define LOGSTATUS mml::Logger().get_logstatus()
#define LOG_ACTIVE mml::Logger().get_logstatus()
#define LOG_DEACTIVE !mml::Logger().get_logstatus()
#define logmsg(level, message) mml::Logger().log(level, message, __FILE__, __LINE__)
#define logwarning(message) mml::Logger().warning(message, __FILE__, __LINE__)
#define loginfo(message) mml::Logger().info(message, __FILE__, __LINE__)
#define logerror(message) mml::Logger().error(message, __FILE__, __LINE__)
#define logdebug(message) mml::Logger().debug(message, __FILE__, __LINE__)
#define logsetup(level, logfile, logToConsole) mml::Logger().setup(level, logfile, logToConsole)
#define loglevel(level) mml::Logger().set_level(level)
#define logstatus mml::Logger().get_logstatus()
#endif