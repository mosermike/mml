#include <iostream>
#include <cassert>

#include "mml/standards.hpp"
#include "mml.hpp"


int main() {
	std::cout << std::endl;
	std::cout << "╭───────────────────────────────────╮" << std::endl;
	std::cout << "│ Performing test for standards.hpp │" << std::endl;
	std::cout << "╰───────────────────────────────────╯" << std::endl;
	
	mml::string test = "If you can see this without any numbers, then you the class string workes as intended library132!";
	test.del_number(true);
	std::cout << test << std::endl;
	std::cout << "Now you should see your date and time:" << std::endl;
	std::cout << mml::date(-1, "Date+Time") << std::endl;
	
	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	return 0;
}
