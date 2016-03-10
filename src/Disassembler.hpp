#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <cstdint>

#include "Assembly.hpp"

class Disassembler {
public:
    std::uint32_t opcode;
    std::uint32_t rs, rt, rd;
    std::uint32_t shamt, func;
    std::uint32_t immediate;
    std::uint32_t signedExtImm;
    std::uint32_t address;

    void deAsm(const Assembly &assembly);
};

#endif