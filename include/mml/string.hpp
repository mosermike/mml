/**
 * @file string.hpp
 * @author Mike Moser
 * @brief Own string implementation with additional functions to std::string
 * @version 1.0
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#ifndef MML_INCLUDE_MML_STRING_HPP
#define MML_INCLUDE_MML_STRING_HPP

#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include <random>
#include <float.h>
#include <iostream>

#include "mml/definitions.hpp"


namespace mml {
	/**
	 * Class string which adds additional functions to std::string
	 * 
	*/
	class string{

	private:
		std::string 				value		= ""; // Value of the string
		std::string 				temp		= ""; // Temporary saved string (only for intern functions)
		
		// only for internal conversions
		template <typename templ> mml::string to_mml(templ val) const noexcept {
			std::ostringstream stream;
			stream << val;

			mml::string temp;
			temp.value = stream.str();
			return temp;
		}
		// Define iterator types
		using iterator = std::vector<char>::iterator;
    	using const_iterator = std::vector<char>::const_iterator;
	public:
		/**
		 * @brief Constructor with a value
		 * @param str Value to be converted to a string
		*/
		template <typename templ> string(templ str) noexcept {
			std::ostringstream stream;
			stream << str;
			value = stream.str();
			temp = value;
    	}

		/**
		 * @brief Constructor creating n times the char c
		 * @param n how often the character c should appear
		 * @param c Character which appears n times
		*/
		string(size_t n, char c) : value(std::string(n,c)) {}
		
		/**
		 * @brief Constructor without a value
		*/
		string(){}
		
		/**
		 * @brief Assign the value of the template type with the '=' sign 
		 * @param str Value
		 * @return Class instance
		*/
		template <typename templ> mml::string& operator=(templ str) noexcept {
			std::ostringstream stream;
			stream << str;
			value = stream.str();

			temp = value;
			return *this;
    	}
		

		/**
		 * @brief Output the value of the string via a stream
		 * @param out output stream
		 * @param String Value
		 * @return ostream
		*/
		friend std::ostream& operator<< (std::ostream &out, const string &String) noexcept {
			out << String.value;
			return out;
		}
		
		/**
		 * @brief Input the value of the string via a stream
		 * @param in Input stream
		 * @param String Value
		 * @return istream
		*/
		friend std::istream& operator>> (std::istream &in, string &String) noexcept{
			in >> String.value;
			return in;
		}
		
		/**
		*  @brief Operator equal
		*  @param Test Value
		*  @return bool
		*/
		template<typename templ> bool operator==(templ Test) const noexcept {return to_mml(Test).str() == value ? true : false;}

		/**
		*  @brief Operator unequal
		*  @param Test Value
		*  @return bool
		*/
		template<typename templ> bool operator!=(templ Test) const noexcept {return to_mml(Test).str() != value ? true : false;}


		/**
		*  @brief Operator add somehting at the end of this instance
		*  @param Test Value to be added
		*  @return mml::string
		*/
		template<typename templ> mml::string operator+(templ Test) const noexcept{return to_mml(this->value + to_mml(Test).str());}


		/**
		*  @brief Operator add a char vector to this string
		*  @param add Value to be added
		*  @return mml::string
		*/
		template<typename templ> mml::string operator+=(templ add)  noexcept{this->value += to_mml(add).str(); return *this;}
		
		/**
		 * @brief Return a specific char from the string
		 * @param index Index of the character to be retured
		 * @return char
		 * @throw logic_error : if out of range
		*/
		char& operator[](int index);
		const char& operator[](int index) const;
		
		/**
		 * @brief Returns the value
		 * @return Value of the instance as a std::string
		*/
		std::string &operator()() noexcept;
		const std::string &operator()() const noexcept;

		/**
		 * @brief Converts this string into a double
		 * @return double
		 */
		double atof() const noexcept;

		/**
		 * @brief Convert this string into an integer
		 * @return int
		 */
		int atoi() const noexcept;

		/**
		 * @brief Returns an iterator that points to the beginning of the string
		 * @return std::string::iterator
		*/
		std::string::iterator begin() noexcept { return value.begin(); }

		/**
		 * @brief Returns an iterator that points to the beginning of the string
		 * @return std::string::const_iterator
		*/
   		std::string::const_iterator begin() const noexcept { return value.begin(); }

		/**
		* @brief Returns the string as a character pointer
		* @return char*
		*/
		const char* c_str() const noexcept;
		
		/**
		 * @brief Clears the string
		 * @return None
		*/
		void clear() noexcept {value.clear(); return;};
		/**
		 * @brief Count how often a string appears
		 * @param name String which is counted
		 * @return uint32_t
		 * 
		 */
		uint32_t count(mml::string name) const noexcept;
		
		/**
		 * @brief Print out the value of this instance
		 * @param newline Print newline.
		 * @param text Additional text.
		 * @return None
		 */
		void cout(bool newline = true, std::string text = "") const noexcept;
		
		/**
		 * @brief Delete letters
		 * @param save Save the changed string in this instance.
		 * @return std::string
		 */
		  std::string del_letter(bool save = false) noexcept;
		
		/**
		 * @brief Delete numbers
		 * @param save Save the changed string in this instance.
		 * @return std::string
		 */
		std::string del_number(bool save = false) noexcept;
		
		/**
		 * @brief Remove everything after the first space
		 * @param save Save the changed string in this instance.
		 * @return std::string
		 */
		  std::string del_space(bool save = false) noexcept;

		/**
		 * @brief Checks if the string is empty
		 * @return bool
		 */
		  bool empty() const noexcept {return value.empty();};

		/**
		 * @brief Returns an iterator that points to the end of the string
		 * @return std::string::iterator
		*/
    	std::string::iterator end() noexcept { return value.end(); }

		/**
		 * @brief Returns an iterator that points to the end of the string
		 * @return std::string::const_iterator
		*/
    	std::string::const_iterator end() const  noexcept { return value.end(); }

	private:
		/**
		 * @brief Check if a string exists
		 * @param name String to be checked
		 * @return bool
		 */
		bool _exist(std::string name) const  noexcept;

	public:
		/**
		 * @brief Check if one *or* another string exists
		 * @param args Parameters to be checked
		 * @return bool
		 */
		template<typename... Args> bool exist(const Args&... args) const noexcept {
    		return (... || _exist(to_mml(args).str()));
		}
		
		/** 
		 * @brief Position of the first appearance of a character after a start position
		 * @param letter Value
		 * @param old Value from where to search for the char.
		 * @return Position
		 */
		std::size_t find(char letter,std::size_t old = 0) const noexcept {return value.find(letter,old);}
		/** 
		 * @brief Position of the first appearance of a string after a start position
		 * @param name Value
		 * @param old Value from where to search for the char.
		 * @return Position
		 */
		std::size_t find(mml::string name,std::size_t old = 0) const noexcept {return value.find(name.str(),old);}

		/**
		 * @brief Reads a line from an input file stream and assigns it to the instance
		 * @param input
		 * @return None
		 */
		void getline(std::ifstream& input) noexcept;
		
		/**
		 * @brief Reads a line from a file
		 * @param input File name
		 * @param line Line number.
		 * @param back Line Number from the back
		 * @return std::string
		 * 
		 */
		std::string getline(const mml::string input,const std::size_t line = 0, bool back = false);
		
		/**
		 * @brief Reads the last line from a file
		 * @param input File name
		 * @return std::string
		 * 
		 * 
		 */
		std::string getlastline(const mml::string input);

		/**
		* @brief Get the value of this instance
		* @return std::string
		*/
		std::string getValue() const noexcept;
		
		/**
		 * @brief Creates a hash value of this instance. This hash value can then be used for example in an switch ... case with strings by using hash values.
		 * @return uint32_t
		 */
		uint32_t hash() const  noexcept;
           
		/**
		 * @brief Writes the value of this instance into a log file
		 * @param logpath Path to the logfile
		 * @return None
		 * @throw runtime_error : if permission to create log file is denied
		 */
		void log (std::string logpath) const;
		
		/**
		* @brief Transforms all letters into low case letters
		* @return std::string
		*/
		std::string lower() noexcept;
		
		/**
		 * @brief List all files and directories in a path. Directories end with '/' in the entry
		 * @param name_include Only list files or directories which include this string in the name.
		 * @param name_exclude Exclude files or directories with this string in the name
		 * @param directories Reference to a vector where the directories are added
		 * @param recursive Check directory recursively
		 * @param all Also list hidden files
		 * @return std::vector<std::string>
		 * @note If name_include or name_exclude is detected for a directory, all the elements in this directory are either included or excluded, respectively.
		 * @throw runtime_error : if the string does not exist
		 */
		std::vector<std::string> ls(std::string name_include, std::string name_exclude, std::vector<std::string> &directories, bool recursive = false, bool all = false) const;
		
		/**
		 * @brief List all files and directories in a path. Directories end with '/' in the entry
		 * @param name_include Only list files or directories which include this string in the name.
		 * @param name_exclude Exclude files or directories with this string in the name
		 * @param recursive Check directory recursively
		 * @param all Also list hidden files
		 * @return std::vector<std::string>
		 * @throw runtime_error : if the string does not exist
		 * @note If name_include or name_exclude is detected for a directory, all the elements in this directory are either included or excluded, respectively.
		 */
		std::vector<std::string> ls(std::string name_include = "", std::string name_exclude = "", bool recursive = false, bool all = false) const;
			
		/**
		* @brief Create directory with creating parent directories
		* @return bool
		*/
		bool mkdir_p() noexcept;
		
		/**
		 * @brief Remove the file with the value of the instance
		 * @return bool
		 */
		bool remove() const noexcept;
			
		/**
		 * @brief Replace sth in the string with sth else
		 * @param str_old Replace this value
		 * @param str_new Replaced with this value
		 * @param pos Start from this position to replace
		 * @return mml::string
		 * @throw invalid_argument : if str_old is empty
		 */
		template <typename T1,typename T2> mml::string replace(T1&& str_old, T2&& str_new, std::size_t pos = 0) {
			 mml::string str_old1(std::forward<T1>(str_old)); // Convert str_old to mml::string
            mml::string str_new1(std::forward<T2>(str_new));

			if (str_old1.empty()) {
				throw std::invalid_argument("The value to be replaced must not be empty.");
			}

			temp = value;

			while ((pos = temp.find(str_old1.str(), pos)) != std::string::npos) {
				temp = temp.replace(pos, str_old1.size(), str_new1.str());
				pos += str_new1.size();  // Move past the new string to avoid infinite loop
			}

			return to_mml(temp);

		}
	
		/** 
		 * @brief Get position of last occurance of a character
		 * @param letter Value to be found
		 * @param pos Position where to begin to search to the right
		 * @param end Position where to stop the search from the right
		 * @return std::size_t
		 */
		std::size_t rfind(char letter, std::size_t pos = std::string::npos, std::size_t end = 0) const noexcept {return value.substr(end).rfind(letter, pos)+end;}
		
		/**
		 * @brief Compute size of the string
		 * @return std::size_t
		 */
		
		std::size_t size() const noexcept;

		/**
		 * @brief Create a substring starting from this position to the end
		 * @param pos1 Start position to the end
		 * @return mml::string
		*/
		mml::string substr(std::size_t pos1) const noexcept;

		/**
		 * @brief Create substring 
		 * @param pos1 Start position
		 * @param length1 Length of the string
		 * @return mml::string
		*/
		mml::string substr(std::size_t pos1, std::size_t length1) const noexcept;
		
		/**
		 * @brief Create a substring starting and ending of specific positions
		 * @param beg Start of the new string
		 * @param end End of the new string
		 * @return mml::string
		 */
		mml::string sub(std::size_t beg, std::size_t end) const noexcept;
		
		/**
		* @brief Transform this instance to an integer
		* @return int
		*/
		int stoi() const noexcept;
		
		/**
		 * @brief Return the value of this instance as a std::string
		 * @return std::string
		*/
		std::string str() const noexcept;
		
		/**
		 * @brief Write this instance into the end of a file 
		 * @param output Write to this output file stream
		 * @return None
		 */
		void writeline(std::ofstream& output) const noexcept;

		/**
		 * @brief Write this instance into the end of a file
		 * @param output Path to the file
		 * @return None
		 */
		void writeline(std::string output) const noexcept;
		
		~string(){} // Destruktor
	};
}
#endif
