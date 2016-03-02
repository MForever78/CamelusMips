#include <regex>
#include <map>
#include <cstdint>
#include <cstdio>
#include <bitset>
#include <string>

#include "Assembler.hpp"
#include "Assembly.hpp"

using namespace std;

Assembler::Assembler() {

}

Assembler::Assembler(const vector<string> &instOriginal) {
    this->instOriginal = instOriginal;

    const static regex rTypeExp ("(addu|add|subu|sub|and|or|xor|nor|sltu|slt|sllv|srlv|srav|jr|sll|srl|sra)\\b");
    const static regex iTypeExp ("(addiu|addi|andi|ori|xori|lui|lw|sw|beq|bne|sltiu|slti)\\b");
    const static regex jTypeExp ("(jal|j)\\b");

    const static regex operandExp ("\\$(\\w+)");
    const static regex operandsExp ("\\$(\\w+),\\s*\\$(\\w+),\\s*\\$(\\w+)");
    const static regex operandsWithImmExp ("\\$(\\w+),\\s*\\$(\\w+),\\s*(\\d+)");
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
            // R-type

            opcode = 0b000000;
            string funcName = match[0];

            string rsName, rtName, rdName, immName;
            smatch operands, operandsWithImm, operand;

            if (regex_search(inst, operands, operandsExp)) {
                // Regular R-type
                // i.e. Assembly with rs, rt, rd

                rsName = operands[2];
                rtName = operands[3];
                rdName = operands[1];
                rs = getOperand(rsName);
                rt = getOperand(rtName);
                rd = getOperand(rdName);
                shamt = 0b00000;
                func = funcMap.at(funcName);
            } else if (regex_search(inst, operandsWithImm, operandsWithImmExp)) {
                // Shift R-type
                // i.e. Assembly with rt, rd, shamt

                rdName = operandsWithImm[2];
                rtName = operandsWithImm[1];
                immName = operandsWithImm[3];
                rs = 0b00000;
                rd = getOperand(rdName);
                rt = getOperand(rtName);
                shamt = stoul(immName);
                func = funcMap.at(funcName);
            } else if (regex_search(inst, operand, operandExp)) {
                // JR

                rsName = operand[1];
                rs = getOperand(rsName);
                rd = 0b00000;
                rt = 0b00000;
                shamt = 0b00000;
                func = funcMap.at(funcName);
            } else {
                // Syntax Error

                cout << "Syntax error with statement:" << endl;
                cout << inst << endl;
            }
        }

        uint32_t instruction = opcode;
        instruction = (instruction << 5) | rs;
        instruction = (instruction << 5) | rt;
        instruction = (instruction << 5) | rd;
        instruction = (instruction << 5) | shamt;
        instruction = (instruction << 6) | func;

        instAssembled.push_back(Assembly(instruction));
    }
}

vector<Assembly> Assembler::getInstAssembled() {
    return instAssembled;
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

    cout << "Unrecongnized reg:" << operandName << endl;
    return -1;
}

ostream &operator<< (ostream &os, const Assembler &assembler) {
    for (auto inst: assembler.instAssembled) {
        os << inst << endl;
    }
    return os;
}
