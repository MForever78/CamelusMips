#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <cstdint>
#include <iostream>

class Device {
public:
    virtual void set(const std::uint32_t data) = 0;
    virtual std::uint32_t get() const = 0;

    inline void setAddress(const std::uint32_t addr) {
        operatingAddress = addr;
    }
protected:
    std::uint32_t operatingAddress;
};

#endif