#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <vector>
#include <cstdint>
#include <iostream>

#include "Assembly.hpp"

class Assembler {
public:
    Assembler();
    Assembler(const std::vector<std::string> &instOriginal);

    // getter
    std::vector<Assembly> getInstAssembled();

    friend std::ostream &operator<<(std::ostream &os, const Assembler &assembler);

    static const int RS, RT, RD;

private:
    std::vector<std::string> instOriginal;
    std::vector<Assembly> instAssembled;

    std::uint32_t getOperand(std::string &operandName);
};

#endif
