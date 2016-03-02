#include <vector>
#include <string>
#include <cstdint>
#include "gtest/gtest.h"

#include "../src/Assembler.hpp"
#include "../src/Assembly.hpp"

TEST(AssemblerTest, RegularRTypeInstructionTest) {
    std::string instLiteral[] = {
        "add    $t0, $t1, $t2",
        "addu   $t0, $t1, $t2",
        "sub    $t0, $t1, $t2",
        "subu   $t0, $t1, $t2",
        "and    $t0, $t1, $t2",
        "or     $t0, $t1, $t2",
        "xor    $t0, $t1, $t2",
        "nor    $t0, $t1, $t2",
        "slt    $t0, $t1, $t2",
        "sltu   $t0, $t1, $t2",
        "sllv   $t0, $t1, $t2",
        "srlv   $t0, $t1, $t2",
        "srav   $t0, $t1, $t2"
    };

    std::uint32_t assemblyLiteral[] = {
        0b00000001001010100100000000100000,     // add
        0b00000001001010100100000000100001,     // addu
        0b00000001001010100100000000100010,     // sub
        0b00000001001010100100000000100011,     // subu
        0b00000001001010100100000000100100,     // and
        0b00000001001010100100000000100101,     // or
        0b00000001001010100100000000100110,     // xor
        0b00000001001010100100000000100111,     // nor
        0b00000001001010100100000000101010,     // slt
        0b00000001001010100100000000101011,     // sltu
        0b00000001001010100100000000000100,     // sllv
        0b00000001001010100100000000000110,     // srlv
        0b00000001001010100100000000000111      // srav
    };

    Assembler assembler(std::vector<std::string> (instLiteral, instLiteral + sizeof(instLiteral) / sizeof(std::string)));
    std::vector<Assembly> instAssembled = assembler.getInstAssembled();
    std::vector<Assembly> assembly (assemblyLiteral, assemblyLiteral + sizeof(assemblyLiteral) / sizeof(std::uint32_t));

    EXPECT_EQ(instAssembled, assembly);
}

TEST(AssemblerTest, ShiftRTypeTest) {
    std::string instLiteral[] = {
        "sll    $t0, $t1, 15",
        "srl    $t0, $t1, 15",
        "sra    $t0, $t1, 15"
    };

    std::uint32_t assemblyLiteral[] = {
        0b00000000000010000100101111000000,     // sll
        0b00000000000010000100101111000010,     // srl
        0b00000000000010000100101111000011      // sra
    };

    Assembler assembler(std::vector<std::string> (instLiteral, instLiteral + sizeof(instLiteral) / sizeof(std::string)));
    std::vector<Assembly> instAssembled = assembler.getInstAssembled();
    std::vector<Assembly> assembly (assemblyLiteral, assemblyLiteral + sizeof(assemblyLiteral) / sizeof(std::uint32_t));

    EXPECT_EQ(instAssembled, assembly);
}

TEST(AssemblerTest, JrRTypeTest) {
    std::string instLiteral[] = {
        "jr     $t0"
    };

    std::uint32_t assemblyLiteral[] = {
        0b00000001000000000000000000001000      // jr
    };

    Assembler assembler(std::vector<std::string> (instLiteral, instLiteral + sizeof(instLiteral) / sizeof(std::string)));
    std::vector<Assembly> instAssembled = assembler.getInstAssembled();
    std::vector<Assembly> assembly (assemblyLiteral, assemblyLiteral + sizeof(assemblyLiteral) / sizeof(std::uint32_t));

    EXPECT_EQ(instAssembled, assembly);
}
