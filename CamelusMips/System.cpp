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

System::System(Options opt): options(opt) {
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
    busOption.push_back(make_pair(Range(0x80000000, 0x80FFFFFF), static_pointer_cast<Device>(vga)));

    // Initialize bus with IO space config
    bus.reset(new Bus(busOption));
    LOG(INFO) << "Initialized bus...";

    // Initialize cpu with bus
    cpu.reset(new Processor(bus, cp0, options.debug));
    LOG(INFO) << "Initialized CPU...";

    // Initialize demo instructions
    const string instLiteral[] = {
        "# s0 is the vram base addr",
        "lui     $s0, 0x8000",
        "# s1 is the loop uppper bound",
        "addi    $s1, $zero, 600",
        "# t0 is the color",
        "add     $t0, $zero, $zero",
        "# t1 is red",
        "addi    $t1, $zero, 255",
        "# t2 is green",
        "add     $t2, $zero, $zero",
        "# t3 is blue",
        "add     $t3, $zero, $zero",
        "drawframe:",
        "beq     $s1, $zero, exit",
        "# assemble the color",
        "add     $a0, $zero, $t1",
        "sll     $a0, $a0, 8",
        "add     $a0, $a0, $t2",
        "sll     $a0, $a0, 8",
        "add     $a0, $a0, $t3",
        "jal     drawline",
        "# change color",
        "addi    $t1, $t1, 1",
        "addi    $t2, $t2, 1",
        "addi    $t3, $t3, 0",
        "# sub loop variable",
        "addi    $s1, $s1, -1",
        "j       drawframe",
        "drawline:",
        "addi    $t4, $t4, 800",
        "drawpixel:",
        "sw      $a0, 0($s0)",
        "addi    $s0, $s0, 1",
        "addi    $t4, $t4, -1",
        "bne     $t4, $zero, drawpixel",
        "jr      $ra",
        "exit:",
        "j       exit"
    };

    // Load demo instructions if external file is not specified
    vector<string> inst(instLiteral, instLiteral + sizeof(instLiteral) / sizeof(string));
    if (options.instructions.size() > 0) {
        inst = options.instructions;
    }
    Assembler assembler(inst);
    LOG(INFO) << "Assembled instructions...";

    vector<Assembly> instAssembled = assembler.getInstAssembled();
    LOG(INFO) << "Assembly length: " << instAssembled.size();

    // Load instructions into memory
    memory->load(instAssembled);
    LOG(INFO) << "Loaded instructions to memory...";

    process = new thread([this] {
        LOG(INFO) << "CPU starts to run...";
        for (;;) {
            cpu->tick();
            if (systemShouldQuit) {
                LOG(INFO) << "CPU exited";
                break;
            }
            // this_thread::sleep_for(chrono::milliseconds(1));
            if (options.debug) {
                cin.get();
            }
        }
    });

    for (;;) {
        // Must pull events in the main thread
        vga->pollEvents();
        if (vga->shouldQuit) {
            LOG(INFO) << "VGA exited";
            systemShouldQuit = true;
            break;
        }
    }

    process->join();
    LOG(INFO) << "System shutting down...";
}
