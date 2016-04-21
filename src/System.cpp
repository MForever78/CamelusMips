#include <memory>
#include <thread>
#include <chrono>
#include <vector>

#include "Assembly.hpp"
#include "Assembler.hpp"
#include "VGA.hpp"
#include "Memory.hpp"
#include "Bus.hpp"
#include "Processor.hpp"
#include "System.hpp"

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

using namespace std;

System::System() {
    /*
        Hardware initialize order:
            0. Memory
            1. VGA
            2. Coprocessor 0 as a special member of bus
            2. Bus, with peripherals as parameter
            3. CPU, with bus as parameter
    */

    memory.reset(new Memory());
    LOG(INFO) << "Initialized memory...";

    vga.reset(new VGA());
    LOG(INFO) << "Initialized VGA...";

    cp0.reset(new Coprocessor());
    LOG(INFO) << "Initialized Coprocessor 0...";

    // Initialize IO space
    vector<pair<Range, shared_ptr<Device>>> busOption;

    busOption.push_back(make_pair(Range(0x00000000, 0x7FFFFFFF), static_pointer_cast<Device>(memory)));
    busOption.push_back(make_pair(Range(0x80000001, 0x80FFFFFF), static_pointer_cast<Device>(vga)));

    // Initialize bus with IO space config
    bus.reset(new Bus(busOption));
    LOG(INFO) << "Initialized bus...";

    // Initialize cpu with bus
    cpu.reset(new Processor(bus, cp0));
    LOG(INFO) << "Initialized CPU...";

    // Initialize demo instructions
    const string instLiteral[] = {
        "start:",
        "       add    $t0, $zero, $zero",
        "       addi   $t0, $t0, 15",
        "loop:  add    $t1, $t0, $zero",
        "       addi   $t0, $t0, -1",
        "       bne    $t0, $zero, loop",
        "exit:  j      start"
    };

    vector<string> inst(instLiteral, instLiteral + sizeof(instLiteral) / sizeof(string));
    Assembler assembler(inst);
    LOG(INFO) << "Assembled instructions...";

    vector<Assembly> instAssembled = assembler.getInstAssembled();

    // Load instructions into memory
    memory->load(instAssembled);
    LOG(INFO) << "Loaded instructions to memory...";

    process = new thread([this] {
        LOG(INFO) << "CPU starts to run...";
        for (;;) {
            cpu->tick();
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    });

    for (;;) {
        // Must pull events in the main thread
        vga->pollEvents();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

System::~System() {
    process->join();
}
