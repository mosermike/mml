/**
 * Performing test for tthe class arguments
*/
#include <iostream>
#include <cassert>
#include <filesystem>

#include "mml/Unix.hpp"

#include <cstdlib>  // For std::abort

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
	std::cout << "│ Performing test for Unix.hpp │" << std::endl;
	std::cout << "╰──────────────────────────────╯" << std::endl;

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;
	#ifdef __linux__
	std::cout << "Reading permission of a created file with changed permissions with C++ standard libraries ...";
	std::string file = "/tmp/test_unix";
	std::ofstream output(file);
	std::filesystem::permissions(
        file,
        std::filesystem::perms::owner_write | std::filesystem::perms::group_read | std::filesystem::perms::others_exec,
        std::filesystem::perm_options::add
    );
	std::filesystem::permissions(
        file,
        std::filesystem::perms::owner_read | std::filesystem::perms::owner_exec | std::filesystem::perms::group_exec
		| std::filesystem::perms::group_write | std::filesystem::perms::others_read| std::filesystem::perms::others_write,
        std::filesystem::perm_options::remove
    );

	mml::Unix::permissions perms = mml::Unix::perms(file);
	
	std::filesystem::remove(file);

	assert_msg(perms.owner_write && perms.group_read && perms.others_exec && !perms.owner_read && !perms.others_write, "\nReading permissions failed.");
	std::cout << " Passed" << std::endl;
	
	#else
	std::cout << "Unix only defined for linux-based distributions" << std::endl;
	#endif

	std::cout << std::endl;
	std::cout << "─────────────────────────────────────────────────────" << std::endl;
	std::cout << std::endl;

	
	return 0;
}
