#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include <cstdint>
#include <iostream>
#include <bitset>
#include <iomanip>
#include <sstream>

class Assembly {
public:
    Assembly() {};
    Assembly(std::uint32_t m) : machineCode(m) {};

    std::string toHex() const {
        std::stringstream stream;
        stream << std::setfill('0') << std::setw(8) << std::hex << machineCode;
        return stream.str();
    }

    char *toBinaryBlocks() const {
        char *binBlocks = new char[4];
        binBlocks[0] = machineCode & 0xff;
        binBlocks[1] = (machineCode >> 8) & 0xff;
        binBlocks[2] = (machineCode >> 16) & 0xff;
        binBlocks[3] = (machineCode >> 24) & 0xff;

        return binBlocks;
    }

    friend std::ostream &operator<< (std::ostream &os, const Assembly &assembly) {
        os << std::bitset<32> (assembly.machineCode);
        return os;
    }

    friend bool operator==(const Assembly &lhs, const Assembly &rhs) {
        return lhs.machineCode == rhs.machineCode;
    }

    friend bool operator!=(const Assembly &lhs, const Assembly &rhs) {
        return !(lhs == rhs);
    }

private:
    std::uint32_t machineCode;
};

#endif