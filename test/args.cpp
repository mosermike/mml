/**
 * Performing test for tthe class arguments
*/
#include <iostream>

#include "mml/shell.hpp"


int main(int argc, char **argv) {
	std::cout << "╭────────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for class args │" << std::endl;
	std::cout << "╰────────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	try {
		mml::shell::arg args(argv,argc);
		
		std::cout << "Did you execute the program as " << args[0] << " or as 'make test'?" << std::endl;
		
		std::cout << std::endl;
		std::cout << "─────────────────────────────────────────────────────" << std::endl;
		std::cout << std::endl;

		args = (std::vector<mml::string>) {"-abc","-fg","--hi","-jkl"};
		args.init("-de","-fg","-hi");

		for(auto i : args.tovec())
			std::cout << i << ", ";
		std::cout << std::endl;
		std::cout << "Was the last printed out this string: '-a, -b, -c, -fg, --hi, -j, -k, -l,'?";
		if(args[0] == "-a" && args[1] == "-b" && args[2] == "-c" && args[3] == "-fg" && args[4] == "--hi" && args[5] == "-j" && args[6] == "-k" && args[7] == "-l")
			std::cout << " Yes!" << std::endl;
		else
			std::cout << " No! There might be something wrong..." << std::endl;

		std::cout << std::endl;
		std::cout << "─────────────────────────────────────────────────────" << std::endl;
		std::cout << std::endl;
		
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

	}
	catch (const std::invalid_argument& e) {
        std::cerr << "Detected Error: " << e.what() << std::endl;
	}
	
	return 0;
}
