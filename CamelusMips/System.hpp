#ifndef SYSTEM_H
#define SYSTEM_H

#include <memory>
#include <atomic>
#include <thread>

#include "Assembler.hpp"
#include "Bus.hpp"
#include "Processor.hpp"
#include "VGA.hpp"
#include "Memory.hpp"
#include "Coprocessor.hpp"
#include "Options.hpp"

class System {
public:
    System(Options opt);
    System(): System(Options()) {};

private:
    std::shared_ptr<Bus> bus;
    std::shared_ptr<Coprocessor> cp0;
    std::shared_ptr<Processor> cpu;
    std::shared_ptr<VGA> vga;
    std::shared_ptr<Memory> memory;

    std::thread *process;
    std::atomic<bool> systemShouldQuit {false};

    Options options;
};

#endif