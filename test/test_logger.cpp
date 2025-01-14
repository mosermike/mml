// TODO setup properly this script
#include "mml/logger.hpp"




int main() {
	
	std::cout << std::endl;
	std::cout << "╭────────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for logger.hpp │" << std::endl;
	std::cout << "╰────────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;
	logmsg(mml::INFO, "This is an info message from the library. This info should not be visible");

	logsetup(mml::INFO, "test_logger.log", true);
	logmsg(mml::INFO, "This is an info message from the library. This info should be visible");
    logerror("An error occurred in the library. This error should be visible.");
	loglevel(mml::ERROR);
	mml::logger().log(mml::INFO, "An info occurred in the library. This info should not be visible.", __FILE__, __LINE__);
	loglevel(mml::INFO);
	logmsg(mml::WARNING, "A warning occurred in the library. This warning should appear.");
	LOGDEBUG("This line should not appear");
	
	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;
	
	LOGINFO("Close the log file");
	mml::Logger().close(); // Close the log file
	return 0;
}