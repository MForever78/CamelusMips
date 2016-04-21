//
// Created by MForever78 on 16/4/19.
//

#ifndef TIMER_HPP
#define TIMER_HPP

#include "Device.hpp"

class Timer: Device {
public:
    inline void set(const std::uint32_t data) override {
        counting = true;
        reverseCount = data;
    }
    inline std::uint32_t get() const override {
        return clock;
    };
    void tick() {
        clock++;
        timeSlice++;
        if (counting) reverseCount--;

        if (reverseCount == 0) {
            counting = false;
            interrupting = true;
        }
    }

private:
    std::uint32_t clock = 0;
    bool counting = false;
    std::uint32_t reverseCount = 0;
    std::uint32_t timeSlice = 0;
};


#endif //TIMER_HPP
