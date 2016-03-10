#include <iostream>
#include <vector>
#include "Assembler.hpp"
#include "Processor.hpp"

using namespace std;

int main() {
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
    Processor cpu(instAssembled);
    cpu.run();
}
