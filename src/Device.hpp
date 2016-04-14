#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <cstdint>

class Device {
public:
    virtual void set(const std::uint32_t data) = 0;
    virtual std::uint32_t get(const std::uint32_t addr) const = 0;
    virtual void setAddress(const std::uint32_t addr) = 0;
};

#endif