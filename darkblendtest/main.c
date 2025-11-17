#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

void renderRect(float[], float[]);
void renderCircle(float[], float, int);
void keyHandle(GLFWwindow*, int, int, int, int);
void move();

float pos[2] = {0, 0};
int keyPressed[4] = {0, 0, 0, 0};

int main() {
    GLFWwindow* window;
    if (!glfwInit()) {
        printf("Failed to initialize GLFW.\n");
        return -1;
    }

    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);
    window = glfwCreateWindow(640, 640, "Dark Blending Test", NULL, NULL);
    if (!window) {
        printf("Failed to create GLFW window.\n");
        return -1;
    }
    glfwSetKeyCallback(window, keyHandle);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

    while (!glfwWindowShouldClose(window)) {
        move();
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable();
        renderCircle(pos, 0.4, 40);

        /*
        glEnable(GL_STENCIL_TEST);
        glClearStencil(0);
        glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
        glStencilFunc(GL_ALWAYS, 1, ~0);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        renderCircle(pos, 0.4, 40);

        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDepthMask(GL_TRUE);
        glStencilFunc(GL_NOTEQUAL, 1, ~0);
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        renderRect((float[]){0.0, 0.0, 2.0, 2.0}, (float[]){0.0, 0.0, 0.0});
        glDisable(GL_STENCIL_TEST);
        */

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}

void move() {
    if (keyPressed[LEFT]) {
        pos[0] -= 0.01;
    }
    if (keyPressed[RIGHT]) {
        pos[0] += 0.01;
    }
    if (keyPressed[UP]) {
        pos[1] += 0.01;
    }
    if (keyPressed[DOWN]) {
        pos[1] -= 0.01;
    }
}

void keyHandle(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_W) {
            keyPressed[UP] = 1;
        }
        if (key == GLFW_KEY_A) {
            keyPressed[LEFT] = 1;
        }
        if (key == GLFW_KEY_S) {
            keyPressed[DOWN] = 1;
        }
        if (key == GLFW_KEY_D) {
            keyPressed[RIGHT] = 1;
        }
    }

    if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_W) {
            keyPressed[UP] = 0;
        }
        if (key == GLFW_KEY_A) {
            keyPressed[LEFT] = 0;
        }
        if (key == GLFW_KEY_S) {
            keyPressed[DOWN] = 0;
        }
        if (key == GLFW_KEY_D) {
            keyPressed[RIGHT] = 0;
        }
    }
}

void renderRect(float rect[4], float color[3]) {
    glBegin(GL_QUADS);
    glColor3f(color[0], color[1], color[2]);
    glVertex2f(rect[0] - rect[2] / 2, rect[1] + rect[3] / 2);
    glVertex2f(rect[0] - rect[2] / 2, rect[1] - rect[3] / 2);
    glVertex2f(rect[0] + rect[2] / 2, rect[1] - rect[3] / 2);
    glVertex2f(rect[0] + rect[2] / 2, rect[1] + rect[3] / 2);
    glEnd();
}

void renderCircle(float center[2], float radius, int nVertex) {
    for (int i = 0; i < nVertex; i++) {
        float angle1 = M_PI * 2.0 / nVertex * i, angle2 = M_PI * 2.0 / nVertex * (i + 1);
        float vertex[10] = {
            center[0], center[1],
            center[0] + radius * cos(angle1) / 2.0, center[1] + radius * sin(angle1) / 2.0,
            center[0] + radius * cos(angle1), center[1] + radius * sin(angle1),
            center[0] + radius * cos(angle2) / 2.0, center[1] + radius * sin(angle2) / 2.0,
            center[0] + radius * cos(angle2), center[1] + radius * sin(angle2),
        };
        glBegin(GL_TRIANGLES);
        glColor4f(0.0, 0.0, 1.0, 1.0);
        glVertex2f(vertex[0], vertex[1]);
        glVertex2f(vertex[2], vertex[3]);
        glVertex2f(vertex[6], vertex[7]);
        glEnd();
        glBegin(GL_QUADS);
        glColor4f(0.0, 0.0, 1.0, 1.0);
        glVertex2f(vertex[2], vertex[3]);
        glColor4f(0.0, 1.0, 1.0, 0.5);
        glVertex2f(vertex[4], vertex[5]);
        glColor4f(0.0, 1.0, 1.0, 0.5);
        glVertex2f(vertex[8], vertex[9]);
        glColor4f(0.0, 0.0, 1.0, 1.0);
        glVertex2f(vertex[6], vertex[7]);
        glEnd();
    }
}
