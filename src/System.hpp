#ifndef SYSTEM_H
#define SYSTEM_H

#include <memory>

#include "Assembler.hpp"
#include "Processor.hpp"
#include "VGA.hpp"

class System {
public:
    System();
    ~System();
    void initVGA();

private:
    // Processor is necessary, but vga is optional
    Processor cpu;
    std::unique_ptr<VGA> vga;

    std::thread *process;
};

#endif