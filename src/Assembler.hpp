#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <vector>
#include <cstdint>
#include <iostream>

class Assembler {
public:
    Assembler();
    Assembler(const std::vector<std::string> &instOriginal);

    friend std::ostream &operator<<(std::ostream &os, const Assembler &assembler);

    static const int RS, RT, RD;

private:
    std::vector<std::string> instOriginal;
    std::vector<std::uint32_t> instAssembled;

    std::uint32_t getOperand(std::string &operandName);
};

#endif