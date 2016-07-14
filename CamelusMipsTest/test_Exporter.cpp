#include <sstream>

#include "catch.hpp"
#include "Exporter.hpp"
#include "Assembler.hpp"

TEST_CASE("Exporter test") {
    std::vector<std::string> instLiteral = {
        "start:",
        "       add    $t0, $zero, $zero",
        "       addi   $t0, $t0, 15",
        "loop:  add    $t1, $t0, $zero",
        "       addi   $t0, $t0, -1",
        "       bne    $t0, $zero, loop",
        "exit:  j      start"
    };
    std::vector<Assembly> instAssembled;
    
    Assembler assembler(instLiteral);
    instAssembled = assembler.getInstAssembled();

    SECTION("Export COE test") {
        std::vector<std::string> coe = {
            "memory_initialization_radix=16;",
            "memory_initialization_vector=",
            "00004020,",
            "2108000f,",
            "01004820,",
            "2108ffff,",
            "1408fff4,",
            "08000000;"
        };
        
        std::string coeString;
        
        for (auto c: coe)
            coeString += c + "\n";
        
        Exporter exporter;
        std::stringstream stream;
        
        exporter.exportAssembly(instAssembled, stream, Exporter::COE);
        std::string exportedCOE = stream.str();
        
        CHECK(exportedCOE == coeString);
    }
    
    SECTION("Export HEX test") {
        std::vector<std::string> hex = {
            "00004020",
            "2108000f",
            "01004820",
            "2108ffff",
            "1408fff4",
            "08000000"
        };
        
        std::string hexString;
        
        for (auto h: hex)
            hexString += h + "\n";
        
        Exporter exporter;
        std::stringstream stream;
        
        exporter.exportAssembly(instAssembled, stream, Exporter::HEX);
        std::string exportedHex = stream.str();
        
        CHECK(exportedHex == hexString);
    }
    
    SECTION("Export ASCII bin test") {
        std::vector<std::string> asciiBin = {
            "00000000000000000100000000100000",
            "00100001000010000000000000001111",
            "00000001000000000100100000100000",
            "00100001000010001111111111111111",
            "00010100000010001111111111110100",
            "00001000000000000000000000000000"
        };
        
        std::string binString;
        
        for (auto b: asciiBin)
            binString += b + "\n";
        
        Exporter exporter;
        std::stringstream stream;
        
        exporter.exportAssembly(instAssembled, stream, Exporter::ASCIIBIN);
        std::string exportedBin = stream.str();
        
        CHECK(exportedBin == binString);
    }
    
    SECTION("Export BIN test") {
        const unsigned char bin[] = {
            0x20, 0x40, 0x00, 0x00,
            0x0f, 0x00, 0x08, 0x21,
            0x20, 0x48, 0x00, 0x01,
            0xff, 0xff, 0x08, 0x21,
            0xf4, 0xff, 0x08, 0x14,
            0x00, 0x00, 0x00, 0x08
        };
        
        Exporter exporter;
        std::stringstream stream;
        
        exporter.exportAssembly(instAssembled, stream, Exporter::BIN);
        char exportedBin[24];
        stream.read(&exportedBin[0], 24);
        
        unsigned char *exportedUnsignedBin = reinterpret_cast<unsigned char *>(exportedBin);
        
        for (int i = 0; i < 24; ++i) {
            CHECK(bin[i] == exportedUnsignedBin[i]);
        }
    }
}
