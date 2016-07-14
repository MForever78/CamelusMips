#include <cstdint>

#include "catch.hpp"

#include "Disassembler.hpp"
#include "Assembly.hpp"

TEST_CASE("DisassemblerTest") {
    Disassembler d;
    
    SECTION("RegularRTypeTest") {
        Assembly assembly(0b00000001001010100100000000100001);  // addu
        d.deAsm(assembly);
        
        CHECK(d.rs == 9);
        CHECK(d.rt == 10);
        CHECK(d.rd == 8);
        CHECK(d.shamt == 0);
        CHECK(d.func == 33);
        CHECK(d.opcode == 0);
    }
    
    SECTION("ShiftRTypeTest") {
        Assembly assembly(0b00000000000010010100001111000000);  // sll
        d.deAsm(assembly);
        
        CHECK(d.rt == 9);
        CHECK(d.rd == 8);
        CHECK(d.shamt == 15);
        CHECK(d.func == 0);
        CHECK(d.opcode == 0);
    }
    
    SECTION("ITypeTest") {
        Assembly assembly(0b00110101001010000000000001001110);  // ori
        d.deAsm(assembly);
        
        CHECK(d.rs == 9);
        CHECK(d.rt == 8);
        CHECK(d.signedExtImm == 78);
        CHECK(d.opcode == 13);
    }
    
    SECTION("JTypeTest") {
        Assembly assembly(0b00001000000000000010011100010000);  // j
        d.deAsm(assembly);
        
        CHECK(d.address == 10000);
        CHECK(d.opcode == 2);
    }
}
