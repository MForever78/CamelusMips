#include <sstream>

#include "gtest/gtest.h"
#include "../src/Exporter.hpp"
#include "../src/Assembler.hpp"

TEST(ExporterTest, exportCOETest) {
    std::vector<std::string> instLiteral = {
        "start:",
        "       add    $t0, $zero, $zero",
        "       addi   $t0, $t0, 15",
        "loop:  add    $t1, $t0, $zero",
        "       addi   $t0, $t0, -1",
        "       bne    $t0, $zero, loop",
        "exit:  j      start"
    };

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

    for (auto it = coe.begin(); it != coe.end(); ++it)
        coeString += *it + "\n";

    Assembler assembler(instLiteral);
    std::vector<Assembly> instAssembled = assembler.getInstAssembled();

    Exporter exporter;
    std::stringstream stream;

    exporter.exportAssembly(instAssembled, stream, Exporter::COE);
    std::string exportedCOE = stream.str();

    EXPECT_EQ(exportedCOE, coeString);
}
