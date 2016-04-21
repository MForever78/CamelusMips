#ifndef SYSTEM_H
#define SYSTEM_H

#include <memory>

#include "Assembler.hpp"
#include "Bus.hpp"
#include "Processor.hpp"
#include "VGA.hpp"
#include "Memory.hpp"
#include "Coprocessor.hpp"

class System {
public:
    System();
    ~System();

private:
    std::shared_ptr<Bus> bus;
    std::shared_ptr<Coprocessor> cp0;
    std::shared_ptr<Processor> cpu;
    std::shared_ptr<VGA> vga;
    std::shared_ptr<Memory> memory;

    std::thread *process;
};

#endif