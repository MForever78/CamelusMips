#include <vector>
#include <string>
#include <cstdint>
#include "catch.hpp"

#include "Assembler.hpp"
#include "Assembly.hpp"

TEST_CASE("Assembler test") {
    SECTION("Regular RType instuction test") {
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
        
        CHECK(instAssembled == assembly);
    }
    
    SECTION("Shift RType test") {
        std::string instLiteral[] = {
            "sll    $t0, $t1, 15",
            "srl    $t0, $t1, 15",
            "sra    $t0, $t1, 15"
        };
        
        std::uint32_t assemblyLiteral[] = {
            0b00000000000010010100001111000000,     // sll
            0b00000000000010010100001111000010,     // srl
            0b00000000000010010100001111000011      // sra
        };
        
        Assembler assembler(std::vector<std::string> (instLiteral, instLiteral + sizeof(instLiteral) / sizeof(std::string)));
        std::vector<Assembly> instAssembled = assembler.getInstAssembled();
        std::vector<Assembly> assembly (assemblyLiteral, assemblyLiteral + sizeof(assemblyLiteral) / sizeof(std::uint32_t));
        
        CHECK(instAssembled == assembly);
    }
    
    SECTION("JR RType test") {
        std::string instLiteral[] = {
            "jr     $t0"
        };
        
        std::uint32_t assemblyLiteral[] = {
            0b00000001000000000000000000001000      // jr
        };
        
        Assembler assembler(std::vector<std::string> (instLiteral, instLiteral + sizeof(instLiteral) / sizeof(std::string)));
        std::vector<Assembly> instAssembled = assembler.getInstAssembled();
        std::vector<Assembly> assembly (assemblyLiteral, assemblyLiteral + sizeof(assemblyLiteral) / sizeof(std::uint32_t));
        
        CHECK(instAssembled == assembly);
    }
    
    SECTION("Regular IType test") {
        std::string instLiteral[] = {
            "addi   $t0, $t1, -78",
            "addi   $t0, $t1, 0x10ff",
            "addiu  $t0, $t1, 78",
            "andi   $t0, $t1, 78",
            "ori    $t0, $t1, 78",
            "xori   $t0, $t1, 78",
            "slti   $t0, $t1, 78",
            "sltiu  $t0, $t1, 78"
        };
        
        std::uint32_t assemblyLiteral[] = {
            0b00100001001010001111111110110010,     // addi
            0b00100001001010000001000011111111,     // addi
            0b00100101001010000000000001001110,     // addiu
            0b00110001001010000000000001001110,     // andi
            0b00110101001010000000000001001110,     // ori
            0b00111001001010000000000001001110,     // xori
            0b00101001001010000000000001001110,     // slti
            0b00101101001010000000000001001110      // sltiu
        };
        
        Assembler assembler(std::vector<std::string> (instLiteral, instLiteral + sizeof(instLiteral) / sizeof(std::string)));
        std::vector<Assembly> instAssembled = assembler.getInstAssembled();
        std::vector<Assembly> assembly (assemblyLiteral, assemblyLiteral + sizeof(assemblyLiteral) / sizeof(std::uint32_t));
        
        CHECK(instAssembled == assembly);
    }
    
    SECTION("LUI IType test") {
        std::string instLiteral[] = {
            "lui    $t0, 100",
            "lui    $t0, 0x1000"
        };
        
        std::uint32_t assemblyLiteral[] = {
            0b00111100000010000000000001100100,     // lui
            0b00111100000010000001000000000000
        };
        
        Assembler assembler(std::vector<std::string> (instLiteral, instLiteral + sizeof(instLiteral) / sizeof(std::string)));
        std::vector<Assembly> instAssembled = assembler.getInstAssembled();
        std::vector<Assembly> assembly (assemblyLiteral, assemblyLiteral + sizeof(assemblyLiteral) / sizeof(std::uint32_t));
        
        CHECK(instAssembled == assembly);
    }
    
    SECTION("Save load IType test") {
        std::string instLiteral[] = {
            "lw     $t0, 78($t1)",
            "sw     $t0, 78($t1)"
        };
        
        std::uint32_t assemblyLiteral[] = {
            0b10001101001010000000000001001110,     // lw
            0b10101101001010000000000001001110      // sw
        };
        
        Assembler assembler(std::vector<std::string> (instLiteral, instLiteral + sizeof(instLiteral) / sizeof(std::string)));
        std::vector<Assembly> instAssembled = assembler.getInstAssembled();
        std::vector<Assembly> assembly (assemblyLiteral, assemblyLiteral + sizeof(assemblyLiteral) / sizeof(std::uint32_t));
        
        CHECK(instAssembled == assembly);
    }
    
    SECTION("JType test") {
        std::string instLiteral[] = {
            "j      10000",
            "jal    10078"
        };
        
        std::uint32_t assemblyLiteral[] = {
            0b00001000000000000010011100010000,     // j
            0b00001100000000000010011101011110      // jal
        };
        
        Assembler assembler(std::vector<std::string> (instLiteral, instLiteral + sizeof(instLiteral) / sizeof(std::string)));
        std::vector<Assembly> instAssembled = assembler.getInstAssembled();
        std::vector<Assembly> assembly (assemblyLiteral, assemblyLiteral + sizeof(assemblyLiteral) / sizeof(std::uint32_t));
        
        CHECK(instAssembled == assembly);
    }
    
    SECTION("Generate symbol table test") {
        std::string instLiteral[] = {
            "L1:",
            "L2:",
            "       add    $t0, $zero, $zero",
            "       addi   $t0, $t0, 15",
            "L3:    add    $t1, $t0, $zero",
            "exit:  xor    $t1, $t1, $t1"
        };
        
        std::map<std::string, int> symbolTable = {
            {"L1", 0},
            {"L2", 0},
            {"L3", 2},
            {"exit", 3}
        };
        
        Assembler assembler(std::vector<std::string> (instLiteral, instLiteral + sizeof(instLiteral) / sizeof(std::string)));
        std::map<std::string, int> symbolTableAssembled = assembler.getSymbolTable();
        
        CHECK(symbolTableAssembled == symbolTable);
    }
    
    SECTION("Label substitute test") {
        std::string instLiteral[] = {
            "start:",
            "       add    $t0, $zero, $zero",
            "       addi   $t0, $t0, 15",
            "loop:  add    $t1, $t0, $zero",
            "       addi   $t0, $t0, -1",
            "       bne    $t0, $zero, loop",
            "exit:  j      start"
        };
        
        std::vector<std::string> instSubstituted = {
            "add    $t0, $zero, $zero",
            "addi   $t0, $t0, 15",
            "add    $t1, $t0, $zero",
            "addi   $t0, $t0, -1",
            "bne    $t0, $zero, -12",
            "j      0"
        };
        
        Assembler assembler(std::vector<std::string> (instLiteral, instLiteral + sizeof(instLiteral) / sizeof(std::string)));
        std::vector<std::string> instTrimmed = assembler.getInstTrimmed();
        
        CHECK(instTrimmed == instSubstituted);
    }
}
