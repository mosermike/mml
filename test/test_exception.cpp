/**
 * @file test_exception.cpp
 * @author Mike Moser
 * @brief Tests for exception.hpp
 * @version 1.0
 * @date 2025-02-
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <iostream>
#include <cassert>
#include <cstdlib>  // For std::abort

#include "mml/string.hpp"
#include "mml/Unix.hpp"
#include "mml/exception.hpp"

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

bool file_exist(mml::string file) {
	if(mml::Unix::exist(file))
		return true;
	else
		throw mml::FileNotFound(file.str());

}
int main(int argc, char **argv) {
	std::cout << std::endl;
	std::cout << "╭───────────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for exception.hpp │" << std::endl;
	std::cout << "╰───────────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;
	std::cout << "Test Exception FileNotFound" << std::endl;

	try{
		throw mml::FileNotFound("File Not Found");
	}
	catch (const mml::FileNotFound& e) {
        // print the exception
        std::cerr << "Exception File Not Found: " << e.what() << std::endl;
		std::cout << "Exception works as expected" << std::endl;
    }
    catch (const std::exception& e) {
        // print the exception
        std::cerr << "Unexpected Exception " << e.what() << std::endl;
		throw std::runtime_error("Unexpected exception happened");
    }
	

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	try{
		throw mml::MissingArgument("Missing argument xxx");
	}
	catch (const mml::MissingArgument& e) {
        // print the exception
        std::cerr << "Exception Missing Argument: " << e.what() << std::endl;
		std::cout << "Exception works as expected" << std::endl;
    }
    catch (const std::exception& e) {
        // print the exception
        std::cerr << "Unexpected Exception " << e.what() << std::endl;
		throw std::runtime_error("Unexpected exception happened");
    }

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	
	return 0;
}
