//
// Created by MForever78 on 16/7/13.
//

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <stdexcept>

class InvalidInstructionException: public std::exception {
    virtual const char *what() const throw() {
        return "Invalid instruction caught";
    }
};

#endif //EXCEPTION_HPP
