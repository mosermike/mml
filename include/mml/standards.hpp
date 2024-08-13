/**
 * @author Mike Moser
 * 
 * @file standards.hpp 
 * @details Contains several standard functions and the class string
 * 
*/

#ifndef MML_INCLUDE_MML_STANDARDS_HPP
#define MML_INCLUDE_MML_STANDARDS_HPP

#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include <random>
#include <float.h>
#include <iostream>

#include "mml/definitions.hpp"
#include "mml/string.hpp"

namespace mml {
	/**
	 * @brief Converts value to bool
	 * @param t Value
	 * @return bool
	*/
	template<typename templ> double atob(const templ& t) noexcept {
		std::ostringstream stream;
		
		stream << t;
		
		
		return (std::atoi((stream.str().c_str())) > 0) ? true : false;
	}
	
	/**
	 * @brief Converts value to bool
	 * @param t Value
	 * @return double
	*/
	template<typename T> double atof(const T& t) noexcept {
		std::ostringstream stream;
		
		stream << t;
		
		return std::atof(stream.str().c_str());
	}
	
	/**
	 * @brief Converts value to int
	 * 
	 * @param t Value
	 * @return int
	*/
	template<typename T> int atoi(const T& t) noexcept {
		std::ostringstream stream;
		
		stream << t;
		
		return std::atoi(stream.str().c_str());
	}
	
	/**
	 * @brief Check if program executed as root
	 * @param programme Programme name
	 * @param logpath Path to the logfile, by default "" which means it is not used
	 * @return true if root
	 * @return false if not root
	 * @throw runtime_error : if user is not root
	 */
	bool check_root(std::string programme = "", mml::string logpath = "");
	
	/**
	 * Prints the values of a vector
	 * 
	 * @param vec Vector to be printed
	 */
	template <typename templ> void cout (std::vector<templ> const& vec) noexcept {
	for(uint32_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << std::endl;    //Ausgabe aller Werte
	}
	
	/**
	 * @brief Returns the wished info from the time (like date etc.)
	 * Options are:
	 * - 0: Seconds
	 * - 1: Minutes
	 * - 2: Hours
	 * - 3: Day 
	 * - 4: Month
	 * - 5: Year
	 * - 6: Summertime
	 * - 7: Weekday (Days since sunday)
	 * - 8: Yearday (Days since New Year)
	 * - 9: kw
	 * 
	 * @param info Determines what information is printed
	 * @param time1 Time for which the information is printed. -1 => Actual time now.
	 * @return unsigned integer
	 * @author Mike
	*/
	uint32_t date(int info, time_t time1 = -1) noexcept;

	/**
	 * @brief Returns the date and/or time as a std::string
	 * @param time1 Time for which the information is printed. -1 => Actual time now
	 * @param value Determines what information is printed.
	 *              - "Date" : DD.MM.YYYY (based on separator1)
	 *              - "Time" : HH:MM:SS  (based on separator1)
	 *              - "Date+Time"  : Complete date in format DD.MM.YYYY HH:MM:SS.
	 *              - "Date1+Time" : Compete date in format YYYY.MM.DD HH:MM:SS.
	 * @param separator1 First separation sign for the date
	 * @param separator2 Second separation sign for the time
	 * 
	 * @return std::string
	 * @author Mike
	*/
	std::string date(time_t time1 = -1, mml::string value = "Date+Time", std::string separator1 = ":", std::string separator2 = ".") noexcept;

	/**
	 * @brief Checks if a character is a number
	 * @param c Character to be checked
	 * @return bool
	*/
	bool isnum(char c) noexcept;
	/**
	 * @brief Checks if a number has reached the maximum value (std::string::npos)
	 * @param number Number to be checked
	 * @return true : smaller than the maximum value
	 */
	bool range(std::size_t number) noexcept;

	/**
	 * @brief Checks if one of two numbers has reached the maximum value
	 * @param number1 Number to be checked
	 * @param number2 Number to be checked
	 * @return true : at least one number is smaller than the max. value
	 */
	bool range(std::size_t number1, std::size_t number2) noexcept;
	
	/**
	 * @brief round a number
	 * @param number Number which is rounded
	 * @param digits To which digit it is rounded
	 * @return round number
	 */
	double round(double number, uint16_t digits) noexcept;
				 
	/**
	 * @brief Convert value to mml::string
	 * @param t Value to be changed
	 * @return mml::string
	 */
	template<typename T> mml::string to_string(const T& t) noexcept {
		std::ostringstream stream;
		stream << t;
		return stream.str();
	}



	/**
	 * @brief Forms a hash value of a string
	 * @param string String to be converted
	 * @return Hash value
	 */
	constexpr uint32_t const_string_hash(const char *string) noexcept {
		uint32_t	hash_value	= 0;
		uint32_t	prim[169]	= {
				  2,   3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,
				 43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97,	101, 103,
				107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
				181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
				263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347,
				349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431,
				433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509,
				521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607,
				613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691,
				701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797,
				809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883,
				887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991,
				997};
		uint32_t size = 0;
		
		for(uint16_t i = 0;;i++) {
			if(string[i] == '\0') {
				size = i;
				break;
			}
		}
		
		for(uint32_t i = 0; i < size; i++)
			hash_value +=string[i] * prim[i];
				return hash_value;
		}
	
	/**
	 * @brief Convert month number to month string
	 * @param month_nr Month as a number
	 * @return Name of the month as a string
	 */
	std::string declare_month(int month_nr) noexcept;
	
	/**
	 * @brief Empty a vector
	 * @param data Reference to the vector to be erased
	 */
	template <typename templ> void erase(std::vector<templ> &data) noexcept {while(!data.empty()) {data.pop_back();}; return;}
	
	/**
	 * @brief Create a random number in a defined range
	 * @param min Lowest Number
	 * @param max Highes Number
	 * @return generated random number
	 */
	template <typename templ> templ get_random(templ min = 0, templ max=100) noexcept;

	/**
	 * @brief Return the smallest number
	 * @param values Values as a vector
	 * @param pos Start position
	 * @return smallest number
	 * @throw logic_error : if type is non-arithmetic
	 */
	template <typename templ> templ smallest_num(std::vector<templ> values, std::size_t pos = 0);
		
	/**
	 * @brief Create a random, lower-case string
	 * @param letters Number of letters
	 * @param start Add the generated characters to this string 
	 * @return generated string
	 */
	std::string random_str(size_t letters = 10, std::string start = "") noexcept;
		
	/**
	 * @brief Determine number of digits of a double number
	 * @param number the number
	 * @return Number of digits
	 */
	std::size_t digits(double number) noexcept;	

}

#endif
