#include "Bus.hpp"
#include "Device.hpp"

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
