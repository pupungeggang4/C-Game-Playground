#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdio.h>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

void renderRect(float[], float[]);
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
    printf("OpenGL Version: %s", glGetString(GL_VERSION));

    while (!glfwWindowShouldClose(window)) {
        move();
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_BLEND);
        renderRect((float[]){0.5, -0.5, 0.2, 0.2}, (float[]){0.0, 1.0, 0.0});
        renderRect((float[]){-0.5, -0.5, 0.2, 0.2}, (float[]){1.0, 1.0, 0.0});
        renderRect((float[]){0.5, 0.5, 0.2, 0.2}, (float[]){1.0, 0.0, 1.0});
        renderRect((float[]){-0.5, 0.5, 0.2, 0.2}, (float[]){0.0, 1.0, 1.0});
        renderRect((float[]){pos[0], pos[1], 0.2, 0.2}, (float[]){0.0, 0.0, 0.0});

        glEnable(GL_BLEND);
        glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
        glColor4f(0.0, 0.0, 0.0, 1.0);
        glVertex2f(-1.0, -1.0);
        glVertex2f(1.0, -1.0);
        glVertex2f(1.0, 1.0);
        glVertex2f(-1.0, 1.0);
        glColor4f(0.0, 1.0, 0.0, 1.0);
        glVertex2f(pos[0] - 0.3, pos[1] - 0.3);
        glVertex2f(pos[0] + 0.3, pos[1] - 0.3);
        glVertex2f(pos[0] + 0.3, pos[1] + 0.3);
        glVertex2f(pos[0] - 0.3, pos[1] + 0.3);
        glEnd();
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
