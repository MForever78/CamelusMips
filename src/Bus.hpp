#ifndef BUS_HPP
#define BUS_HPP

#include <vector>
#include <cstdint>
#include <iostream>

#include "Device.hpp"

class Range {
public:
    Range(std::uint32_t l, std::uint32_t u): lower(l), upper(u) {};

    std::uint32_t getRelativeAddr(const std::uint32_t addr) const {
        return addr - lower;
    }

    inline int compare(const std::uint32_t addr) const {
        if (addr < lower) return -1;
        if (addr >= lower && addr <= upper) return 0;
        return 1;
    }

    friend std::ostream &operator<<(std::ostream &os, Range range) {
        os << "lower: " << range.lower << " | upper: " << range.upper;
        return os;
    }

private:
    std::uint32_t upper, lower;
};

class Bus {
public:
    Bus(const std::vector<std::pair<Range, std::shared_ptr<Device>>> &devices): devices(devices) {};
    std::shared_ptr<Device> at(const std::uint32_t addr);

private:
    std::vector<std::pair<Range, std::shared_ptr<Device>>> devices;
};

#endif