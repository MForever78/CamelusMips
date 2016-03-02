#include "Assembler.hpp"
#include <regex>
#include <map>
#include <cstdint>
#include <cstdio>
#include <bitset>

using namespace std;

const int Assembler::RS = 0;
const int Assembler::RT = 1;
const int Assembler::RD = 2;

Assembler::Assembler() {

}

Assembler::Assembler(const vector<string> &instOriginal) {
    this->instOriginal = instOriginal;

    const static regex rTypeExp ("(addu|add|subu|sub|and|or|xor|nor|sltu|slt|sllv|srlv|srav|sll|srl|sra|jr)\\b");
    const static regex iTypeExp ("(addiu|addi|andi|ori|xori|lui|lw|sw|beq|bne|sltiu|slti)\\b");
    const static regex jTypeExp ("(jal|j)\\b");
    const static regex operandExp ("\\$(\\w+),\\s*\\$(\\w+),\\s*\\$(\\w+)");
    const static map<string, int> funcMap = {
        {"addu",    0b100001},
        {"add",     0b100000},
        {"sub",     0b100010},
        {"subu",    0b100011},
        {"and",     0b100100},
        {"or",      0b100101},
        {"xor",     0b100110},
        {"nor",     0b100111},
        {"slt",     0b101010},
        {"sltu",    0b101011},
        {"sll",     0b000000},
        {"srl",     0b000010},
        {"sra",     0b000011},
        {"sllv",    0b000100},
        {"srlv",    0b000110},
        {"srav",    0b000111},
        {"jr",      0b001000}
    };

    for (auto inst: this->instOriginal) {
        uint32_t opcode, rs, rt, rd, shamt, func;
        smatch match;

        if (regex_search(inst, match, rTypeExp)) {
            opcode = 0b000000;
            string funcName = match[0];

            string rsName, rtName, rdName;
            smatch operands;
            if (regex_search(inst, operands, operandExp)) {
                rsName = operands[0];
                rtName = operands[1];
                rdName = operands[2];
                rs = getOperand(rsName);
                rt = getOperand(rtName);
                rd = getOperand(rdName);
                func = funcMap.at(funcName);
                shamt = 0;

                uint32_t instruction = opcode;
                instruction = (instruction << 6) + rs;
                instruction = (instruction << 5) + rt;
                instruction = (instruction << 5) + rd;
                instruction = (instruction << 5) + shamt;
                instruction = (instruction << 5) + func;
                instAssembled.push_back(instruction);
            } else {
                cout << "Syntax error with statement:" << endl;
                cout << inst << endl;
            }
        }
    }
}

uint32_t Assembler::getOperand(string &operandName) {
    const static string regNames[] = {
        "zero", "at",
        "v0", "v1", "a0", "a1", "a2", "a3",
        "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
        "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
        "t8", "t9",
        "k0", "k1",
        "gp", "sp", "fp", "ra"
    };

    for (int i = 0; i < 32; ++i) {
        if (regNames[i] == operandName) return i;
    }

    return -1;
}

ostream &operator<< (ostream &os, const Assembler &assembler) {
    for (auto inst: assembler.instAssembled) {
        os << bitset<32>(inst) << endl;
    }
    return os;
}
