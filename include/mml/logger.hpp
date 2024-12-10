
#ifndef MML_INCLUDE_MML_LOG_HPP
#define MML_INCLUDE_MML_LOG_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <ctime>

#include "mml/standards.hpp"

namespace mml{

	// Enum for log levels
	enum LogLevel {
		DEBUG,
		INFO,
		WARNING,
		ERROR
	};

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
			
			std::string file_str = file.substr(mml::to_string(file).rfind('/')+1);
			
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
			if (!filename.empty()) {
				logFile.open(filename, std::ios::app);
				if (!logFile.is_open()) {
					throw std::runtime_error("Unable to open log file: " + filename);
				}
			}
			else
				log(ERROR, "Logfile is already open", __FILE__, __LINE__);
		}

		/**
		 * @brief Set the output console boolean
		 * @param value determines whether infos are put to console
		 */
		void set_output_console(bool value) {
			this->logToConsole = value;
		}

		/**
		 * @brief Set the level object
		 * @param level 
		 */
		void set_level(LogLevel level) {
			currentLevel = level;
		}

		/**
		 * @brief Set the logging object true
		 */
		void set_logging() {
			log_active = true;
		}

		/**
		 * @brief Set the timeformat object
		 * @param format format to the time is put to (i.e. "%Y-%m-%d %H:%M:%S")
		 */
		void set_timeformat(std::string format) {
			this->timestamp_format = format;
		}
		/**
		 * @brief Setup the logging
		 * 
		 * @param level Loglevel to be printed
		 * @param filename where to be logged
		 * @param logToConsole log to console
		 */
		void setup(LogLevel level, std::string filename, bool logToConsole) {
			set_logging();
			set_level(level);
			set_output_console(logToConsole);
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
	logger Logger;
}

// Macro to simplify logging
#define LOG(level, message) \
    mml::Logger.log(level, message, __FILE__, __LINE__)
#define LOGWARNING(message) \
    mml::Logger.warning(message, __FILE__, __LINE__)
#define LOGINFO(message) \
    mml::Logger.info(message, __FILE__, __LINE__)
#define LOGERROR(message) \
    mml::Logger.error(message, __FILE__, __LINE__)
#define LOGDEBUG(message) \
    mml::Logger.debug(message, __FILE__, __LINE__)
#define LOGLEVEL(level) \
    mml::Logger.set_level(level)

#endif