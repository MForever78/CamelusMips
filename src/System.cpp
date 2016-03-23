#include <memory>
#include <thread>
#include <chrono>

#include "Assembly.hpp"
#include "Assembler.hpp"
#include "VGA.hpp"
#include "System.hpp"

using namespace std;

System::System() {
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

    vector<Assembly> instAssembled = assembler.getInstAssembled();
    cpu.load(instAssembled);

    process = new thread([this] {
        for (;;) {
            cpu.tick();
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    });

    initVGA();
    for (;;) {
        vga->pollEvents();
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

System::~System() {
    process->join();
}

void System::initVGA() {
    unique_ptr<VGA> vp(new VGA());
    vga = std::move(vp);
}
