#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <cstdint>
#include "Assembly.hpp"
#include "Disassembler.hpp"

class Processor {
public:
    Processor();
    Processor(std::vector<Assembly> &instIn): instructions(instIn), pc(0) {
        regs[0] = 0;
    }

    void tick();

    // setter
    void load(std::vector<Assembly> &instIn);

    // getter
    uint32_t getPC() const {
        return pc;
    }

private:
    // status
    bool running;

    // helper
    Disassembler d;

    // core member
    std::vector<Assembly> instructions;
    uint32_t pc;
    uint32_t regs[32];
    uint32_t memory[65536];
};

#endif