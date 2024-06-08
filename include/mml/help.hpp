/**
 * @author Mike Moser
 * @file help.hpp
 * @brief Contains functions to print help pages
 * 
*/

#ifndef MML_INCLUDE_MML_HELP_HPP
#define MML_INCLUDE_MML_HELP_HPP

#include <iostream>
#include <string>

namespace mml {
	namespace help {
		
		// move help pages to the programmes
		//void check_root();
		//void cifs();
		//void convert();
		//void cop();
		//void copy();
		//void farben();
		//void finanzen();
		//void hhelp();
		//void hhelp_commands();
		//void R_cop();
		// TODO void R_nas();
		//void R_dns_filter();
		//void rechner();
		//void sizeof_h();
		//void statistik();
		////void timer();
		//void todos();
		//void userinfo();
		
		/**
		 * @brief Print the foot line with notes to author and date
		 * @param version Version Number
		 * @param month Month
		 * @param year year
		 * @param author Author
		 */
		void foot(std::string version, std::string month, int year, std::string author) noexcept;

		/**
		 * @brief Print out a header
		 * @param command Command of the program
		 */
		void header(std::string command, std::string option="") noexcept;
		
	}
}

#endif
//#endif
