#include <vector>

#include "gtest/gtest.h"

#include "../src/Assembler.hpp"
#include "../src/Assembly.hpp"
#include "../src/Memory.hpp"

TEST(MemoryTest, InitToZeroTest) {
    Memory memory;

    for (int i = 0; i < 65536; ++i) {
        memory.setAddress(i);
        EXPECT_EQ(0, memory.get());
    }
}

TEST(MemoryTest, LoadAndReadTest) {
    Memory memory;
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
        EXPECT_EQ(instAssembled[i].getMachineCode(), memory.get());
    }
}