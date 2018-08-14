#include <GLFW/glfw3.h>

#ifndef HMME_INPUT_H
#define HMME_INPUT_H

struct Input {
    double mouseX;
    double mouseY;
};

Input GetInput(GLFWwindow *window) {
    Input i;

    glfwGetCursorPos(window, &i.mouseX, &i.mouseY);

    return i;
}

#endif
