#include <vector>
#include <iostream>
#include <iomanip>
#include <thread>

#include "Processor.hpp"
#include "Exception.hpp"

using namespace std;

const uint32_t Processor::interruptHandlerAddress = 0x00010000;

void Processor::handleInterruption() {
    if (cp0->interruptable() && cp0->interrupting()) {
        // save current PC to EPC
        cp0->regs[14] = pc;
        // set PC to interrupt handler address
        pc = interruptHandlerAddress;
        // disable interrupt from the same device
        cp0->disableInterruptForCode(cp0->interruptingBusCode());
    }
}

void Processor::tick() throw() {
    d.deAsm(bus->at(pc >> 2)->get());
    pc += 4;
    handleInterruption();

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
                case 0b000000: regs[d.rd] = regs[d.rt] << d.shamt; break;   // sll
                case 0b000010: regs[d.rd] = regs[d.rt] >> d.shamt; break;   // srl
                case 0b000011:
                    regs[d.rd] = (uint32_t)((int32_t)regs[d.rs] >> regs[d.rt]);   // sra
                    break; 
                case 0b000100: regs[d.rd] = regs[d.rt] << regs[d.rs]; break;      // sllv
                case 0b000110: regs[d.rd] = regs[d.rt] >> regs[d.rs]; break;      // srlv
                case 0b000111:
                    regs[d.rd] = (uint32_t)((int32_t)regs[d.rt] >> regs[d.rs]);   // srav
                    break;
                case 0b001000: pc = regs[d.rs]; break;                            // jr
                default: throw InvalidInstructionException();
            }
            break;
        // I-type instruction
        case 0b001000: regs[d.rt] = regs[d.rs] + d.signedExtImm; break;               // addi
        case 0b001001: regs[d.rt] = regs[d.rs] + d.signedExtImm; break;               // addiu
        case 0b001100: regs[d.rt] = regs[d.rs] & d.signedExtImm; break;               // andi
        case 0b001101: regs[d.rt] = regs[d.rs] | d.signedExtImm; break;               // ori
        case 0b001110: regs[d.rt] = regs[d.rs] ^ d.signedExtImm; break;               // xori
        case 0b001111: regs[d.rt] = d.signedExtImm << 16; break;                      // lui
        case 0b100011: regs[d.rt] = bus->at(regs[d.rs] + d.signedExtImm)->get(); break;     // lw
        case 0b101011: bus->at(regs[d.rs] + d.signedExtImm)->set(regs[d.rt]); break;        // sw
        case 0b000100: if (regs[d.rs] == regs[d.rt]) pc += d.signedExtImm; break;     // beq
        case 0b000101: if (regs[d.rt] != regs[d.rs]) pc += d.signedExtImm; break;     // bne
        case 0b001010: regs[d.rt] = regs[d.rs] < d.signedExtImm ? 1 : 0; break;       // slti
        case 0b001011: regs[d.rt] = regs[d.rs] < d.signedExtImm ? 1 : 0; break;       // sltiu
        // J-type instruction
        case 0b000010: pc = d.address; break;                                         // j
        case 0b000011: regs[31] = pc; pc = d.address; break;                          // jal
        default: throw InvalidInstructionException();
    }

    if (debug) {
        dump();
        cout << "PC: 0x" << setfill('0') << setw(8) << hex << ((pc >> 2) - 1) << endl << endl;
    }
}

void Processor::dump() const {
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
        cout << regNames[i] << ": " << "0x" << setfill('0') << setw(8) << hex << regs[i] << "\t";
        if (((i + 1) % 8) == 0)
            cout << endl;
    }
}
