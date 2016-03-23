#ifndef VGA_H
#define VGA_H

#include <thread>
#include "GLFW/glfw3.h"
#include "OpenGL/gl.h"

class VGA {
public:
    VGA();
    ~VGA();

    void pollEvents();

private:
    GLFWwindow *window;
    std::thread *monitor;
    GLubyte vram[600][800][3];

    void draw();
};

#endif
