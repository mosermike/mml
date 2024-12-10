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
	mml::Logger.setup(mml::INFO, "test_logger.log", true);

	LOG(mml::INFO, "This is an info message from the library. This info should be visible");
    LOGERROR("An error occurred in the library. This error should be visible.");
	LOGLEVEL(mml::ERROR);
	LOG(mml::INFO, "An info occurred in the library. This info should not be visible.");
	LOGLEVEL(mml::INFO);
	LOG(mml::WARNING, "A warning occurred in the library. This warning should appear.");
	LOGDEBUG("This line should not appear");
	
	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;
	
	LOGINFO("Close the log file");
	mml::Logger.close(); // Close the log file

	return 0;
}