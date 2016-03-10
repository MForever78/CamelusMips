#include <cstdint>

#include "gtest/gtest.h"

#include "../src/Disassembler.hpp"
#include "../src/Assembly.hpp"

TEST(DisassemblerTest, RegularRTypeTest) {
    Assembly assembly(0b00000001001010100100000000100001);  // addu
    Disassembler d;
    d.deAsm(assembly);

    EXPECT_EQ(9, d.rs);
    EXPECT_EQ(10, d.rt);
    EXPECT_EQ(8, d.rd);
    EXPECT_EQ(0, d.shamt);
    EXPECT_EQ(33, d.func);
    EXPECT_EQ(0, d.opcode);
}

TEST(DisassemblerTest, ShiftRTypeTest) {
    Assembly assembly(0b00000000000010010100001111000000);  // sll
    Disassembler d;
    d.deAsm(assembly);

    EXPECT_EQ(9, d.rt);
    EXPECT_EQ(8, d.rd);
    EXPECT_EQ(15, d.shamt);
    EXPECT_EQ(0, d.func);
    EXPECT_EQ(0, d.opcode);
}

TEST(DisassemblerTest, ITypeTest) {
    Assembly assembly(0b00110101001010000000000001001110);  // ori
    Disassembler d;
    d.deAsm(assembly);

    EXPECT_EQ(9, d.rs);
    EXPECT_EQ(8, d.rt);
    EXPECT_EQ(78, d.signedExtImm);
    EXPECT_EQ(13, d.opcode);
}

TEST(DisassemblerTest, JTypeTest) {
    Assembly assembly(0b00001000000000000010011100010000);  // j
    Disassembler d;
    d.deAsm(assembly);

    EXPECT_EQ(10000, d.address);
    EXPECT_EQ(2, d.opcode);
}
