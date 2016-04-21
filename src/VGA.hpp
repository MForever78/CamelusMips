#ifndef VGA_H
#define VGA_H

#include <thread>
#include <atomic>
#include <cstdint>
#include "GLFW/glfw3.h"
#include "OpenGL/gl.h"
#include "Device.hpp"

#include "easylogging++.h"

class VGA: public Device {
public:
    VGA();
    ~VGA();

    GLubyte vram[600][800][3];
    void pollEvents();

    inline void set(const std::uint32_t data) override {

        int row = operatingAddress / 800;
        int col = operatingAddress - row * 800;
        GLubyte blue = static_cast<GLubyte>(data);
        GLubyte green = static_cast<GLubyte>(data >> 8);
        GLubyte red = static_cast<GLubyte>(data >> 16);

        vram[row][col][0] = red;
        vram[row][col][1] = green;
        vram[row][col][2] = blue;
    }

    inline std::uint32_t get() const override {
        int row = operatingAddress / 800;
        int col = operatingAddress - row * 800;
        std::uint32_t data = 0;

        data += vram[row][col][0];
        data <<= 8;
        data += vram[row][col][1];
        data <<= 8;
        data += vram[row][col][2];

        return data;
    }

    std::atomic<bool> shouldQuit {false};

private:
    GLFWwindow *window;
    std::thread *monitor;
};

#endif
