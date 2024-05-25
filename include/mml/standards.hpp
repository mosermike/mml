/**
 * @author Mike Moser
 * 
 * @file standards.hpp 
 * @note Contains several standard functions
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


namespace mml {
	
	namespace shell{
		class arg;
	}
	
	/**
	 * Class string which adds additional functions to std::string
	 * 
	*/
	class string{

	private:
		std::string 				value		= ""; // Value of the string
		std::string 				temp		= ""; // Temporary saved string (only for intern functions)
		
		// only for internal conversions
		template <typename templ> mml::string to_mml(templ val) {
			std::ostringstream stream;
			stream << val;

			mml::string temp;
			temp.value = stream.str();
			return temp;
		}

	public:
		/**
		 * @brief Constructor with a value
		 * @param str Value to be converted to a string
		*/
		template <typename templ> string(templ str) {
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
		template <typename templ> mml::string& operator=(templ str) {
			std::ostringstream stream;
			stream << str;
			value = stream.str();

			temp = value;
			return *this;
    	}
		

		/**
		 * @brief Output the value of the string via a stream
		 * @param String Value
		 * @return ostream
		*/
		friend std::ostream& operator<< (std::ostream &out, const string &String){
			out << String.value;
			return out;
		}
		
		/**
		 * @brief Input the value of the string via a stream
		 * @param String Value
		 * @return ostream
		*/
		friend std::istream& operator>> (std::istream &in, string &String){
			in >> String.value;
			return in;
		}
		
		/**
		*  @brief Operator equal
		*  @param Test Value
		*  @return bool
		*/
		template<typename templ> bool operator==(templ Test) {return to_mml(Test).str() == value ? true : false;}

		/**
		*  @brief Operator unequal
		*  @param Test Value
		*  @return bool
		*/
		template<typename templ> bool operator!=(templ Test) {return to_mml(Test).str() != value ? true : false;}


		/**
		*  @brief Operator add somehting at the end of this instance
		*  @param Test Value to be added
		*  @return mml::string
		*/
		template<typename templ> mml::string operator+(templ Test) {return to_mml(this->value + to_mml(Test).str());}


		/**
		*  @brief Operator add a char vector to this string
		*  @param add Value to be added
		*  @return mml::string
		*/
		template<typename templ> mml::string operator+=(templ add) {this->value += to_mml(add).str(); return *this;}
		
		/**
		 * @brief Return a specific char from the string
		 * @param index Index of the character to be retured
		 * @return char
		*/
		char &operator[](int index);		// bestimmte Position ausgeben
		
		/**
		 * @brief Returns the value
		 * @return Value of the instance as a std::string
		*/
		std::string &operator()();		// value zurückgeben, wenn in Klammern

		/**
		 * @brief Converts this string into a double
		 * @return double
		 * 
		 */
		double atof();

		/**
		 * Convert this string into an integer
		 * 
		 * @return int
		 */
		int atoi();

		// Define iterator types
    using iterator = std::vector<char>::iterator;
    using const_iterator = std::vector<char>::const_iterator;

		/**
		 * @brief Returns an iterator that points to the beginning of the string
		 * @return std::string::iterator
		*/
		std::string::iterator begin() { return value.begin(); }
   		std::string::const_iterator begin() const { return value.begin(); }

		/**
		* @brief Returns the string as a character pointer
		* @return char*
		*/
		const char* c_str();
		
		/**
		 * @brief Clears the string
		 * @return None
		*/
		void clear() {value.clear(); return;};
		/**
		 * @brief Count how often a string appears
		 * @param name String which is counted
		 * @return uint32_t
		 * 
		 */
		uint32_t count(mml::string name);
		
		/**
		 * @brief Print out the value of this instance
		 * @param newline,optional Print newline.
		 * @param text,optional Additional text.
		 * @return None
		 */
		void cout(bool newline = true, std::string text = "");
		
		/**
		 * @brief Delete letters
		 * @param save,optional Save the changed string in this instance.
		 * @return std::string
		 */
		  std::string del_letter(bool save = false);
		
		/**
		 * @brief Delete numbers
		 * @param save,optional Save the changed string in this instance.
		 * @return std::string
		 * 
		 */
		std::string del_number(bool save = false);
		
		/**
		 * @brief Remove everything after the first space
		 * @param save,optional Save the changed string in this instance.
		 * @return std::string
		 */
		  std::string del_space(bool save = false);

		/**
		 * @brief Checks if the string is empty
		 * @return bool
		 */
		  bool empty() {return value.empty();};

		/**
		 * @brief Returns an iterator that points to the end of the string
		 * @return std::string::iterator
		*/
    	std::string::iterator end() { return value.end(); }
    	std::string::const_iterator end() const { return value.end(); }

	private:
		/**
		 * @brief Check if a string exists
		 * @param name String to be checked
		 * @return bool
		 */
		bool _exist(std::string name);

	public:
		/**
		 * @brief Check if one *or* another string exists
		 * @param args Parameters to be checked
		 * @return bool
		 */
		template<typename... Args> bool exist(const Args&... args) {
    		return (... || _exist(to_mml(args).str()));
		}
		
		/** 
		 * Position of the first appearance of a character after a start position
		 * 
		 * @param char Value
		 * @param size_t,optional Value from where to search for the char.
		 * @return Position
		 * @author Mike
		 */
		std::size_t find(char letter,std::size_t old = 0){return value.find(letter,old);}
		/** 
		 * Position of the first appearance of a string after a start position
		 * 
		 * @param string Value
		 * @param size_t,optional Value from where to search for the char.
		 * @return Position
		 * @author Mike
		 */
		std::size_t find(mml::string name,std::size_t old = 0){return value.find(name.str(),old);}
		
		/**
		 * @note Check if a string exists but starting from the right side
		 *
		 * @param name String to look for
		 * @param std::size_t,optional Value from where to search for the string. 0 means that it is not used.
		 * @param std::size_t,optional Lower limit to which point is searched for.
		 * @return std::size_t
		 * 
		 */
		std::size_t find_back(mml::string name, std::size_t pos = 0, std::size_t low = 0);

		/**
		 * Reads a line from an input file stream and assigns it to the instance
		 * @param std::ifstream
		 * @return None
		 * 
		 */
		void getline(std::ifstream& input);
		
		/**
		 * Reads a line from a file
		 * @param string File name
		 * @param std::size_t,optional Line number.
		 * @return std::tring
		 * 
		 */
		std::string getline(std::string input,std::size_t line = 0);
		
		/**
		* Get the value of this instance
		* @return std::string
		* 
		*/
		std::string getValue();
		
		/**
		 * Creates a hash value of this instance. This hash value can then be used for example in an switch ... case with strings by using hash values.
		 * 
		 * @return uint32_t
		 * 
		 */
		uint32_t hash();
           
		/**
		 * Writes the value of this instance into a log file
		 * @param std::string Path to the logfile
		 * @return None
		 */
		void log (std::string logpath);
		
		/**
		* Transforms all letters into low case letters
		* @return std::string
		*/
		std::string lower();
		
		/**
		* List all files and directories in a path. Directories end with '/' in the entry
		* @note If name_include or name_exclude is detected for a directory, all the elements in this directory are either included or excluded, respectively.
		* @param std::string Only list files or directories which include this string in the name.
		* @param std::string Exclude files or directories with this string in the name
		* @param std::vector<std::string> Reference to a vector where the directories are added
		* @param bool Check directory recursively
		* @param bool Also list hidden files
		* @return std::vector<std::string>
		* @author Mike
		*/
		std::vector<std::string> ls(std::string name_include, std::string name_exclude, std::vector<std::string> &directories, bool recursive = false, bool all = false);
		
		/**
		* List all files and directories in a path. Directories end with '/' in the entry
		* @note If name_include or name_exclude is detected for a directory, all the elements in this directory are either included or excluded, respectively.
		* @param std::string Only list files or directories which include this string in the name.
		* @param std::string Exclude files or directories with this string in the name
		* @param bool Check directory recursively
		* @param bool Also list hidden files
		* @return std::vector<std::string>
		* @author Mike
		*/
		std::vector<std::string> ls(std::string name_include = "", std::string name_exclude = "", bool recursive = false, bool all = false);
			
		/**
		* Create directory with creating parent directories
		* @return bool
		*/
		bool mkdir_p();
		
		/**
		 * Remove the file with the value of the instance
		 * @return bool
		 */
		bool remove();
			
		/**
		* Replace sth in the string with sth else
		* @param str_old Replace this value
		* @param str_new Replaced with this value
		* @param pos Start from this position to replace
		* @return mml::string
		*/
		template <typename T> mml::string replace(T str_old, T str_new, std::size_t pos = 0) {
			mml::string str_old1(str_old);
			mml::string str_new1(str_new);

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
		 * Get position of last occurance of a character
		 * @param char Value to be found
		 * @return std::size_t
		 */
		std::size_t rfind(char letter){return value.rfind(letter);}
		
		/**
		 * Compute size of the string
		 * @return std::size_t
		 */
		
		std::size_t size();
		
		/**
		 * Create substring 
		 * @param pos1 Start position
		 * @param length1 Length of the string
		 * @return mml::string
		*/
		mml::string substr(std::size_t pos1, std::size_t length1);

		/**
		 * Create a substring starting from this position to the end
		 * @param pos1 Start position to the end
		 * @return mml::string
		*/
		mml::string substr(std::size_t pos1);
		
		/**
		 * @brief Create a substring starting and ending of specific positions
		 * @param beg Start of the new string
		 * @param end End of the new string
		 * @return mml::string
		 */
		mml::string sub(std::size_t beg, std::size_t end);
		
		/**
		* Transform this instance to an integer
		* @return int
		*/
		int stoi();
		
		/**
		 * Return the value of this instance as a std::string
		 * @return std::string
		*/
		std::string str();
		
		/**
		 * Write this instance into the end of a file 
		 * @param std::ofstream Write to this output file stream
		 * @return None
		 */
		void writeline(std::ofstream& output);

		/**
		 * Write this instance into the end of a file
		 * @param std::string Path to the file
		 * @return None
		 */
		void writeline(std::string output);
		
		~string(){} // Destruktor
	};
	
	/**
	 * Converts value to bool
	 * 
	 * @param templ Value
	 * @return bool
	 * @author Mike
	*/
	template<typename templ> double atob(const templ& t) {
		std::ostringstream stream;
		
		stream << t;
		
		
		return (std::atoi((stream.str().c_str())) > 0) ? true : false;
	}
	
	/**
	 * Converts value to bool
	 * 
	 * @param templ Value
	 * @return double
	 * @author Mike
	*/
	template<typename T> double atof(const T& t) {
		std::ostringstream stream;
		
		stream << t;
		
		return std::atof(stream.str().c_str());
	}
	
	/**
	 * Converts value to int
	 * 
	 * @param templ Value
	 * @return int
	 * @author Mike
	*/
	template<typename T> int atoi(const T& t) {
		std::ostringstream stream;
		
		stream << t;
		
		return std::atoi(stream.str().c_str());
	}
	
	/**
	 * Check if program executed as root
	 * @param std::string,optional Programme name
	 * @return bool
	 */
	bool check_root(std::string programme = "");
	
	/**
	 * Prints the values of a vector
	 * 
	 * @param std::vector<templ> Vector to be printed
	 */
	template <typename templ> void cout (std::vector<templ> const& vec){
	for(uint32_t i = 0; i < vec.size(); i++)
		std::cout << vec[i] << std::endl;    //Ausgabe aller Werte
	}
	
	/**
	 * Returns the wished info from the time (like date etc.)
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
	 * @param int Determines what information is printed
	 * @param time_t Time for which the information is printed. -1 => Actual time now.
	 * @return unsigned integer
	 * @author Mike
	*/
	uint32_t date(int info, time_t time1 = -1);

	/**
	 * Returns the actual date and/or time as a std::string
	 * @param mml::string Determines what information is printed.
	 *              - "Date" : DD.MM.YYYY (based on separator1)
	 *              - "Time" : HH:MM:SS  (based on separator1)
	 *              - "Date+Time"  : Complete date in format DD.MM.YYYY HH:MM:SS.
	 *              - "Date1+Time" : Compete date in format YYYY.MM.DD HH:MM:SS.
	 * @param std::string,optional First separation sign for the date
	 * @param std::string,optional Second separation sign for the time
	 * 
	 * @return std::string
	 * @author Mike
	*/
	std::string date(mml::string value, std::string separator1 = ":", std::string separator2 = ".");

	/**
	 * Checks if a character is a number
	 * @param char Character to be checked
	 * @return bool
	*/
	bool is_num(char c);
	/**
	 * @note Überprüfen, ob maximalert Wert von std::size_t erreicht
	 * 
	 * @param number Number to be checked
	 * 
	 * @return true (kleiner als max Wert) oder false
	 * @author Mike
	 */
	bool range(std::size_t number);

	/**
	 * @note Überprüfen, ob maximalert Wert von std::size_t erreicht
	 * 
	 * @param number1 Number to be checked
	 * @param number2 Number to be checked
	 * 
	 * @return true (kleiner als max Wert) oder false
	 * @author Mike
	 */
	bool range(std::size_t, std::size_t);
	
	/**
	 * @note Zahl runden
	 * 
	 * @param number Number which is rounded
	 * @param digits To which digit it is rounded
	 * 
	 * @return gerundete double Zahl 
	 * @author Mike
	 */
	double round(double number, uint16_t digits);
				 
	/**
	 * @note Wert in mml::string umwandeln
	 * 
	 * @param t Value to be changed
	 * @return mml::string
	 * @author Mike
	 */
	template<typename T> mml::string to_string(const T& t) {
		std::ostringstream stream;
		
		stream << t;
		
		return stream.str();
	}
	
// 	template<typename T> T toT(mml::string s) {
// 				std::istringstream stream (s.str());
// 				
// 				T t;
// 				stream >> t;
// 				
// 				return t;
// 	}

}

#endif
