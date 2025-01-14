#include "mml/logger.hpp"

//#ifdef ENABLE_LOGGING
//mml::Logger globalLogger(mml::INFO, true, "library.log");
//#endif
mml::logger& mml::Logger() {
        static logger instance;
        return instance;
}

std::string mml::getLogLevelName(LogLevel level) {
		switch (level) {
			case DEBUG:   return "DEBUG";
			case INFO:    return "INFO";
			case WARNING: return "WARNING";
			case ERROR:   return "ERROR";
			default:      return "Loglevel unknown";
    	}
	}