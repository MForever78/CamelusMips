#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <cstdint>
#include <iostream>

class Device {
public:
    Device() {};

    virtual void set(const std::uint32_t data) = 0;
    virtual std::uint32_t get() const = 0;

    inline void setAddress(const std::uint32_t addr) {
        operatingAddress = addr;
    }

    // interrupt
    bool interrupting = false;
protected:
    std::uint32_t operatingAddress = 0;
};

#endif