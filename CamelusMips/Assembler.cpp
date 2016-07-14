#include <regex>
#include <map>
#include <bitset>
#include <stack>

#include "Assembler.hpp"

using namespace std;

const regex Assembler::rTypeExp ("(addu|add|subu|sub|and|or|xor|nor|sltu|slt|sllv|srlv|srav|jr|sll|srl|sra)\\b");
const regex Assembler::iTypeExp ("(addiu|addi|andi|ori|xori|lui|lw|sw|beq|bne|sltiu|slti)\\b");
const regex Assembler::jTypeExp ("(jal|j)\\b");

const regex Assembler::branchExp ("(beq|bne)\\b");
const regex Assembler::jumpExp ("(jal|j)\\b");

const regex Assembler::immExp ("([0-9a-fA-FxX+-]+$)");
const regex Assembler::labelExp ("\\s+([a-zA-Z_]\\w*)");
const regex Assembler::operandExp ("\\$(\\w+)");
const regex Assembler::operandsExp ("\\$(\\w+),\\s*\\$(\\w+),\\s*\\$(\\w+)");
const regex Assembler::operandWithImmExp ("\\$(\\w+),\\s*([0-9a-fA-FxX+-]+)$");
const regex Assembler::operandsWithAddrExp ("\\$(\\w+),\\s*([0-9a-fA-FxX+-]+)\\s*\\(\\$(\\w+)\\)");
const regex Assembler::operandsWithImmExp ("\\$(\\w+),\\s*\\$(\\w+),\\s*([0-9a-fA-FxX+-]+)");
const regex Assembler::operandsWithLabelExp ("\\$\\w+,\\s*\\$\\w+,\\s*([a-zA-Z_]\\w*)");

const map<string, int> Assembler::funcMap = {
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
const map<string, int> Assembler::opcodeMap = {
    {"addi",    0b001000},
    {"addiu",   0b001001},
    {"andi",    0b001100},
    {"ori",     0b001101},
    {"xori",    0b001110},
    {"lui",     0b001111},
    {"lw",      0b100011},
    {"sw",      0b101011},
    {"beq",     0b000100},
    {"bne",     0b000101},
    {"slti",    0b001010},
    {"sltiu",   0b001011},
    {"j",       0b000010},
    {"jal",     0b000011}
};

Assembler::Assembler() {

}

Assembler::Assembler(const vector<string> &instOriginal): instTrimmed(instOriginal) {
    symbolTable = generateSymbolTable(instTrimmed);
    substituteLabels(instTrimmed);

    for (auto inst: instTrimmed) {
        smatch match;
        Assembly assembled;

        if (regex_search(inst, match, rTypeExp)) {
            // R-type
            assembled = getRTypeAssembly(inst, match);
        } else if (regex_search(inst, match, iTypeExp)) {
            // I-type
            assembled = getITypeAssembly(inst, match);
        } else if (regex_search(inst, match, jTypeExp)) {
            // J-type
            assembled = getJTypeAssembly(inst, match);
        }

        instAssembled.push_back(assembled);
    }
}

map<string, int> Assembler::generateSymbolTable(vector<string> &inst) {
    map<string, int> symbolTable;
    stack<string> unMarkedLabels;
    int count = 0;
    for (auto it = inst.begin(); it < inst.end();) {
        trimComment(*it);

        size_t found;
        found = it->find_first_of(':');
        if (found != string::npos) {
            // line contains label
            string labelName = it->substr(0, found);

            if (labelName.size() == 0) throw runtime_error("Zero length label");

            unMarkedLabels.push(labelName);

            // trim label
            *it = it->substr(found + 1);
        }

        if (it->size() == 0) {
            // nothing left
            it = inst.erase(it);
        } else {
            // trim possible whitespace
            found = it->find_first_not_of(" \t");
            if (found != string::npos) {
                *it = it->substr(found);
            }

            // statement remains
            while (!unMarkedLabels.empty()) {
                string labelName = unMarkedLabels.top();
                if (symbolTable.find(labelName) != symbolTable.end()) {
                    throw runtime_error("Duplicated label name");
                } else {
                    symbolTable[labelName] = count;
                }
                unMarkedLabels.pop();
            }

            count++;
            it++;
        }
    }

    return symbolTable;
}

void Assembler::trimComment(string &inst) {
    size_t found;

    // get rid of line comment
    found = inst.find_first_of('#');
    if (found != string::npos) {
        inst = inst.substr(0, found);
    }

    // get rid of semicolumn and garbage behind it
    found = inst.find_first_of(';');
    if (found != string::npos) {
        inst = inst.substr(0, found);
    }

    // get rid of the trailing whitespace
    found = inst.find_last_not_of(" \t");
    if (found != string::npos) {
        inst = inst.substr(0, found + 1);
    }

    // get rid of the leading whitespace
    found = inst.find_first_not_of(" \t");
    if (found != string::npos) {
        inst = inst.substr(found);
    }
}

void Assembler::substituteLabels(vector<string> &inst) {
    for (int i = 0; i < inst.size(); ++i) {
        if (regex_search(inst[i], branchExp)) {
            // branch statement
            smatch match;
            if (regex_search(inst[i], match, operandsWithLabelExp)) {
                // branch to a label
                string labelName = match[1];
                auto it = symbolTable.find(labelName);

                if (it == symbolTable.end()) {
                    throw logic_error("Label not found: " + labelName);
                }

                int absoluteAddr = it->second;

                string relativeAddr = to_string((absoluteAddr - i - 1) * 4);
                inst[i] = regex_replace(inst[i], regex(labelName), relativeAddr);
            }
        } else if (regex_search(inst[i], jumpExp)) {
            // jump statement
            smatch match;
            if (regex_search(inst[i], match, labelExp)) {
                // jump to a label
                string labelName = match[1];
                auto it = symbolTable.find(labelName);

                if (it == symbolTable.end()) {
                    throw logic_error("Label not found: " + labelName);
                }

                int absoluteAddr = it->second * 4;

                inst[i] = regex_replace(inst[i], regex(labelName), to_string(absoluteAddr));
            }
        }
    }
}

Assembly Assembler::getRTypeAssembly(const string &inst, const smatch &match) {
    uint32_t opcode, rs, rt, rd, shamt, func;
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
        rdName = operandsWithImm[1];
        rtName = operandsWithImm[2];
        immName = operandsWithImm[3];
        rs = 0b00000;
        rd = getOperand(rdName);
        rt = getOperand(rtName);
        shamt = static_cast<uint32_t>(stoul(immName));
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
        throw logic_error("Syntax error with R-type statement: " + inst);
    }

    uint32_t instruction = opcode;
    instruction = (instruction << 5) | rs;
    instruction = (instruction << 5) | rt;
    instruction = (instruction << 5) | rd;
    instruction = (instruction << 5) | shamt;
    instruction = (instruction << 6) | func;

    return Assembly(instruction);
}

Assembly Assembler::getITypeAssembly(const string &inst, const smatch &match) {
    uint32_t opcode, rs, rt;
    uint32_t imm;
    uint32_t mask = 0x0000ffff;
    string funcName = match[0];

    string rsName, rtName, immName;
    smatch operandsWithImm, operandWithImm, operandsWithAddr;

    if (regex_search(inst, operandsWithImm, operandsWithImmExp)) {
        // Regular I-type
        // i.e. Assembly with rs, rt, immediate
        opcode = opcodeMap.at(funcName);
        rsName = operandsWithImm[2];
        rtName = operandsWithImm[1];
        immName = operandsWithImm[3];

        rs = getOperand(rsName);
        rt = getOperand(rtName);
        imm = static_cast<uint32_t>(stoi(immName, nullptr, 0));
    } else if (regex_search(inst, operandWithImm, operandWithImmExp)) {
        // lui
        opcode = opcodeMap.at(funcName);
        rtName = operandWithImm[1];
        immName = operandWithImm[2];

        rs = 0b00000;
        rt = getOperand(rtName);
        imm = static_cast<uint32_t>(stoi(immName, nullptr, 0));
    } else if (regex_search(inst, operandsWithAddr, operandsWithAddrExp)) {
        // Save load I-type
        opcode = opcodeMap.at(funcName);
        rsName = operandsWithAddr[3];
        rtName = operandsWithAddr[1];
        immName = operandsWithAddr[2];

        rs = getOperand(rsName);
        rt = getOperand(rtName);
        imm = static_cast<uint32_t>(stoi(immName, nullptr, 0));
    } else {
        // Syntax Error
        throw logic_error("Syntax error with I-type statement: " + inst);
    }

    uint32_t instruction = opcode;
    instruction = (instruction << 5) | rs;
    instruction = (instruction << 5) | rt;
    instruction = (instruction << 16) | (imm & mask);

    return Assembly(instruction);
}

Assembly Assembler::getJTypeAssembly(const string &inst, const smatch &match) {
    uint32_t opcode, imm;
    uint32_t mask = 0x03ffffff;
    string funcName = match[0];

    string immName;
    smatch immMatch;
    if (regex_search(inst, immMatch, immExp)) {
        opcode = opcodeMap.at(funcName);
        immName = immMatch[0];
        imm = static_cast<uint32_t>(stoi(immName, nullptr, 0));
    } else {
        // Syntax Error
        throw logic_error("Syntax error with J-type statement: " + inst);
    }

    uint32_t instruction = opcode;
    instruction = (instruction << 26) | (imm & mask);

    return Assembly(instruction);
}

vector<Assembly> Assembler::getInstAssembled() const {
    return instAssembled;
}

map<string, int> Assembler::getSymbolTable() const {
    return symbolTable;
}

vector<string> Assembler::getInstTrimmed() const {
    return instTrimmed;
}

uint32_t Assembler::getOperand(const string &operandName) {
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
        if (regNames[i] == operandName) return static_cast<uint32_t>(i);
    }

    // Syntax Error
    throw logic_error("Unrecongnized reg: " + operandName);
}

ostream &operator<< (ostream &os, const Assembler &assembler) {
    for (auto inst: assembler.instAssembled) {
        os << inst << endl;
    }
    return os;
}

void Assembler::printSymbolTable() {
    for (auto symbol: symbolTable) {
        cout << symbol.first << " " << symbol.second << endl;
    }
}
