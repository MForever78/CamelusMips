#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include <cstdint>
#include <iostream>
#include <bitset>

class Assembly {
public:
    Assembly() {};
    Assembly(std::uint32_t m) : machineCode(m) {};

    friend std::ostream &operator<< (std::ostream &os, const Assembly &assembly) {
        os << std::bitset<32> (assembly.machineCode);
        return os;
    }

    friend bool operator==(const Assembly &lhs, const Assembly &rhs) {
        return lhs.machineCode == rhs.machineCode;
    }

private:
    std::uint32_t machineCode;
};

#endif