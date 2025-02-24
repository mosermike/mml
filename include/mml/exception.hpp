#ifndef MML_INCLUDE_MML_EXCEPTION_HPP
#define MML_INCLUDE_MML_EXCEPTION_HPP
#include <iostream>
#include <exception>
#include <string>

#include "mml/string.hpp"

namespace mml{

/**
 * @brief Basis Error class
 * 
 */
class BaseError : public std::exception {
protected:
    std::string message; // Message
public:
    explicit BaseError(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};


class FileNotFound : public BaseError {
	public:
    explicit FileNotFound(const mml::string& msg = "FileNotFound: File not found") : BaseError(msg) {}
};

class MissingArgument : public BaseError {
	public:
    explicit MissingArgument(const mml::string& msg = "MissingArgument: Argument missing") : BaseError(msg) {}
};

}

#endif