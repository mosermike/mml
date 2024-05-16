/**
 * @author Mike Moser
 * 
 * @file standards.hpp 
 * @note Enthält verschiedene Standardfunktionen
 * 
*/

#ifndef __STANDARDS_HPP__
#define __STANDARDS_HPP__

// #include <standards.hpp>
// #include <vector.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include <random>
#include <float.h>

// TODO replace nur einmal

namespace mml {
	
	namespace shell{
		class arg;
	}
	
	
	class string{

	private:
		std::string 				value		= "";
		std::string 				temp		= "";
		std::string 				save_value 	= "";
		
	public:
		// copy consructor
// 		string(const string& temp) : value(temp.value){}
		// Mit direkter Wertübergabe:
		string(const char* val) :  value((std::string)val){}
		// Mit Stringvariable als Wert:
		string(std::string val) :  value(val){}
		// Mit double Wertübergabe NOTE geht nicht, kleine Zahlen werden zu null
// 		string(double val){
// 			std::ostringstream stream;
// 			stream << val;
// 			value =  stream.str();}
		// Ohne direkte Initialisierung:
		string(){}
		
		string &operator=(const char* value_direct){
			this->value= std::string(value_direct);
			this->save_value = this->value;
			return *this;
			
			
		}	// Eingabe eines Strings mit = mit Umwandlung
		
		
		string &operator=(std::string value_undirect){
			this->value = value_undirect;
			save_value = value;
			return *this;
		}	// Zuweisung über = an value
		
		string &operator=(double value){
			this->value = std::to_string(value);
			save_value = value;
			return *this;
		}	// Zuweisung über = an value
		
		string &operator=(int value){
			this->value = std::to_string(value);
			save_value = value;
			return *this;
		}	// Zuweisung über = an value
		
		string &operator=(char value){
			this->value += value;
			save_value = value;
			return *this;
		}	// Zuweisung über = an value
		
		friend std::ostream& operator<< (std::ostream &out, const string &String){		// Ausgabe über std::cout
			out << String.value;
			return out;
		}
		
		friend std::istream& operator>> (std::istream &in, string &String){
			in >> String.value;
			return in;
		}
		
		/**
		*  @note Zuweisungen
		*
		*  @author Mike
		*/
		bool operator==(const std::string test);
		bool operator==(mml::string test);
		bool operator==(const char* test);
		bool operator!=(const std::string test);
		bool operator!=(mml::string test);
		bool operator!=(const char* test);
		mml::string operator+(const char* add);
		mml::string operator+(const std::string add);				// Zwei Strings addieren
		mml::string operator+(mml::string add);
		mml::string operator+=(const char* add);
		mml::string operator+=(const std::string add);				// Zwei Strings addieren
		mml::string operator+=(mml::string add);	// Zwei Strings addieren
		
		/**
		 * @note Bestimmte position im String ausgeben
		 * 
		 * @return Char
		 * @author Mike
		*/
		char &operator[](int index);		// bestimmte Position ausgeben
		
		std::string &operator()();		// value zurückgeben, wenn in Klammern
		/**
		 * @note Wert des String in einen Double umwandeln
		 * 
		 * @return value als double
		 * @author Mike
		 */
		double atof();
		/**
		 * @note Wert des String in einen Integer umwandeln
		 * 
		 * @return value als int
		 * @author Mike
		 */
		int atoi();
		/**
		* @note Wert des Strings Value als char pointer zurückgeben
		* 
		* @return char pointer value
		* @author Mike
		*/
		const char* c_str();
		
		/**
		 * @note Zählen wie oft ein String vorkommt
		 * 
		 * @return uint32_t
		 * @author Mike
		 */
		uint32_t count(mml::string name);
		
		/**
		 * @note Wert ausgeben
		 * 
		 * @author Mike
		 */
		void cout(bool newline = true, std::string text = "");
		/**
		 * @note Buchstaben löschen
		 * 
		 * @return String ohne Buchstaben
		 * @author Mike
		 */
		  std::string del_letter(bool save = false);
		
		/**
		 * @note Zahlen löschen
		 * 
		 * @return String ohne Zahlen
		 * @author Mike
		 */
		std::string del_number(bool save = false);
		/**
		 * @note Alles nach einem Space löschen
		 * 
		 * @return String kürzen bis Space
		 * @author Mike
		 */
		  std::string del_space(bool save = false);
		/**
		 * @note Nachschauen, ob ein String in einem String vorkommt
		 * 
		 * @return true oder false
		 * @author Mike
		 */
		bool exist(std::string name);
		bool exist(std::string name1, std::string name2);
		bool exist(std::string name1, std::string name2, std::string name3);
		bool exist(std::string name1, std::string name2, std::string name3, std::string name4);
		
		/** 
		 * @note Überprüfen, ob ein String existiert
		 * 
		 * @param char/string Value
		 * @param size_t Value from where to search for the char (optional)
		 * @return Position
		 * @author Mike
		 */
		std::size_t find(char letter){return value.find(letter);}
		std::size_t find(char letter,std::size_t old){return value.find(letter,old);}
		std::size_t find(mml::string name){return value.find(name.str());}
		std::size_t find(mml::string name,std::size_t old){return value.find(name.str(),old);}
		
		/**
		 * @note Check if a string exists but starting from the right side
		 *
		 * @param name String to look for
		 * @param pos Value from where to search for the string. 0 means that it is not used. (optional, default 0)
		 * @param low Lower limit to which point is searched for (optional, default 0)
		 * @return Position
		 * @author Mike
		 */
		std::size_t find_back(mml::string name, std::size_t pos = 0, std::size_t low = 0);

		/**
		 * @note Linie aus einer Datei lesen
		 *
		 * @return String
		 * @author Mike
		 */
		void getline(std::ifstream& input);
		std::string getline(std::string input);
		std::string getline(std::string input,uint32_t line);
		
		/**
		* @note Wert des Strings Value zurückgeben
		* 
		* @return String value
		* @author Mike
		*/
		std::string getValue();
		
		/**
		 * @note Hash Wert von einem String erstellen
		 * 
		 * @return Hashwert als unsigned integer
		 * @author Mike
		 */
		uint32_t hash();
           
		/**
		* @note Eine Zeile in eine log Datei schreiben
		* 
		* @author Mike
		*/
		void log (std::string logpath);
		
		/**
		* @note Alle Werte im String als Kleinbuchstaben
		* 
		* @return String mit Kleinbuchstaben
		* @author Mike
		*/
		std::string lower();
		/**
		* @note Alle Datei und Ornder auflisten in einem Pfad, nur Dateien mit Inhalt name
		* 
		* @return Vektor mit den Ordnern (endet mit '/') und Dateien
		* @author Mike
		*/
		std::vector<std::string> ls(mml::shell::arg args, std::string name_include, std::string name_exclude, std::vector<std::string> &directories);
		std::vector<std::string> ls(mml::shell::arg args, std::string name_include = "", std::string name_exclude = "");
			
		/**
		* @note Erstellen eines Ordners
		* 
		* @author Mike
		*/
		bool mkdir_p();
		
		/**
		 * @note value als File löschen (mit Überprüfung)
		 * 
		 * @author Mike
		 */
		bool remove();
			
		/** // TODO ÜBERARBEITEN!!! endless schleife wenn str_old in str_new
		* @note Zeichen in einem String ersetzen
		* @note String in einem String ersetzen
		* @param char Find this character or string
		* @param char New character or string
		* @param bool Save the change in this class (False)
		* @param size_t Start from this position to replace (0)
		* @param bool Replace all strings which exist (True)
		* @return String mit den ersetzten Zeichen
		* @author Mike
		*/

		std::string replace(char sign_old, char sign_new, bool save = false, std::size_t pos = 0, bool all = true);
		std::string replace(mml::string str_old, mml::string str_new, bool save = false, std::size_t pos = 0, bool all = true);
		std::string replace(std::string str_old1, std::string str_new1, std::string str_old2, std::string str_new2, bool save = false, std::size_t pos = 0, bool all = true);
	
	private:
		std::string replace_intern(mml::string str_old, mml::string str_new, std::size_t pos, bool save = false);

	public:
		/** 
		 * @note Get position of last occurance of a character
		 * 
		 * @param char value
		 * @return position
		 * @author Mike
		 */
		std::size_t rfind(char letter){return value.rfind(letter);}
		/**
		* @note Wert des Strings Value setzen
		* @param new_value New string
		* @return neuer value Wert
		* @author Mike
		*/
		std::string setString(std::string new_value);
		
		/**
		* @note Größe des Strings berechnen
		* 
		* @author Mike
		*/
		
		std::size_t size();
		
		/**
		 * @note Bilden eines Substrings
		 * 
		 * @param pos1 size_t of start position
		 * @param length1 size_t of length
		 * 
		 * @return gekürzter String
		 * 
		 * @author Mike
		*/
		mml::string substr(std::size_t pos1, std::size_t length1);

		/**
		 * @note Bilden eines Substrings
		 * 
		 * @param pos1 size_t of start position to the end
		 * 
		 * @return gekürzter String
		 * 
		 * @author Mike
		*/
		mml::string substr(std::size_t pos1);
		
		/**
		 * @note Bilden eines Unterstrings mit Angabe der Anfangs- und Endposition
		 * 
		 * @param beg Start of the new string
		 * @param end End of the new string
		 * 
		 * @return gekürzter String
		 * @author Mike
		 */
		mml::string sub(std::size_t beg, int32_t end);
		
		/**
		* @note Wert des Strings Value als int zurückgeben
		* 
		* @return int value
		* @author Mike
		*/
		int stoi();
		
		/**
		* @note Wert des Strings Value zurückgeben
		 *
		 * 
		 * @return String value
		 * @author Mike
		*/
		std::string str();
		
		/**
		 * @note Linie in eine Datei schreiben
		 * 
		 * @param output Filestream for the output
		 * 
		 * @author Mike
		 */
		void writeline(std::ofstream& output);

		/**
		 * @note Linie in eine Datei schreiben
		 * 
		 * @param output String of the filepath to write in
		 * 
		 * @author Mike
		 */
		void writeline(std::string output);
		
		~string(){} // Destruktor
	};
	
	/**
	* @note Variable zu bool
	 * 
	 * @param t Variable to bool
	 * 
	 * @return true oder false
	 * @author Mike
	*/
	template<typename T> double atob(const T& t) {
		std::ostringstream stream;
		
		stream << t;
		
		
		return (std::atoi((stream.str().c_str())) > 0) ? true : false;
	}
	
	/**
	 * @note string zu double
	 * 
	 * @param t String to be changed into a double
	 * @return double
	 * @author Mike
	 */
	template<typename T> double atof(const T& t) {
		std::ostringstream stream;
		
		stream << t;
		
		return std::atof(stream.str().c_str());
	}
	
	/**
	 * @note string zu int
	 * 
	 * @param t String to be changed into an integer
	 * @return Integer
	 * 
	 * @author Mike
	 */
	template<typename T> int atoi(const T& t) {
		std::ostringstream stream;
		
		stream << t;
		
		return std::atoi(stream.str().c_str());
	}
	
	/**
	 * @note Überprüft, ob ein Programm als root ausgeführt wird
	 * 
	 * @param args Arguments passed for check_root
	 * 
	 * @author Mike
	 */
	bool check_root(mml::shell::arg args);
	
	/**
	 * @note Ausgabe der Werte eines Vektors
	 * 
	 * @param vec Vector which is printed out
	 * 
	 * @author Mike
	 */
	template <typename T> void cout (std::vector<T> const& vec);
	
	/**
	 * @note Ausgabe des aktuellen Datums oder der Uhrzeit 
	 * 
	 * @param info Determines what information is printed
	 * @param time1 Time for which the information is printed. Default is -1 => Actual time now.
	 * 
	 * @return unsigned Integer Wert der gewünschten Information(Tag, Monat, Jahr, Sekunden, etc.)
	 * @author Mike
	*/
	uint32_t date(int info, time_t time1 = -1);
	
	/**
	 * @note Ausgabe des aktuellen Datums oder der Uhrzeit als String
	 * 		 Mögliche Auswahl: "Datum", "Uhrzeit", "Datum+Uhrzeit", Default:"Datum"
	 * 
	 * @param value Determines what information is printed. <br>
	 *              "Datum"          : DD.MM.YYYY (based on trennzeichen2) <br>
	 * 				"Zeit"           : HH:MM:SS  (based on trennzeichen1) <br>
	 *              "Datum+Uhrzeit"  : Complete date in format DD.MM.YYYY HH:MM:SS. <br>
	 *              "Datum1+Uhrzeit" : Compete date in format YYYY.MM.DD HH:MM:SS.
	 * @param trennzeichen1 First separation sign for the date
	 * @param trennzeichen2 Second separation sign for the time
	 * 
	 * @return unsigned Integer Wert der gewünschten Information(Tag, Monat, Jahr, Sekunden, etc.)
	 * @author Mike
	*/
	std::string date(mml::string value = "Datum", std::string trennzeichen1 = ":", std::string trennzeichen2 = ".");
	
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
