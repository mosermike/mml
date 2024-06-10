/**
 * @author Mike Moser
 * 
 * Bibliothek shell.h
 * Enthält verschiedene Funktionen mit namespace shell
 * 
*/

#ifndef MML_INCLUDE_MML_SHELL_HPP
#define MML_INCLUDE_MML_SHELL_HPP 
#include <iostream>
#include <vector>
#include "mml/vector.hpp"

namespace mml{

		//class string;
		//extern template class vector<string>;

	namespace shell
	{
		class arg : public mml::vector<mml::string> {
		protected:
		
			int argc = 0;
			char **argv = {};

		public:
		
			arg(int argc1, char **argv1) {
				argc	=	argc1;
				argv	=	argv1;
				
				std::vector<mml::string> vec_temp(argv,argv+argc);
				
				vec = vec_temp;
				
			}	// Aufruf mml::shell::arg arg(argc,argv);
			
			arg(char **argv1, int argc1) {
				
				argc	=	argc1;
				argv	=	argv1;
				
				std::vector<mml::string> vec_temp(argv,argv+argc);
				
				vec = vec_temp;
			}	// Aufruf mml::shell::arg arg(argv,argc);
			
			// Mit direkter Wertübergabe:
			arg(mml::string a){
				vec.push_back(a);
			}
			arg(mml::string a, mml::string b){
				vec.push_back(a);
				vec.push_back(b);
			}
			arg(mml::string a, mml::string b, mml::string c){
				vec.push_back(a);
				vec.push_back(b);
				vec.push_back(c);
			}
			arg(std::vector<std::string> vec_temp){
				for(uint32_t i = 0; i < vec_temp.size(); i++)
					vec.push_back(vec_temp[i]);
			}
			
			arg() {}
			
			arg(arg &vec_copy) {vec = vec_copy.tovec();}	// Kopierkonstruktor
			
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
			std::size_t begin(const std::string& str) noexcept;
			
		private:
			void _init(std::vector<mml::string>& excepts) noexcept;
		public:
			/**
			 * @brief Determine options given with one minus and separate them ignoring specific strings
			 * @param value Values which are not separated
			 */
			template <typename... values>
			void init(const values&... value) noexcept  {
				std::vector<mml::string> excepts = {value...};
				_init(excepts);
			}
			
			/**
			 * @brief Determine if an element does not exist
			 * @param value values to be looked for
			 * @return true, if values do not exist
			 */
			template <typename... values>
			bool nexist(const values&... value) noexcept {
				return !exist(value...);
			}
			
			/**
			 * @brief Determine the position of a searched string
			 * @param str Value to be looked for
			 * @return position
			 */
			std::size_t pos(const std::string& str) noexcept;
			/**
			 * @brief Determine the position of a searched string or another
			 * @param str1 Value to be looked for
			 * @param str2
			 * @return position
			 * @note If str1 exists, then the position of this string is returned. Only if not, then the position of str2 if it exists
			 */
			std::size_t pos(const std::string& str1, const std::string& str2) noexcept;
			
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
 * @note Hintergrund ändern
 * 
 * @author Mike
 */
void background(string colour);
		
/**
 * @note Hilfeseiteausgabe eines Kapitels 
 * 
 * @author Mike
*/
void chapter(std::string text,bool newline = true);
		
/**
 * @note Ausgabe mit Werten in Klammern in einer Farbe
 * 
 * @author Mike
 */
void cout(mml::string text, bool newline = true, std::string colour = "lightgreen");
		
/**
 * @note Ausgabe eines Errors
 * 
 * @author Mike
 */
void error(std::string text);
		
		/**
		 * @note Formatierung ändern
		 * 
		 * @author Mike
		 */
		void formation(string format1);
		
		/**
		 * @note Schriftfarbe ändern
		 * 
		 * @return 
		 * @author Mike
		*/
		void letter(string colour);
		
		/**
		 * @note Alle Änderungen an der Ausgabe zurücksetzen
		 * 
		 * @author Mike
		 */
		void normal();
		
		/**
		 * @note Eine Notiz ausgeben
		 * 
		 * @author Mike
		 */
		void note(std::string text, bool newline = true);
		/**
		 * @note Finden von übergebenen Argumente(n) 
		 * 
		 * @author Mike
		*/
		//bool findArg(const std::vector<std::basic_string<char> >& args, const std::string& str);
		//bool findArg(const std::vector<string>& args, const std::string& str);
		//bool findArg(const std::vector<std::string>& args, const std::string& str1,const std::string& str2);
		//bool findArg(const std::vector<string>& args, const std::string& str1,const std::string& str2);
		//bool findArg(const std::vector<std::string>& args, const std::string& str1,const std::string& str2, const std::string& str3);
		//bool findArg(const std::vector<string>& args, const std::string& str1,const std::string& str2, const std::string& str3);
		
		/**
		 * @note Ausgabe einer Option von einer Hilfeseite 
		 * 
		 * @author Mike
		*/
		void option(std::string chapter,std::string option);
	
		/**
		 * @note Eingabe eines verdeckten Strings 
		 * 
		 * @return eingegebener String
		 * @author Mike
		*/
		std::string password(std::string ausgabe, std::string source);
		
		/**
		 * @note Ausgabe einer Warnung mit exit(warn)W und ohne exit (warn_opt)
		 * 
		 * @author Mike
		*/
		void warn(std::string text,bool newline = true);
		/**
		 * @note Ausgabe einer Warnung mit exit(warn)W und ohne exit (warn_opt)
		 * 
		 * @author Mike
		*/
		void warn_opt(std::string text,bool newline = true);
		

	}
	
		
	namespace functions{
		typedef mml::shell::arg vector;	
	}
}
#endif
