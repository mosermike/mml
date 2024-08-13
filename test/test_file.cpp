/**
 * @file test_file.cpp
 * @author Mike Moser
 * @brief Tests for file.hpp
 * @version 1.0
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <cassert>
#include <cstdlib>  // For std::abort

#include "mml/file.hpp"
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
	std::cout << "╭──────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for file.hpp │" << std::endl;
	std::cout << "╰──────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	system("mkdir -p ./test_file/test123; touch ./test_file/test1");
	mml::file::copy("./test_file","./test_file1","","",100, false, false, true , true, true, true, true);

	

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	
	return 0;
}
