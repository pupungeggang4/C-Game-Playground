#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdio.h>

int main() {
    GLFWwindow *window;
    if (!glfwInit()) {
        printf("Cannot Init GLFW!\n");
        return -1;
    }
    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);
    window = glfwCreateWindow(1280, 720, "OpenGL Test Window", NULL, NULL);
    if (!window) {
        printf("Window creation failed!\n");
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-0.5f, -0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
