#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <cstdint>
#include "Assembly.hpp"
#include "Disassembler.hpp"

class Processor {
public:
    Processor(std::vector<Assembly> &instIn): instructions(instIn), running(false), pc(0) {
        for (auto reg: memory)
            reg = 0;
    }

    void run();

    // setter
    void load(std::vector<Assembly> &instIn);

private:
    // status
    bool running;

    // helper
    Disassembler d;

    // core member
    std::vector<Assembly> instructions;
    uint32_t pc;
    uint32_t memory[32];
};

#endif