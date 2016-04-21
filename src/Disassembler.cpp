#include <cstdint>

#include "Disassembler.hpp"

using namespace std;

void Disassembler::deAsm(const Assembly &assembly) {
    uint32_t mask6 = 0b111111;
    uint32_t mask5 = 0b11111;
    uint32_t machineCode = assembly.getMachineCode();

    func = machineCode & mask6;
    shamt = (machineCode >> 6) & mask5;
    rd = (machineCode >> 11) & mask5;
    rt = (machineCode >> 16) & mask5;
    rs = (machineCode >> 21) & mask5;
    opcode = (machineCode >> 26) & mask6;

    immediate = machineCode & 0xffff;
    signedExtImm = (immediate & 0x8000) == 0 ? immediate : immediate | 0xffff0000;

    address = machineCode & 0x3ffffff;
}
