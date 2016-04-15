#include <memory>
#include <vector>

#include "gtest/gtest.h"
#include "../src/Bus.hpp"
#include "../src/Device.hpp"
#include "../src/Memory.hpp"
#include "../src/Assembler.hpp"
#include "../src/Assembly.hpp"

TEST(BusTest, ConnectMemoryTest) {
    std::shared_ptr<Memory> memory(new Memory());
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
    memory->load(instAssembled);

    std::vector<std::pair<Range, std::shared_ptr<Device>>> busOption;
    busOption.push_back(std::make_pair(Range(0x00000000, 0x7FFFFFFF), std::static_pointer_cast<Device>(memory)));

    Bus bus(busOption);

    for (int i = 0; i < instAssembled.size(); ++i) {
        EXPECT_EQ(instAssembled[i].getMachineCode(), bus.at(i)->get());
    }
}
