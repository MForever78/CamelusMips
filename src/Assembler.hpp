#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include <vector>
#include <cstdint>
#include <iostream>
#include <regex>
#include <map>

#include "Assembly.hpp"

class Assembler {
public:
    Assembler();
    Assembler(const std::vector<std::string> &instOriginal);

    // getter
    std::vector<Assembly> getInstAssembled();

    friend std::ostream &operator<<(std::ostream &os, const Assembler &assembler);

private:
    const static std::regex rTypeExp;
    const static std::regex iTypeExp;
    const static std::regex jTypeExp;

    const static std::regex operandExp;
    const static std::regex operandsExp;
    const static std::regex operandsWithImmExp;
    const static std::map<std::string, int> funcMap;

    std::vector<std::string> instOriginal;
    std::vector<Assembly> instAssembled;

    std::uint32_t getOperand(const std::string &operandName);
    Assembly getRTypeAssembly(const std::string &inst, const std::smatch &match);
};

#endif
