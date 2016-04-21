#include "Bus.hpp"

using namespace std;

shared_ptr<Device> Bus::at(const uint32_t addr) {
    for (auto &device: devices) {
        if (device.first.compare(addr) == 0) {
            uint32_t relativeAddr = device.first.getRelativeAddr(addr);
            device.second->setAddress(relativeAddr);
            return device.second;
        }
    }
    throw runtime_error("No IO address found for: " + to_string(addr));
}

void Bus::updateInterruptingDevice() {
    uint32_t interrupts = 0;
    for (int i = 0; i < devices.size(); ++i) {
        if (devices[i].second->interrupting) {
            interrupts |= (1 << i);
        }
    }
    interrupts &= (cp0->regs[12] >> 8);

    static uint32_t interruptClearMask = 0xFFFF00FF;
    auto cause = cp0->regs[13];
    cp0->regs[13] = (cause & interruptClearMask) | (interrupts << 8);
}
