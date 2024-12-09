// TODO setup properly this script
#include "mml/logger.hpp"

//#ifdef ENABLE_LOGGING
//mml::Logger globalLogger(mml::INFO, true, "library.log");
//#endif

void exampleFunction() {
    LOG(mml::INFO, "This is an info message from the library.");
    LOG(mml::ERROR, "An error occurred in the library.");
	LOGLEVEL(mml::ERROR);
	LOG(mml::INFO, "An info occurred in the library.");
	LOGLEVEL(mml::INFO);
	LOG(mml::WARNING, "An error occurred in the library11.");
}


int main() {
	exampleFunction();
	mml::globalLogger.setup(mml::INFO, "test_logger.log", true);
	exampleFunction();
	return 0;
}