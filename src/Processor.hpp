#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <cstdint>
#include "Assembly.hpp"
#include "Disassembler.hpp"
#include "Coprocessor.hpp"
#include "Bus.hpp"

class Processor {
public:
    Processor(std::shared_ptr<Bus> bus, std::shared_ptr<Coprocessor> cp0):
            d(), pc(0), regs(), bus(bus), cp0(cp0) {};
    void tick();

    // getter
    std::uint32_t getPC() const {
        return pc;
    }

private:
    // constants
    static const std::uint32_t interruptHandlerAddress;

    // helper
    Disassembler d;

    // core member
    std::uint32_t pc;
    std::uint32_t regs[32];
    std::shared_ptr<Bus> bus;
    std::shared_ptr<Coprocessor> cp0;

    // handle interruption
    void handleInterruption();
};

#endif
