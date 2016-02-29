#include "Assembler.hpp"
#include <regex>
#include <cstdint>
#include <cstdio>

using namespace std;

const int Assembler::RS = 0;
const int Assembler::RT = 1;
const int Assembler::RD = 2;

Assembler::Assembler(const vector<string> &instOriginal) {
    this->instOriginal = instOriginal;

    const static regex rTypeExp ("(addu|add|subu|sub|and|or|xor|nor|sltu|slt|sllv|srlv|srav|sll|srl|sra|jr)\b");
    const static regex iTypeExp ("(addiu|addi|andi|ori|xori|lui|lw|sw|beq|bne|sltiu|slti)\b");
    const static regex jTypeExp ("(jal|j)\b");
    const static regex operandExp ("\$(\w+),\s*\$(\w+),\s*\$(\w+)");

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
            } else {
                cout << "Syntax error with statement:" << endl;
                cout << inst << endl;
            }
        }
    }
}

int Assembler::getOperand(string &operandName) {
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