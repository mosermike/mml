/**
 * @author Mike Moser
 * @file shell.hpp
 * @brief Functions and a class concerning the shell
 * 
*/

#ifndef MML_INCLUDE_MML_SHELL_HPP
#define MML_INCLUDE_MML_SHELL_HPP 
#include <iostream>
#include <vector>
#include "mml/standards.hpp"
#include "mml/vector.hpp"

namespace mml{
	namespace shell
	{
		class arg : public mml::vector<mml::string> {
		private:
		
			int argc = 0;
			char **argv = nullptr;

		public:
			/**
			 * @brief Initialize with the arguments from the main class
			 * @param argc1 Number of arguments
			 * @param argv1 Arguments
			 * @return Instance of the class
			 */
			arg(int argc1, char **argv1) : argc(argc1), argv(argv1){this->vec = std::vector<mml::string>(argv,argv+argc);}

			/**
			 * @brief Initialize with the arguments from the main class
			 * @param argv1 Arguments
			 * @param argc1 Number of arguments
			 * @return Instance of the class
			 */			
			arg(char **argv1, int argc1) : arg(argc1,argv1) {}

			/**
			 * @brief Constructor
			 * @param args Values to be put into the class
			 * @return Instance of the class
			 */
			template <typename... T>
			arg(const T&... args){
				(this->push_back(std::forward<T>(args)), ...);
			}

			/**
			 * @brief Constructor
			 */
			arg(std::vector<std::string> vec_temp){
				for(uint32_t i = 0; i < vec_temp.size(); i++)
					vec.push_back(vec_temp[i]);
			}
			
			/**
			 * @brief Constructor
			 */
			arg() {}
			
			/**
			 * @brief Copy constructor
			 * @param vec_copy Instance of this class
			 * @return Instance of the new created class
			 */
			arg(arg &vec_copy): mml::vector<mml::string>(vec_copy) {vec = vec_copy.tovec();}

			// Als Kopierkonstruktor:
			arg &operator=(const arg &vec_temp){
				vec = vec_temp.vec;
				return *this;
			}
			
			arg &operator=(const std::vector<mml::string> &vec_temp){
				vec = vec_temp;	
				return *this;
			}

			/**
			 * @brief Initialise with the values from the terminal and separated flags given with one minus sign
			 * @param argc1 Number of arguments
			 * @param argv1 Character vector with the arguments from the shell
			 * @param value Values which are not separated
			 * @return Reference to this instance
			 */
			
			template <typename... values>
			std::vector<mml::string> &operator()(int argc1, char **argv1, const values& ...value) noexcept {
				vec = std::vector<mml::string>(argv1,argv1 + argc1);	
				init(value...);
				return vec;
			}

			template <typename... values>
			std::vector<mml::string> &operator()(char **argv1, int argc1, const values& ...value) noexcept {return operator()(argc1,argv1,value...);}
			
			/**
			 * @brief Determine position where an argument starts with a specific string
			 * @param str element starts with this string
			 * @return Position
			 */
			std::size_t begin(const std::string& str) const noexcept;
			
		private:
			void _init(std::vector<mml::string>& excepts) noexcept;
		public:
			/**
			 * @brief Determine options given with one minus and separate them ignoring specific strings
			 * @param value Values which are not separated
			 */
			template <typename... values>
			void init(const values&... value) noexcept {
				std::vector<mml::string> excepts = {value...};
				_init(excepts);
			}
			
			/**
			 * @brief Determine if an element does not exist
			 * @param value values to be looked for
			 * @return true, if values do not exist
			 */
			template <typename... values>
			bool nexist(const values&... value) const noexcept {
				return !exist(value...);
			}
			
			/**
			 * @brief Determine the position of a searched string
			 * @param str Value to be looked for
			 * @return position
			 */
			std::size_t pos(const std::string& str) const noexcept;
			/**
			 * @brief Determine the position of a searched string or another
			 * @param str1 Value to be looked for
			 * @param str2
			 * @return position
			 * @note If str1 exists, then the position of this string is returned. Only if not, then the position of str2 if it exists
			 */
			std::size_t pos(const std::string& str1, const std::string& str2) const noexcept;
			
			/**
			 * @brief Replace a string in each element
			 * @param Old value to be replaced
			 * @param New new value
			 * @return Vector of this instance
			 */
			template<typename T> std::vector<mml::string> replace(T Old, T New) noexcept {
				for(std::size_t i = 0; i < vec.size(); i++)
					vec[i] = vec[i].replace(Old,New);

				return vec;

			}
			
			~arg(){	}
	
		};


		/**
		 * @brief Change background of the shell
		 * @param colour background colour
		 * 
		 */
		void background(string colour);
				
		/**
		 * @brief Print a chapter of a help page
		 * @param text chapter title
		 * @param newline Print a new line
		*/
		void chapter(std::string text,bool newline = true);
				
		/**
		 * @brief Print to the shell
		 * @param text The text to be printed
		 * @param newline New line at the end
		 * @param colour which colour is used for highligting
		 * @note Text within [] is highlighted
		 */
		void cout(mml::string text, bool newline = true, std::string colour = "lightgreen");
				
		/**
		 * @brief Print an error in red colour and exit the program
		 * @param text to be printed
		 * @note This function exits the program
		 */
		void error(std::string text);
		
		/**
		 * @brief Change the formation of printed texts in the shell
		 * @param format Format
		 * @details Possible options are
		 * 		"normal", "fat", "cursive", "underline", "blink", "reverse"
		 * 
		 * @author Mike
		 */
		void formation(string format);
		
		/**
		 * @brief Change printed text colour
		 * @param colour paint of the letters
		 * @details Options are black, darkgray, (light)red, (light)green, brown, yellow, (light)blue, (light)purple, (light)cyan, white, lightgray, normal
		*/
		void letter(string colour);
		
		/**
		 * @brief Reverse changes in the print behaviour of the shell
		 */
		void normal();
		
		/**
		 * @brief Print a note in lightgray
		 * @param text to be printed
		 * @param newline print newline
		 */
		void note(std::string text, bool newline = true);
		
		/**
		 * @brief Print an option in a help page
		 * @param option Name of the option used
		 * @param descr Description of the option
		*/
		void option(std::string option,std::string descr);
	
		/**
		 * @brief Input of a password
		 * @param print text to be printed when the code asks for the password
		 * @param add additional text printed after `print`
		 * @return input
		*/
		std::string password(std::string print, std::string add);
		
		/**
		 * @brief Print a warning and exit the program
		 * @param text Text to be printed
		 * @param newline Print new line
		*/
		void warn(std::string text,bool newline = true);
		/**
		 * @brief Print a warning without exiting the program
		 * @param text Text to be printed
		 * @param newline Print a new line
		*/
		void warn_opt(std::string text,bool newline = true);
		

	}
}
#endif
