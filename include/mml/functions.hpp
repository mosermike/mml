/**
 * @author Mike Moser
 * 
 * @file functions.hpp 
 * @note Enthält verschiedene Funktionen
 * 
*/

#ifndef MML_INCLUDE_MML_FUNCTIONS_HPP
#define MML_INCLUDE_MML_FUNCTIONS_HPP

#include "mml/standards.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <string.h>
#include <random>
#include <float.h>

namespace mml{
	
	namespace shell{
		class arg;
	}
	
	namespace functions {
	
		/**
		 * @note Bilden eines Hashwertes zu einem String
		 * 
		 * @return Hashwert als Integerwert
		 * @author Mike
		 */
		constexpr uint32_t const_string_hash(const char *string){
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
		 * @note Anzahl eines Zeichens bestimmen
		 * 
		 * @author Mike
		 */
		uint32_t count_sym(std::string test, char symbol);
		
		/**
		 * @note Inhalt eines Vektors ausgeben
		 * 
		 * @author Mike
		 */
		void cout(std::vector<std::string> vec);
		void cout(std::vector<mml::string> vec);
		void cout(std::vector<double> vec);
		void cout(std::vector<int> vec);
		
		/**
		 * Den Monatsname zum Monat bestimmen
		 * 
		 * @return Monatsname
		 * @author Mike
		 */
		std::string declare_month(int month_nr);
		
		/**
		 * @note Einen Vektor leeren
		 * 
		 * @return leeren Vektor
		 * @author Mike
		 */
		std::vector<std::string> erase(std::vector<std::string> data);
		std::vector<mml::string> erase(std::vector<mml::string> data);
		std::vector<double> erase(std::vector<double> data);
		std::vector<int> erase(std::vector<int> data);
		
		/**
		 * @note Eine Zufallszahl in bestimmten Grenzen erzeugen
		 * 
		 * @return Zufallszahl
		 * @author Mike
		 */
		int get_random(int min = 0, int max=100);

		/**
		 * @note Eine Linie aus einer geöffneten Datei zurückgeben
		 * 
		 * @return Zeile aus einer Datei
		 * @author Mike
		 */
		//void getline(std::ifstream& input);
		
	
		/**
		 * @note Kleinste Zahl herausfinden
		 * 
		 * @return kleinste Zahl
		 * @author Mike
		 */
		//double smallest_num(std::vector<double> values);
		std::size_t smallest_num(std::vector<std::size_t> values, std::size_t pos = 0);
		/**
		 * @note Anpingen einer IP-Adresse oder eines Strings
		 * 		 mit pip install pyping installieren, wenn nicht vorhanden
		 * 		 -lpython2.7 notwendig
		 * 
		 * @return true, wenn erreichbar
		 * @author Mike
		 */
// 		bool ping(mml::shell::arg args, std::string adresse);
		
		/**
		 * @note Eine Zufallsstring in Kleinbuchstaben erzeugen
		 * 
		 * @return Zufallsstring
		 * @author Mike
		 */
		std::string random_str(uint32_t letters = 10, std::string value = "");
		
		/**
		 * @note temporärer Dateiname erstellen
		 * 
		 * @return /tmp/c++_XXXXXX
		 * @author Mike
		 */
		//std::string tmpfile(std::string filename = "/tmp/c++_XXXXXX");

	/**
	 * @note Zwei Vektoren zu einem Vektor hinzufügen 
	 * 
	 * @return double Vektor
	 * @author Mike
	*/
	std::vector<double> Add_Vector( std::vector <double> vector1 , std::vector <double> vector2);
	std::vector<std::string> Add_Vector( std::vector <std::string> vector1 , std::vector <std::string> vector2);

	
	
	/**
	 * @note Einhängen eines Netzwerklaufwerkes 
	 * 
	 * @author Mike
	*/
	uint32_t cifs(std::string src, std::string dst , mml::string fstype, std::string user , std::string pass);
	

	
	/**
	 * @note Anzahl der Stellen eines doubles bestimmen
	 * 
	 * @return std::size_t
	 * @author Mike
	 */
	std::size_t digits(double number);
	/**
	 * @note Umwandeln von und zu einem String oder Char
	 * 
	 * @author Mike
	 */
	//template<class T> T fromString(const std::string& s);
// 	template<class T> std::string toString(const T& t);
// 	template<class T> T fromChartoNumber(const char& c);
// 	template<class T> T fromChar(const char& c);
	
	/**
	 * @note Zahlenwerte aus einer Datei in einen Vektor schreiben 
	 * 
	 * @return double Vektor 
	 * @author Mike
	*/
	std::vector<double> Get_Values( std::string filepath, int16_t min_value = 0);
	
	/**
	 * @note aus einer Datei eine Zeile auslesen
	 * 
	 * @author Mike
	 */
	void getline(std::ifstream& input, mml::string& String);
	/**
	 * @note Alle Werte im String als Kleinbuchstaben
	 * 
	 * @return String mit Kleinbuchstaben
	 * @author Mike
	 */
	std::string lower(std::string input);
	
	/**
	 * @note Durchschnitt berechnen aus den Werten in einem Vektor oder Array
	 * 
	 * @return Durchschnittswert
	 * @author Mike
	*/
	double Mean_of_Vector( std::vector<double> values, bool ausgabe = false);
	double Mean_of_Array( double array[] , uint16_t length, bool ausgabe = false);
	
	/**
	 * @note Bestimmung von Dateien zur Einbindung eines Laufwerkes in der Funktion cifs 
	 * 
	 * @return Passwort
	 * @author Mike
	*/
	std::string mount_Dir(mml::shell::arg args, std::string mountpath, string mountpoint, string controlpoint, std::string user, std::string pass1, const char* fstype, int count);
	
	/**
	 * @note Aushängen eines Laufwerkes 
	 * 
	 * @param args Arguments passed to the function
	 * @param mountpath String, where the directory is mounted
	 * 
	 * @author Mike
	*/
	bool unmount_dir(std::string mount_dir, std::string controlpoint = "");
	
// 	//Von String zu X: Bsp. double: double d = fromString<double>(string);
// 	template<class T> T fromString(const std::string& s) {
// 		std::istringstream stream (s);
// 		
// 		T t;
// 		stream >> t;
// 		
// 		return t;
// 	}

// 	//Von X zu String: std::string name = toString<int>(integervarialbe);
// 	template<class T> std::string toString(const T& t) {
// 		std::ostringstream stream;
// 		
// 		stream << t;
// 		
// 		return stream.str();
// 	}

	//Von char zu Number X
// 	template<class T> T fromChartoNumber(const char& c) {
// 		char stream (c);
// 		
// 		T t;
// 		t=(T) stream;
// 		
// 		return t-48;	//Ab 48 beginnen die Zahlen
// 	}

	//Von char zu Number X
// 	template<class T> T fromChar(const char& c) {
// 		char stream (c);
// // 		
// 		T t;
// 		t=(T) stream;
		
// 		return t;	//Ab 48 beginnen die Zahlen
// 	}
	}
}


#endif
