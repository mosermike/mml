#include <mml/standards.hpp>
#include <mml.hpp>
#include <iostream>

int main() {
	mml::string test;
	test = "If you can see this without any numbers, then you succesfully installed your library132!";
	test.del_number(true);
	std::cout << test << std::endl;

	return 0;
}
