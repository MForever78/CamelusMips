#include <vector>
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>

#include "Processor.hpp"

using namespace std;

void Processor::load(vector<Assembly> &instIn) {
    instructions = instIn;
    running = false;
    pc = 0;
    regs[0] = 0;
}

void Processor::run() {
    running = true;

    while (running) {
        d.deAsm(instructions[pc >> 2]);
        pc += 4;

        switch(d.opcode) {
            case 0b000000:
                // R-type instruction
                switch(d.func) {
                    case 0b100000: regs[d.rd] = regs[d.rs] + regs[d.rt]; break;       // add
                    case 0b100001: regs[d.rd] = regs[d.rs] + regs[d.rt]; break;       // addu
                    case 0b100010: regs[d.rd] = regs[d.rs] - regs[d.rt]; break;       // sub
                    case 0b100011: regs[d.rd] = regs[d.rs] - regs[d.rt]; break;       // subu
                    case 0b100100: regs[d.rd] = regs[d.rs] & regs[d.rt]; break;       // and
                    case 0b100101: regs[d.rd] = regs[d.rs] | regs[d.rt]; break;       // or
                    case 0b100110: regs[d.rd] = regs[d.rs] ^ regs[d.rt]; break;       // xor
                    case 0b100111: regs[d.rd] = ~(regs[d.rs] | regs[d.rt]); break;    // nor
                    case 0b101010: 
                        regs[d.rd] = (int32_t)(regs[d.rs] - regs[d.rt]) < 0 ? 1 : 0; break;    // slt
                    case 0b101011:
                        regs[d.rd] = (int32_t)(regs[d.rs] - regs[d.rt]) < 0 ? 1 : 0; break;    // sltu
                    case 0b000000: regs[d.rd] = regs[d.rt] << regs[d.shamt]; break;   // sll
                    case 0b000010: regs[d.rd] = regs[d.rt] >> regs[d.shamt]; break;   // srl
                    case 0b000011:
                        regs[d.rd] = (uint32_t)((int32_t)regs[d.rs] >> regs[d.rt]);   // sra
                        break; 
                    case 0b000100: regs[d.rd] = regs[d.rt] << regs[d.rs]; break;      // sllv
                    case 0b000110: regs[d.rd] = regs[d.rt] >> regs[d.rs]; break;      // srlv
                    case 0b000111:
                        regs[d.rd] = (uint32_t)((int32_t)regs[d.rt] >> regs[d.rs]);   // srav
                        break;
                    case 0b001000: pc = regs[d.rs]; break;                                // jr
                }
                break;
            // I-type instruction
            case 0b001000: regs[d.rt] = regs[d.rs] + d.signedExtImm; break;               // addi
            case 0b001001: regs[d.rt] = regs[d.rs] + d.signedExtImm; break;               // addiu
            case 0b001100: regs[d.rt] = regs[d.rs] & d.signedExtImm; break;               // andi
            case 0b001101: regs[d.rt] = regs[d.rs] | d.signedExtImm; break;               // ori
            case 0b001110: regs[d.rt] = regs[d.rs] ^ d.signedExtImm; break;               // xori
            case 0b001111: regs[d.rt] = d.signedExtImm << 16; break;                      // lui
            case 0b100011: regs[d.rt] = memory[d.rs + d.signedExtImm]; break;             // lw
            case 0b101011: memory[d.rs + d.signedExtImm] = regs[d.rt]; break;             // sw
            case 0b000100: if (regs[d.rs] == regs[d.rt]) pc += d.signedExtImm; break;     // beq
            case 0b000101: if (regs[d.rt] != regs[d.rs]) pc += d.signedExtImm; break;     // bne
            case 0b001010: regs[d.rt] = regs[d.rs] < d.signedExtImm ? 1 : 0; break;       // slti
            case 0b001011: regs[d.rt] = regs[d.rs] < d.signedExtImm ? 1 : 0; break;       // sltiu
            // J-type instruction
            case 0b000010: pc = d.address; break;                                         // j
            case 0b000011: regs[31] = pc; pc = d.address; break;                          // jal
        }

        cout << "0x" << setfill('0') << setw(8) << hex << pc << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}