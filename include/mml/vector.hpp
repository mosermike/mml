/**
 * @author Mike Moser
 * 
 * @file vector.hpp 
 * @brief Class vector
 * 
*/

#ifndef MML_INCLUDE_MML_VECTOR_HPP
#define MML_INCLUDE_MML_VECTOR_HPP

#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <cctype> // std::isdigit
#include <algorithm> // std::sort
#include <type_traits> // std::is_same

#include "mml/standards.hpp"
#include "mml/log.hpp"

// todo count how many entries the same

namespace mml{
	template <class T> 
	class vector {
	protected:
		std::vector<T> vec;    // elements 

	public:
		/**
		* @brief Constructors
		*/
        vector() : vec() {}
        vector(const vector &temp) : vec(temp.vec) {}
        vector(std::vector<T>& temp) : vec(temp) {}
        vector(mml::vector<T>& temp) : vec(temp.vec) {}
        vector(double temp) : vec(static_cast<size_t>(temp)) {}
        vector(int cols, T temp) : vec(cols, temp) {}
        vector(int cols, std::vector<T> temp) : vec(cols, temp) {}

		/**
		 * @brief Construct with a list
		 * @param initList Initializer_list
		 * @return this instance
		*/
		vector(std::initializer_list<T> initList) : vec(initList) {}	

		/**
		 * @brief Assign value with equal sign
		 * @param temp Vector with values
		 * @return this instance
		*/
		vector operator=(const std::vector<T>& temp) noexcept {vec = temp; return *this;}
		vector operator=(mml::vector<T> temp) noexcept {vec = temp.vec; return *this;}
		
		/**
		 * @brief Returns a value at a specific index
		 * @param index Index to be returned
		 * @return value at this index
		 * @throw out_of_range : if index not in range
		*/
		T &operator[](int index) {
			if (index < 0)
				index = vec.size() + index;
			if(abs(index) > vec.size())	
				throw std::out_of_range("[vector[]] Out of range for index " + std::to_string(index));
			return vec[index];
		}
		const T &operator[](int index) const {
			if (index < 0)
				index = vec.size() + index;
			if(abs(index) > vec.size())	
				throw std::out_of_range("[vector[]] Out of range for index " + std::to_string(index));
			return vec[index];
		}
		
		/**
		* @brief iterator to the beginning of the vector
		* @return iterator
		*/
		typename std::vector<T>::iterator begin() const noexcept {return vec.begin();}

		/**
		* @brief Checks whether the vector is empty
		* @return iteratur
		*/
		bool empty() const noexcept {return this->vec.empty();}

		/**
		* @brief iterator to the end of the vector
		* @return iterator
		*/
		typename std::vector<T>::iterator end() noexcept {return vec.end();}
		
		/**
		 * @brief Erase an element from the vector
		 * @param position Position to be erase
		 * @return None
		 * @throw out_of_range if position >= vector.size()
		*/
		void erase(size_t position) {
			if (position >= vec.size())
				throw std::out_of_range("[vector::erase] Position " + std::to_string(position) + " out of range");
			vec.erase(vec.begin() + position);
		}

		/**
		 * @brief Erase a range from the vector
		 * @param start Start position
		 * @param end End position
		 * @return None
		 * @throw out_of_range : if start > end || end > vector.size()
		*/
		void erase(size_t start, size_t end) {
			if (start > end || end > vec.size()) {
				throw std::out_of_range("[vector::erase] Invalid range [" + std::to_string(start) + "," + std::to_string(end) + "]");
			}
			vec.erase(vec.begin() + start, vec.begin() + end);
		}

		/**
		 * @brief Insert a value at a specific position
		 * @param position The position where the value is put
		 * @param val Value
		 * @return Iterator
		*/
		typename std::vector<T>::iterator insert (const typename std::vector<T>::iterator position, const T& val) noexcept {return vec.insert(position,val);}

		/**
		 * @brief Removes the last entry
		 * @return None
		*/
		void pop_back() noexcept {
			vec.pop_back();
		}

		/**
		 * @brief Adds an element at the end
		 * @param value to e added
		*/
		void push_back(T value) noexcept {
			vec.push_back(value);
		}

		/**
		 * @brief Size of the vector
		 * @return Size of the vector
		*/
		std::size_t size() const noexcept {return vec.size();}
			
		/**
		 * @brief Print the vector
		 * @param out Output where it is written
		 * @param Vec Vector which is written
		 * @return output stream
		*/
		friend std::ostream& operator<< (std::ostream &out, const vector<T> &Vec) noexcept {		// Ausgabe über std::cout
			for(T i : Vec.vec)
				out << i << " ";
			
			return out;
		}

		/**
		 * @brief Writes a value into the vector
		 * @param in where it should be written in
		 * @param v what should be written in
		 * @return output stream
		 */
		friend std::istream& operator>> (std::istream &in, const vector<T>& v) noexcept {
			T temp;
			if (in >> temp) {
            	v.vec.push_back(temp);
        	}
			return in;
		}
		// Friend function to overload the operator>>
    
		/**
		 * Count how many entries are equal to a value
		 * @param value Value to be checked
		 * @return std::size_t 
		 */
		std::size_t count(T value) const noexcept {
			std::size_t  counts = 0;
			for(T i : vec) {
				if(i == value)
					counts++;
			}
			return counts;
		}

		/**
		 * @brief print elements in the vector
		 * @param newline Print with line breaks
		 */
		void cout(bool newline = false) const noexcept {
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
		 * @brief Empties the vector
		 * @return std::vector<T>
		 */
		std::vector<T> del() noexcept {
			while(!empty())
					pop_back();
			return this->vec;
		}

	private:
		/**
		 * @brief Check if a string exists in the vector
		 * @param name String to be checked
		 * @return bool
		 */
		bool _exist(const T& name) const noexcept {return std::find(this->vec.begin(), this->vec.end(), name) != this->vec.end();}

	public:
		/**
		 * @brief Check if one *or* another string exists
		 * @param value Parameters to be checked if they exist
		 * @return bool
		 */
		template <typename... values>
		bool exist(const values&... value) const noexcept {
			return (... || _exist(value));
		}
		
		/**
		 * @brief Return a position of an element
		 * @param value Value to be looked for
		 * @param start Defines at what position to start to be looked for
		* @return std::size_t
		*/
		std::size_t find(const T value, size_t start = 0) const noexcept {
			for(size_t i = start; i < vec.size(); i++) {
				if (mml::to_string(vec[i]).find(mml::to_string(value).str()) < std::string::npos)
					return i;
			}
			return std::string::npos;
		}

		/**
		 * @brief Write values into a logfile
		 * @param logpath Path of the logfile
		 * @param newline Print a newline
		 * @param first Print this in the start of the logfile before any value
		 * @param last Print this at the end of the logfile after all vlaues are written
		 * @param separator Separation sign after each value if newline = false
		 */
		void log(mml::string logpath, bool newline = false, mml::string first = "", mml::string last = "", mml::string separator = ",") const noexcept {
			
			// Log file
			mml::log log(logpath);
			
			// Write this first in the logfile
			log.cout<mml::string>(first, false);

			// Write all the values into the logfile
			for(uint32_t i = 0; i < vec.size(); i++) {
				log.cout<mml::string>(vec[i],newline);
				// Write separator if not newline
				if(!newline && i < vec.size()-1)
					log.cout<mml::string>(separator,false);
			}

			// Print sth at the end plus a new line
			log.cout<mml::string>(last, true);
		}

		/**
		* @brief Replace specific elements with another element
		* @param Old Value to be replaced
		* @param New New value
		* @return Vector with the replaced values
		*/
		std::vector<T> replace(T Old, T New) noexcept {
			std::vector<T> temp = vec;
		
			for(size_t i = 0; i < temp.size(); i++) {
				if(temp[i] == Old)
					temp[i] = New;
			}
			return temp;
		}
			
			
		/**
		 * @brief Scalarmultiplication
		 * @param value Value to be multiplied
		 * @return Vektor
		 * @throw logic_error : if vector empty or type is not a number
		*/
		vector<T> operator*(const T &value) const {
			if(vec.empty())
				throw std::logic_error("[*] Vector empty");
			
			if(!std::isdigit(vec[0]))
				throw std::logic_error("[*] Scalar multiplication for this type not defined!");
			
			std::vector<T> temp = vec;
			for(uint32_t i = 0; i < temp.size(); i++)
				temp[i] *= value;
			return temp;
		}

		/**
		 * @brief Scalarmultiplication
		 * @param value Value to be multiplied
		 * @return Instance of the class
		 * @throw logic_error : if vector empty or type is not a number
		*/
		vector<T> operator*=(const T &value) {
			if(vec.empty())
				throw std::logic_error("[*] Vector empty");
			
			if(!std::isdigit(vec[0]))
				throw std::logic_error("[*] Scalar multiplication for this type not defined!");
			
			for(uint32_t i = 0; i < vec.size(); i++)
				vec[i] *= value;
			return *this;
		}

		/**
		 * @brief Add a value to each element
		 * @param value Value to be added
		 * @return Vector with the added value
		 * @throw logic_error : if vector is empty
		 */
		vector<T> operator+(const T &value) const {
			if(vec.empty())
				throw std::logic_error("[+] Vector empty");
			
			std::vector<T> temp = vec;
			for(uint32_t i = 0; i < temp.size(); i++)
				temp[i] += value;
			return temp;
		}

		/**
		 * @brief Add a value to each element
		 * @param value Value to be added
		 * @return Instance of the class
		 * @throw logic_error : if vector is empty
		 */
		vector<T> operator+=(const T &value) {
			if(vec.empty())
				throw std::logic_error("[+] Vector empty");
			
			for(uint32_t i = 0; i < vec.size(); i++)
				vec[i] += value;
			return *this;
		}

		/**
		 * @brief Replace the vector with a new vector
		 * @param Vec Vector
		 */
		void set(std::vector<T> Vec) noexcept {
			vec = Vec;
		}

		/**
		 * @brief Sort the vector
		 * @return Return the sorted vector
		 */
		std::vector<T> sort() {std::vector<T> temp = vec; return std::sort(temp.begin(), temp.end());}
		
		/**
		 * @brief Determine the sum of the vector
		 * @return Sum of the vector
		 * @throw logic_error : if vector is empty or if template is boolean
		 */
		T sum() const {
			if(vec.empty())
				throw std::logic_error("[sum] Vector empty");
			
			 if constexpr (std::is_same<T, bool>::value)
        		throw std::logic_error("[sum] Summation for the type bool is not defined");

			T temp; // Temp variable which is set to 0 

			// Set temp as 0 if T is a number otherwise set it to a string ""
			if constexpr (std::is_arithmetic_v<T>) {
				std::string t = "0";
				std::istringstream iss(t);
				iss >> temp;
			}
			else {
				temp = "";
			}
			
			

			for(std::size_t i = 0; i < vec.size(); i++) {
				temp += vec[i];
			}
			return temp;
		}

		/**
		 * @brief Add a vector to this vector
		 * @param temp Vector to be added elementwise
		 * @return resulting vector
		 * @throw logic_error : if vector sizes are not the same
		*/
		mml::vector<T> operator+(vector<T> temp) const {
			// Check if possible
			if(vec.size() != temp.size())
				throw std::logic_error("[+] Vectors have different sizes (" + std::to_string(vec.size()) + " vs. " + std::to_string(temp.size()) + ")!");

			for(size_t i = 0; i < vec.size(); i++)
				temp[i] = vec[i] + temp[i];

			return temp;
		}

		/**
		 * @brief Add a vector to this vector
		 * @param temp Vector to be added elementwise
		 * @return Instance of this class
		 * @throw logic_error : if vector sizes are not the same
		*/
		mml::vector<T> operator+=(mml::vector<T> temp) {
			// Check if possible
			if(vec.size() != temp.size()) {
				throw std::logic_error("[+] Vectors have different sizes (" + std::to_string(vec.size()) + " vs. " + std::to_string(temp.size()) + ")!");
			}

			for(uint32_t i = 0; i < vec.size(); i++) {
				vec[i] += temp[i];
			}
			return *this;
		}
			
		/**
		 * @brief Vector^()
		 * @param exponent Exponent
		 * @return vector
		 * @throw logic_error : if type is not numeric
		 */
		mml::vector<T> operator^(const T exponent) const {
			if(!std::is_arithmetic<T>::value)
				throw std::logic_error("[^] Type of the vector is not arithmetic");
			
			mml::vector temp = vec;
			for(size_t i = 0; i < vec.size(); i++) {
				temp[i] = std::pow(vec[i],exponent);
			}

			return temp;
		}

		/**
		 * @brief Vector^()
		 * @param exponent Exponent
		 * @return Instance of the class
		 * @throw logic_error : if type is not numeric
		 */
		mml::vector<T> operator^=(const T exponent) {
			if(!std::is_arithmetic<T>::value)
				throw std::logic_error("[^] Type of the vector is not arithmetic");
			
			for(size_t i = 0; i < vec.size(); i++) {
				vec[i] = std::pow(vec[i],exponent);
			}

			return *this;
		}
			

			
		/**
		 * @brief Return the std::vector
		 * @return Vector of the standard library
		 */
		typename std::vector<T> tovec() const noexcept {return vec;}

	};

}

#endif
