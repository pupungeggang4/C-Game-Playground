#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdio.h>

int main() {
    float pos[2] = {0, 0};
    GLFWwindow* window;
    if (!glfwInit()) {
        printf("Failed to initialize GLFW.\n");
        return -1;
    }

    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);
    window = glfwCreateWindow(800, 600, "Dark Blending Test", NULL, NULL);
    if (!window) {
        printf("Failed to create GLFW window.\n");
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    printf("OpenGL Version: %s", glGetString(GL_VERSION));

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glEnable(GL_STENCIL_TEST);
        glClearBuffer(GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}
