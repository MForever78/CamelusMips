//
// Created by MForever78 on 16/4/19.
//

#ifndef COPROCESSOR_HPP
#define COPROCESSOR_HPP

#include "Device.hpp"

class Coprocessor {
public:
    Coprocessor(): regs() {};

    // Status register related
    bool interruptable() const;
    bool excepting() const;
    bool userMode() const;
    bool deviceInterruptable(const std::uint32_t busCode) const;

    // Cause register related
    enum Exception {
        // Hardware interrupt
        INT,
        // Address error (load or instruction fetch)
        ADEL,
        // Address error (store)
        ADES,
        // Bus error on instruction fetch
        IBE,
        // Bus error on data load or store
        DBE,
        // System call
        SYS,
        // Breakpoint
        BP,
        // Reserved instruction
        RI,
        // Coprocessor unimplemented
        CPU,
        // Arithmetic overflow
        OV,
        // Trap
        TR,
        // Float point
        FPE
    };
    bool branched() const;
    bool interrupting() const;
    std::uint32_t interruptingBusCode() const;
    Coprocessor::Exception getException() const;
    void disableInterruptForCode(std::uint32_t busCode);

    std::uint32_t regs[32];
};


#endif //CAMELUSMIPS_COPROCESSOR_HPP
