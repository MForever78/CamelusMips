//
// Created by MForever78 on 16/4/19.
//

#include "Coprocessor.hpp"

bool Coprocessor::interruptable() const {
    return (regs[12] & 1) != 0;
}

bool Coprocessor::excepting() const {
    return (regs[12] & 2) != 0;
}

bool Coprocessor::userMode() const {
    return (regs[12] & 16) != 0;
}

bool Coprocessor::deviceInterruptable(const uint32_t busCode) const {
    return ((1 << busCode) & (regs[12] >> 8)) == 1;
}

bool Coprocessor::branched() const {
    return (regs[13] >> 31) == 1;
}

bool Coprocessor::interrupting() const {
    static uint32_t mask = 0x0000F000;
    return (regs[13] & mask) != 0;
}

uint32_t Coprocessor::interruptingBusCode() const {
    static uint32_t mask = 0x0000F000;
    int i = 0;
    for (uint32_t busCode = regs[13] & mask; busCode > 0; busCode >>= 1) {
        if ((busCode & 1) == 1) return static_cast<uint32_t>(i);
    }
    return 1024;
}

Coprocessor::Exception Coprocessor::getException() const {
    static uint32_t mask = 0x0000001F;
    uint32_t code = (regs[13] >> 2) & mask;
    return static_cast<Coprocessor::Exception>(code);
}

void Coprocessor::disableInterruptForCode(uint32_t busCode) {
    uint32_t disableMask = ~(1 << (busCode + 8));
    regs[12] &= disableMask;
}