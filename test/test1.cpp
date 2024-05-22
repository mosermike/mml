#include "mml/standards.hpp"
#include "mml.hpp"
#include <iostream>

int main() {
	mml::string test = "If you can see this without any numbers, then you succesfully installed your library132!";
	test.del_number(true);

	std::cout << "Now you should see your date and time:" << std::endl;
	std::cout << mml::date("Date+Time") << std::endl;
	
	

	return 0;
}
