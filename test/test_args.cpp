/**
 * Performing test for tthe class arguments
*/
#include <iostream>
#include <cassert>

#include "mml/shell.hpp"

#include <cstdlib>  // For std::abort

// Custom assert macro
#define assert_msq(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "Assertion failed: (" #cond "), function " << __func__ \
                      << ", file " << __FILE__ << ", line " << __LINE__ << "." << std::endl \
                      << "Message: " << msg << std::endl; \
            std::abort(); \
        } \
    } while (false)

int main(int argc, char **argv) {
	std::cout << "╭────────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for class args │" << std::endl;
	std::cout << "╰────────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	mml::shell::arg args(argv,argc);
		
	args = (std::vector<mml::string>) {"-abc","-fg","--hi","-jkl"};
	args.init("-de","-fg","-hi");

	for(auto i : args.tovec())
		std::cout << i << ", ";
	std::cout << std::endl;
	std::cout << "Was the last printed out this string: '-a, -b, -c, -fg, --hi, -j, -k, -l,'?" << std::endl;
	assert_msq(args[0] == "-a" && args[1] == "-b" && args[2] == "-c" && args[3] == "-fg" && args[4] == "--hi"
			&& args[5] == "-j" && args[6] == "-k" && args[7] == "-l", "No! There might be something wrong ...");
	std::cout << "Yes!" << std::endl;
	

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	
	return 0;
}
