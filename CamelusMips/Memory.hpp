#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdio>
#include <vector>
#include "Device.hpp"
#include "Assembly.hpp"

class Memory: public Device {
public:
    Memory(): memory() {};

    inline std::uint32_t get() const override {
        if (operatingAddress >= 65536) {
            throw std::runtime_error("Memory address overflow: " + std::to_string(operatingAddress));
        } else {
            return memory[operatingAddress];
        }
    }

    inline void set(const std::uint32_t data) override {
        if (operatingAddress >= 65536) {
            throw std::runtime_error("Memory address overflow: " + std::to_string(operatingAddress));
        } else {
            memory[operatingAddress] = data;
        }
    }

    inline void load(std::vector<Assembly> inst) {
        for (int i = 0; i < inst.size(); ++i) {
            memory[i] = inst[i].getMachineCode();
        }
    }

private:
    std::uint32_t memory[65536];
};

#endif
