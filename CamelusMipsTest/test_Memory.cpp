#include <vector>

#include "catch.hpp"

#include "Assembler.hpp"
#include "Assembly.hpp"
#include "Memory.hpp"

TEST_CASE("Memory Test") {
    Memory memory;
    
    SECTION("Init to zero") {
        for (int i = 0; i < 65536; ++i) {
            memory.setAddress(i);
            CHECK(memory.get() == 0);
        }
    }
    
    SECTION("Load and read") {
        const std::string instLiteral[] = {
            "start:",
            "       add    $t0, $zero, $zero",
            "       addi   $t0, $t0, 15",
            "loop:  add    $t1, $t0, $zero",
            "       addi   $t0, $t0, -1",
            "       bne    $t0, $zero, loop",
            "exit:  j      start"
        };
        
        std::vector<std::string> inst(instLiteral, instLiteral + sizeof(instLiteral) / sizeof(std::string));
        Assembler assembler(inst);
        
        std::vector<Assembly> instAssembled = assembler.getInstAssembled();
        memory.load(instAssembled);
        
        for (int i = 0; i < instAssembled.size(); ++i) {
            memory.setAddress(i);
            CHECK(memory.get() == instAssembled[i].getMachineCode());
        }
    }
}