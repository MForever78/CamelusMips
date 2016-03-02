#include <vector>
#include <string>
#include <cstdint>
#include "gtest/gtest.h"

#include "../src/Assembler.hpp"
#include "../src/Assembly.hpp"

TEST(AssemblerTest, RTypeInstructionTest) {
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
        //"sll    $t0, $t1, 15",
        //"srl    $t0, $t1, 15",
        //"sra    $t0, $t1, 15",
        "sllv   $t0, $t1, $t2",
        "srlv   $t0, $t1, $t2",
        "srav   $t0, $t1, $t2"
        //"jr     $t0"
    };

    std::uint32_t assemblyLiteral[] = {
        0b00000001000010010101000000100000,     // add
        0b00000001000010010101000000100001,     // addu
        0b00000001000010010101000000100010,     // sub
        0b00000001000010010101000000100011,     // subu
        0b00000001000010010101000000100100,     // and
        0b00000001000010010101000000100101,     // or
        0b00000001000010010101000000100110,     // xor
        0b00000001000010010101000000100111,     // nor
        0b00000001000010010101000000101010,     // slt
        0b00000001000010010101000000101011,     // sltu
        //0b00000001000010010101001111000000,     // sll
        //0b00000001000010010101001111000010,     // srl
        //0b00000001000010010101001111000011,     // sra
        0b00000001000010010101000000000100,     // sllv
        0b00000001000010010101000000000110,     // srlv
        0b00000001000010010101000000000111     // srav
        //0b00000001000000000000000000001000      // jr
    };

    Assembler assembler(std::vector<std::string> (instLiteral, instLiteral + sizeof(instLiteral) / sizeof(std::string)));
    std::vector<Assembly> instAssembled = assembler.getInstAssembled();
    std::vector<Assembly> assembly (assemblyLiteral, assemblyLiteral + sizeof(assemblyLiteral) / sizeof(std::uint32_t));

    EXPECT_EQ(instAssembled, assembly);
}
