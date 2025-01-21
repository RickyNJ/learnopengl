#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "test", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    return 0;
}
