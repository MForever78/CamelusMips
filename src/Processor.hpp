#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <cstdint>
#include "Assembly.hpp"
#include "Disassembler.hpp"
#include "Bus.hpp"

class Processor {
public:
    Processor(std::shared_ptr<Bus> bus): pc(0), regs(), bus(bus) {};
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
    std::uint32_t pc;
    std::uint32_t regs[32];
    std::shared_ptr<Bus> bus;
};

#endif