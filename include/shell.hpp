/**
 * @author Mike Moser
 * 
 * Bibliothek shell.h
 * Enthält verschiedene Funktionen mit namespace shell
 * 
*/

#ifndef __SHELL_HPP__
#define __SHELL_HPP__ 
#include <iostream>
#include <vector>
#include <vector.hpp>
#include <functions.hpp>

namespace mml{

		//class string;
		//extern template class vector<string>;

	namespace shell
	{
		class arg : public mml::vector<mml::string> {
		protected:
		
			int argc = 0;
		
			char **argv = {};
 			//std::vector<mml::string> vec = {};
		
		public:
		
			// Mit Initialisierung eins Vektors:
// 			arg(std::vector<mml::string> vec_temp) :  vec(vec_temp){}
			
			// Mit direkter Initialisierung der Argumenten:
			arg(int argc1, char **argv1, bool getarg = false, std::string except1 = "xxxxx", std::string except2 = "xxxxx", std::string except3 = "xxxxx", std::string except4 = "xxxxx", std::string except5 = "xxxxx", std::string except6 = "xxxxx", std::string except7 = "xxxxx") {
				argc	=	argc1;
				argv	=	argv1;
				
				std::vector<mml::string> vec_temp(argv,argv+argc);
				
				vec = vec_temp;
				
				if(getarg)
					getArg(except1, except2, except3, except4,except5,except6,except7);
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
			
			// Mit direkter Wertübergabe:
			//arg(std::vector<mml::string> val) :  arg(val){}
			//arg(const arg &val) :  vec(val.vec){}

			/*arg(mml::vector<mml::string> vec_temp){
				for(uint32_t i = 0; i < vec_temp.size(); i++)
					vec.push_back(vec_temp[i]);
			};*/
			// Ohne direkte Initialisierung:
			arg() {}
			
			arg(arg &vec_copy) {vec = vec_copy.tovec();}	// Kopierkonstruktor
			
// 			arg(const std::vector<mml::string> vec_temp) :  vec(vec_temp){}
			
// 			arg &operator=(std::vector<mml::string> vec_temp){
// 				this->vec = vec_temp;
// 				return *this;
// 			}	// Zuweisung über = an value
// 			
			// Als Kopierkonstruktor:
			arg &operator=(const arg &vec_temp){
				vec = vec_temp.vec;
				return *this;
			}	// Zuweisung über = an value
			
			arg &operator=(const std::vector<std::string> &vec_temp){
				vec = tostr(vec_temp);
				
				return *this;
			}	// Zuweisung über = an value
			/**
			 * @note Initialisierung mit direkter Übergabe der argv und argc Werte
			 * 
			 * @author Mike
			 */
			std::vector<mml::string> &operator()(char **argv1, int argc1, bool getarg = false);		// bestimmte Position ausgeben
			std::vector<mml::string> &operator()(int argc1, char **argv1, bool getarg = false);
			
			
// 			mml::string &operator[](int index);		// bestimmte Position ausgeben
			
			/**
			 * @note Positionsbestimmung, sobald ein String beginnend am Anfang mit einem Wert übereinstimmt
			 * 
			 * @return Position
			 * @author Mike
			 */
			std::size_t beginArg(const std::string& str);
			
			
			/**
			* @note Ausgabe aller Elemente im Vektor
			* 
			* @author Mike
			*/
// 			void cout();
			
			/**
			* @note Ein Element oder mehrere entfernen
			* 
			* @author Mike
			*/
			void erase(std::size_t pos1, std::size_t pos2 = 0);
			
			
			/**
			 * @note nachschauen ob ein String im Vektor vec vorkommt
			 * 
			 * @return true oder false
			 * @author Mike
			 */
			bool exist(std::string search);
			bool exist(std::string search1, std::string search2);
			bool exist(std::string search1, std::string search2, std::string search3);
			bool exist(std::string search1, std::string search2, std::string search3, std::string search4);
			
			/**
			 * @note Nachschauen, ob ein String in einem bestimmten String vorkommt
			 * 
			 * @return true oder false
			 * @author Mike
			 */
			bool exist(std::size_t pos,std::string name);
			
			/**
			 * @note Finden von Argumenten
			 * 
			 * @author Mike
			 */
			bool findArg (const std::string& str);
			bool findArg (const std::string& str1,const std::string& str2) ;
			bool findArg (const std::string& str1,const std::string& str2, const std::string& str3);
			bool findArg (const std::string& str1,const std::string& str2, const std::string& str3, const std::string& str4);
			
			/**
			 * Argumente bei -xyz bestimmen
			 * 
			 * @author Mike
			 */
			void getArg(std::string except1 = "xxxxx", std::string except2 = "xxxxx", std::string except3 = "xxxxx", std::string except4 = "xxxxx", std::string except5 = "xxxxx", std::string except6 = "xxxxx", std::string excep7 = "xxxxx");
			
			/**
			 * @note Initialisierung bei Start zum Ausführen von Standardoperationen
			 * 
			 * @author Mike
			 */
			void init(std::string except1 = "xxxxx", std::string except2 = "xxxxx", std::string except3 = "xxxxx", std::string except4 = "xxxxx", std::string except5 = "xxxxx", std::string except6 = "xxxxx", std::string except7 = "xxxxx");
			
			/**
			 * @note Finden von nicht vorhandenen Argumenten
			 * 
			 * @return true, wenn nicht gefunden
			 * @author Mike
			 */
			bool notArg (const std::string& str1);
			bool notArg (const std::string& str1, const std::string& str2);
			bool notArg (const std::string& str1,const std::string& str2, const std::string& str3);
			bool notArg (const std::string& str1,const std::string& str2, const std::string& str3, const std::string& str4);
			
			/**
			 * @note Positionsbestimmungen, wo ein gesuchter String steht
			 * 
			 * @return Positionnamespace mml{
			 * @author Mike
			 */
			std::size_t positionArg(const std::string& str);
			std::size_t positionArg(const std::string& str, const std::string& str2);
			
			/**
			 * @note Ersetzen eines chars oder eines Strings in einem Vektor
			 * 
			 * @return Vektor mit den ersetzten Werten
			 * @author Mike
			 */
			std::vector<mml::string> replace(char sign_old, char sign_new);
			std::vector<mml::string> replace(std::string str_old, std::string str_new);
			
			/**
			 * @note Nachträgliche Initialisierung der Werte von übergebenen Werten
			 * 
			 * @author Mike
			 */
			
			/**
			 * @note Sortieren der Werte
			 * 
			 * @author Mike
			 */
			void sort();
			
			/**
			 * @note Umwandlungen der Werte in einen Standard String Vektor
			 * 
			 * @return String Vektor
			 * @author Mike
			 */
			std::vector<mml::string> str();	// Umwandlung zu string
			std::vector<std::string> str_change();	// Umwandlung zu std::string
			std::vector<mml::string> tostr(std::vector<std::string> temp); 	// Umwandlung zu mml::string
		
			

			
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
