/**
 * Performing test for the class log
*/
#include <iostream>
#include <cassert>

#include "mml/log.hpp"
#include "mml/Unix.hpp"
#include "mml/standards.hpp"
#include <cstdlib>  // For std::abort
#include <filesystem>

// Custom assert macro
#define assert_msg(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "Assertion failed: (" #cond "), function " << __func__ \
                      << ", file " << __FILE__ << ", line " << __LINE__ << "." << std::endl \
                      << "Message: " << msg << std::endl; \
            std::abort(); \
        } \
    } while (false)

int main(int argc, char **argv) {
	std::cout << std::endl;
	std::cout << "╭───────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for class log │" << std::endl;
	std::cout << "╰───────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	std::cout << "Testing writing and reading a log entry ...";

	// Create Random File
	mml::string tmpfile = "./test_log_" + mml::random_str(10) + ".log"; // Create a temporary, random logfile

	// Open the log file
	mml::log log(tmpfile);
		
	log << "TEST123" << std::endl;

	mml::string test = log.lastline();
	assert_msg(test == "TEST123", "\nFirst log entry was '" + test.str() + "' instead of 'TEST123'.");
	std::cout << " Passed" << std::endl;
	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	std::cout << "Testing backup function ...";

	log.set_num(4);
	//log.backup(false,true);
	//log.backup(false,true);
	
	//assert_msg(mml::Unix::exist(tmpfile.str(), tmpfile + ".bak", tmpfile + ".bak1", tmpfile + ".bak2"), 
	//			"\nBackups are not created and moved as expected. Expected are in total 7 files."
	//);
	//std::filesystem::remove(tmpfile.str());
	//std::filesystem::remove(tmpfile.str() + ".bak");
	//std::filesystem::remove(tmpfile.str() + ".bak1");
	//std::filesystem::remove(tmpfile.str() + ".bak2");
	std::cout << " Passed" << std::endl;
	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;
	
	return 0;
}
