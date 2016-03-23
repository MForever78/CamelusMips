#include "GLFW/glfw3.h"
#include "OpenGL/gl.h"

#include <iostream>
#include <thread>

#include "VGA.hpp"

using namespace std;

VGA::VGA() {
    if (!glfwInit())
        throw runtime_error("GLFW init error!");
    window = glfwCreateWindow(800, 600, "Camelus Mips", NULL, NULL);

    for (int i = 0; i < 600; i++) {
        for (int j = 0; j < 800; j++) {
            int c = ((((i&0x8)==0)^((j&0x8))==0))*255;
            vram[i][j][0] = (GLubyte) c;
            vram[i][j][1] = (GLubyte) c;
            vram[i][j][2] = (GLubyte) c;
        }
    }

    monitor = new thread([this] {
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glShadeModel(GL_FLAT);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        while (!glfwWindowShouldClose(window)) {
            float ratio;
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            ratio = width / (float) height;

            glClear(GL_COLOR_BUFFER_BIT);
            glRasterPos2i(-1, -1);
            glDrawPixels(800, 600, GL_RGB, GL_UNSIGNED_BYTE, vram);
            glfwSwapBuffers(window);
        }

        glfwDestroyWindow(window);
    });
}

VGA::~VGA() {
    glfwTerminate();
    monitor->join();
}

void VGA::pollEvents() {
    glfwPollEvents();
}
