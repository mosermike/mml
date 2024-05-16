/**
 * @author Mike Moser
 * 
 * @file vector.hpp 
 * @note Enthält verschiedene Standardfunktionen
 * 
*/

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <iostream>
#include <vector>
#include <string>
#include "standards.hpp"


// TODO
#include <iostream>
#include <standards.hpp>
#include <vector>
#include <string>
#include <algorithm> // std::sort
//#include "shell.hpp"
#include "log.hpp"

// todo count how many entries the same

namespace mml{
	//class string;
	// To print out things from mml::shell
	template <class T> 
	class vector : private std::vector<T> {
	protected:
		std::vector<T> vec;    // elements 

	public:
		/**
			* @note constructor
			* 
			* @author Mike
			*/
		vector(const vector &temp);
		vector(std::vector<T>& temp) : vec(){vec = temp;}
		vector(mml::vector<T>& temp) : vec(){vec = temp.vec;}
		vector(double temp) : vec(){vec = std::vector<T>(temp);}
		vector(int cols, T temp) : vec(){vec = std::vector<T>(cols,temp);}
		vector(int cols, std::vector<T> temp) : vec(){vec = std::vector<std::vector<T>>(cols,temp);}
		// TODO vector(int cols, mml::vector<T> const& temp1) : vec(){vec = std::vector<std::vector<T>>(cols,temp1.to_vec());}
		// Ohne direkte Initialisierung:
		vector() : vec() {}
		vector operator=(const std::vector<T>& temp) {vec = temp; return *this;}	//for(uint32_t i = 0; i < temp.size(); temp++) vec.push_back(temp[i]); return *this;}
		vector operator=(mml::vector<T> temp) {vec = temp.vec; return *this;}
		

		
		/**
			* @note destructor
			* 
			* @author Mike
			*/
		//~vector() {}
		
			/**
			* @note Standardfunktionen aus std::vector
			* 
			* @author Mike
			*/
			typename std::vector<T>::iterator begin() noexcept{return vec.begin();}
			bool empty() noexcept {
				return this->vec.empty();
			}
			typename std::vector<T>::iterator end() noexcept{return vec.end();}
			typename std::vector<T>::iterator erase(typename std::vector<T>::iterator start,typename std::vector<T>::iterator amount = 0) {vec.erase(start,start+amount);}
			typename std::vector<T>::iterator insert (const typename std::vector<T>::iterator position, const T& val) {return vec.insert(position,val);}
			T &operator[](int index){
				if (index < 0)
					index = vec.size() + index;
				
				return vec[index];
			}
			void pop_back(){
				vec.pop_back();
			}

			void push_back(T value){
				vec.push_back(value);
			}
			std::size_t size() const noexcept{return vec.size();}
			
// 			T& operator= (std::vector<T> temp){vec = temp;}
			
			
			/**
			* @note Vektorinhalt ausgeben
			* 
			* @author Mike
			*/
			friend std::ostream& operator<< (std::ostream &out, const vector<T> &Vec){		// Ausgabe über std::cout
				for(uint32_t i = 0; i < Vec.size();i++) {
					out << Vec.vec[i] << " ";
				}
				return out;
			}
			/**
			* @note Wert in Vektor reinschreiben
			* 
			* @author Mike
			*/
			friend std::istream& operator>> (std::istream &in, vector<T> &Vec){
				T temp;
				in >> temp;
				Vec.push_back(temp);
				return in;
			}
			/**
			* @note Vektorinhalt ausgeben
			* 
			* @author Mike
			*/
			void cout(bool newline = false) noexcept{
				if (vec.empty()) {
					std::cout << "[cout] Vector is empty" << std::endl;
					return;
				}
				std::cout << vec[0];
				if(newline) {
					std::cout << std::endl;
					for(uint32_t i = 1; i < vec.size(); i++)
						std::cout << vec[i] << std::endl;
				}
				else {
					for(uint32_t i = 1; i < vec.size(); i++)  {
						std::cout << ", ";
						std::cout << vec[i];
					}

					std::cout << std::endl;
				}
			}

			/**
			 * @note Vektor leeren
			 * 
			 * @author Mike
			 */
			std::vector<T>  del(){
				while(!empty())
						pop_back();	// Da eine Initialisierung stattfindet am Anfang
				return this->vec;
			}
			/**
			* @note exist
			* 
			* @return bool
			* @author Mike
			*/
			bool exist(T const& value) {
				// 	bool exist = false;

				// 	if(typeid(T) == typeid(std::string)) {
				//
				// 		for(uint32_t i = 0; i < vec.size(); i++) {
				// 			//exist = true;//vec[i].find(value) < std::string::npos ? true : false;
				// 			if(exist)
				// 				return true;
				// 		}
				// 	}
				// 	else if(typeid(T) == typeid(mml::string)) {
				// 		for(uint32_t i = 0; i < vec.size(); i++) {
				// 			exist = true; //vec[i].find(value) < std::string::npos ? true : false;
				// 			if(exist)
				// 				return true;
				// 		}
				// 	}
				// 	else {
						for(uint32_t i = 0; i < vec.size(); i++) {
							if(vec[i] == value)
								return true;
						}
				// 	}


					return false;
				}
			/**
			 * @note String in T umwandeln
			 *
			 * @return T
			 * @author Mike
			 */
			T toT(mml::string s) {
						std::istringstream stream (s.str());

						if(typeid(T) == typeid(mml::string) || typeid(T) == typeid(std::string)) {
							if(s.exist(" "))
								std::cout << "[toT] everything after special character is ignored!" << std::endl;
						}
						T t;
						stream >> t;
						return t;
			}
			/**
			 * @note get data from file
			 * 
			 * @author Mike
			 */
			 void get_data( std::string filepath, int skip = -1) {	//Nach dem Zeichen border wird ausgegeben
				// TODO doesnt work because of toT
				std::string 		value1 	= "";			//String aus einer Linie
				//Öffne die Datei:

				std::fstream input(filepath);


				//Überprüfung, ob die Datei geöffnet wurde
				if ( !input ){
					std::cerr << "file not found" << std::endl;

					//return ;

				}

				//Inhalt der Datei Zahl für Zahl einlesen
				int i = 0;
				while (! input.eof()){
					std::getline(input, value1);

					std::cout << toT(value1) << std::endl;

					if (i > skip )	//Korrektur des Titels, das als Zahl 0 verwertet wird
						this->vec.push_back(toT(value1));
					i++;
				}

				return;
			}
			/**
			* @note Position zurückgeben
			* 
			* @return std::size_t
			* @author Mike
			*/
			std::size_t find(const T value) {
				if(typeid(T) != typeid(std::string)  || typeid(T) != typeid(mml::string)) {
					std::cout << "[find] Umwandlung des Typids notwendig." << std::endl;
					for(uint32_t i = 0; i < vec.size(); i++) {
						if(vec[i] == value)
							return i;
					}
				}
				for(uint32_t i = 0; i < vec.size(); i++) {
					return mml::to_string(vec[i]).find(mml::to_string(value).str()) < std::string::npos ? i : -1;
				}
				return std::string::npos;
			}

			
			/**
			 * @note Werte in eine Logdatei schreiben
			 * 
			 * @author Mike
			 */
			void log(mml::string logpath, bool newline = false, mml::string first = "", mml::string last = "") {
				mml::log log(logpath);

				// Etwas vorangehendes in die Logdatei
				log.cout(first, false);

				// Werte in die Logdatei
				for(uint32_t i = 0; i < vec.size(); i++) {
					log.cout(vec[i],newline);
					// Newline oder , als Trennungszeichen
					if(!newline && i < vec.size()-1)
						log.cout(", ");
				}
				// Etwas nachgehendes in die Logdatei
				log.cout(last, true);

			}
			/**
			* @note Ersetzen eines Wertes in einem Vektor
			* 
			* @return Vektor mit den ersetzten Werten
			* @author Mike
			*/
			std::vector<T> replace(T old, T new1) {
				if(typeid(T) == typeid(std::string)  || typeid(T) == typeid(mml::string)) {
					for(uint32_t i = 0; i < vec.size(); i++) {
						mml::string temp = mml::to_string(vec[i]);
						if(temp.exist(mml::to_string(old).str())) {
							temp = temp.replace(mml::to_string(old).str(),mml::to_string(new1).str());
							vec[i] = toT(temp);
						}
					}
				}
				else {
					for(uint32_t i = 0; i < vec.size(); i++) {
						if(vec[i] == old)
							vec[i] = new1;
					}
				}
				return vec;
			}
			
			
			/**
			* @note Skalarmultiplikation
			* 
			* @return Vektor
			* @author Mike
			*/
			vector<T> operator*(const T &value) {
				for(uint32_t i = 0; i < vec.size(); i++)
					vec[i] *= value;
				return vec;
			}
			/**
			 * @note Skalare Addition
			 * 
			 * @author Mike
			 */
// 			vector<T> s_add(const T &value);
			/**
			 * @note vec setzen
			 * 
			 * @author Mike
			 */
			void set(std::vector<T> temp) {
				vec = temp;
			}
			/**
			 * @note vec sortieren
			 * 
			 * @author Mike
			 */
// 			std::vector<T> sort(bool save = true);
			/**
			* @note Summe des Vektors bestimmen
			* 
			* @return T
			* @author Mike
			*/
			T sum() {
				// 	if(typeid(T) == typeid(std::string) || typeid(T) == typeid(mml::string))
				// 		mml::shell::note("[operator^] Achtung Umwandlung u.U. notwendig.");
					T temp = toT("0");

					for(uint32_t i = 0; i < vec.size(); i++) {
						temp += vec[i];
					}

					return temp;
				}
			/**
			* @note Zwei Vektoren zeilenweise addieren
			* 
			* @return Vektor
			* @author Mike
			*/
			std::vector<T> operator+(mml::vector<T> temp) {

				// Summe nicht möglich
				if(vec.size() != temp.size()) {
					std::cout << "\e[" << "31" << "m" << "[SUM] Größe unterschiedlich." << "\e[" << "0" << "m" << std::endl;
					exit(EXIT_FAILURE);
				}

				for(uint32_t i = 0; i < vec.size(); i++) {
					vec[i] += temp[i];
				}
				return vec;
			}

			std::vector<T> operator+=(mml::vector<T> temp) {

				// Summe nicht möglich
				if(vec.size() != temp.size()) {
					std::cout << "\e[" << "31" << "m" << "[SUM] Größe unterschiedlich." << "\e[" << "0" << "m" << std::endl;
				}

				for(uint32_t i = 0; i < vec.size(); i++) {
					vec[i] += temp[i];
				}
				return vec;
			}
			
			/**
			* @note Vektor hoch exponent
			* 
			* @return Vektor
			* @author Mike
			*/
			std::vector<T> operator^(const double exponent) {

				if(typeid(T) == typeid(std::string) || typeid(T) == typeid(mml::string)) {
					std::cout << "\e[" << "31" << "m" << "[operator^] Inkompatibler Typid" << "\e[" << "0" << "m" << std::endl;
					exit(EXIT_FAILURE);
				}
				if(typeid(T) != typeid(double)) {
					std::cout << "\e[" << "31" << "m" << "[operator^] Achtung Umwandlung u.U. notwendig." << "\e[" << "0" << "m" << std::endl;
				}
				for(uint32_t i = 0; i < vec.size(); i++) {
					vec[i] = std::pow(mml::atof(vec[i]),exponent);
				}
				return vec;
			}
			

			
			/**
			* @note Vektor zurückgeben
			* 
			* @return Vektor
			* @author Mike
			*/
			typename std::vector<T> tovec() {return vec;}



		// template <class T> std::vector<T> mml::vector<T>::sort(bool save) {
		//
		// 	// NOTE ineffizient
		// 	std::vector<std::string> temp;
		// 	std::vector<T> temp1;
		// 	for(uint32_t i = 0; i < vec.size(); i++)
		// 		temp[i] = mml::to_string(vec[i]).str();
		//
		// 	std::sort(temp.begin(),temp.end());
		//
		// 	for(uint32_t i = 0; i < vec.size(); i++)
		// 			temp1[i] = toT(temp[i]);
		// 	if(save)
		// 		vec = temp1;
		// 	return temp1;
		// }

		// template <class T> mml::vector<T> mml::vector<T>::s_add(const T &value) {
		// 	for(uint32_t i = 0; i < vec.size(); i++) {
		// 		vec[i] = vec[i] + value;
		// 	}
		// 	return vec;
		// }
	};
}

// namespace vec{
// 	/**
// 	 * @note std vector std string zu mml vector mml string
// 	 * 
// 	 * @return mml::vector<mml::string>
// 	 * @author Mike
// 	 */
// // 	mml::vector<mml::string> tovec(std::vector<std::string> temp) {
// // 		mml::vector<mml::string> temp1;
// // 		for(uint32_t i = 0; i < temp.size(); i++)
// // 			temp1.push_back(temp[i]);
// // 		return temp1;
// // 	}
// 		
// }


/**
 * @note mml::string
 */
//template <> mml::vector<mml::string>::vector();
template bool mml::vector<mml::string>::empty() noexcept;
template void mml::vector<mml::string>::cout(bool newline = false) noexcept;
template std::vector<mml::string>  mml::vector<mml::string>::del();
template bool mml::vector<mml::string>::exist(const mml::string& value);
template void mml::vector<mml::string>::get_data( std::string filepath, int skip);
template std::size_t mml::vector<mml::string>::find(const mml::string value);
template void mml::vector<mml::string>::log(mml::string logpath, bool newline, mml::string first, mml::string last);
template void mml::vector<mml::string>::pop_back();
template void mml::vector<mml::string>::push_back(mml::string value);
template std::vector<mml::string> mml::vector<mml::string>::replace(mml::string old, mml::string new1);
// template mml::vector<mml::string> mml::vector<mml::string>::s_add(const mml::string &value);
// template std::vector<mml::string> mml::vector<mml::string>::sort(bool save);
template std::size_t mml::vector<mml::string>::size() const noexcept;
template mml::string mml::vector<mml::string>::sum();
template mml::string mml::vector<mml::string>::toT(mml::string s);
template std::vector<mml::string> mml::vector<mml::string>::operator+(vector<mml::string> temp);
template std::vector<mml::string> mml::vector<mml::string>::operator+=(vector<mml::string> temp);
template std::vector<mml::string> mml::vector<mml::string>::operator^(const double exponent);

#endif
