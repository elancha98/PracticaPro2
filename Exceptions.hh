//
// Created by ernesto on 23/04/17.
//

#ifndef PRO2_EXCEPTIONS
#define PRO2_EXCEPTIONS

#include <exception>
#include <string.h>

namespace exceptions {

/**
 * thrown when the Argument passed is invalid
 */
    class IllegalArgumentException : public std::exception {
    public:
        IllegalArgumentException(const std::string mot) : exception(), error("Illegal argument exception caused by: " + mot) {};
        virtual ~IllegalArgumentException() throw() {};
        const char* what() const throw() { return error.c_str(); };
    private:
        const std::string error;
    };

/**
 * thrown when you try add a duplicated element to some data structure
 */
    class DuplicatedElementException : public std::exception {
    public:
        DuplicatedElementException(const std::string mot) : exception(), error("Duplicated element exception caused by: " + mot) {};
        virtual ~DuplicatedElementException() throw() {};
        const char* what() const throw() { return error.c_str(); };
    private:
        const std::string error;
    };

/**
 * thrown when you try to access an element that doesn't exist
 */
    class ElementNotFoundException : public std::exception {
    public:
        ElementNotFoundException(const std::string mot) : exception(), error("Element not found exception caused by: " + mot) {};
        virtual ~ElementNotFoundException() throw() {};
        const char* what() const throw() { return error.c_str(); };
    private:
        const std::string error;
    };
}

#endif /* PRO2_EXCEPTIONS */