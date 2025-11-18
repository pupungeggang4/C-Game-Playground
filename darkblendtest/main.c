#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

void renderRect(float[], float[]);
void renderLightCircle(float[], float, int);
void renderStencilCircle(float[], float, int);
void keyHandle(GLFWwindow*, int, int, int, int);
void move();

float pos[2] = {0, 0};
int keyPressed[4] = {0, 0, 0, 0};

int main() {
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int iwidth, iheight;
    unsigned int imageSize;
    unsigned char * data;

    FILE * file = fopen("a.bmp", "rb");
    if (!file) { /* Error handling */ return 0; }
    if (fread(header, 1, 54, file) != 54) { /* Error handling */ return 0; }
    if (header[0] != 'B' || header[1] != 'M') { /* Error handling */ return 0; }
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    iwidth      = *(int*)&(header[0x12]);
    iheight     = *(int*)&(header[0x16]);
    printf("%d, %d, %d, %d\n", dataPos, imageSize, iwidth, iheight);
    fseek(file, dataPos, SEEK_SET);
    data = malloc(imageSize);
    fread(data, 1, imageSize, file);
    fclose(file);

    GLFWmonitor* monitor;
    GLFWwindow* window;
    GLuint texture;
    GLubyte* pixel = NULL;
    if (!glfwInit()) {
        printf("Failed to initialize GLFW.\n");
        return -1;
    }

    monitor = glfwGetPrimaryMonitor();
    if (!monitor) {
        printf("No monitor.\n");
        glfwTerminate();
        return -1;
    }
    float xscale, yscale;  
    glfwGetMonitorContentScale(monitor, &xscale, &yscale);
    //glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    int width = 800 * xscale, height = 800 * yscale;
    window = glfwCreateWindow(width, height, "Dark Blending Test", NULL, NULL);
    pixel = (GLubyte*)malloc(width * height * 4);
    if (!window) {
        printf("Failed to create GLFW window.\n");
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, keyHandle);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    while (!glfwWindowShouldClose(window)) {
        move();
        glClearColor(0.0, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        renderRect((float[]){0.0, 0.7, 0.2, 0.2}, (float[]){0.0, 0.0, 1.0, 1.0});
        renderLightCircle(pos, 0.5, 40);
        renderLightCircle((float[]){0.5, 0.0}, 0.2, 40);
        renderLightCircle((float[]){-0.5, 0.0}, 0.2, 40);
        renderLightCircle((float[]){0.0, 0.5}, 0.2, 40);
        renderLightCircle((float[]){0.0, -0.5}, 0.2, 40);
        glBindTexture(GL_TEXTURE_2D, texture);
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
        
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        renderRect((float[]){0.5, 0.5, 0.2, 0.2}, (float[]){1.0, 1.0, 0.0, 1.0});
        renderRect((float[]){0.5, -0.5, 0.2, 0.2}, (float[]){0.0, 1.0, 1.0, 1.0});
        renderRect((float[]){-0.5, -0.5, 0.2, 0.2}, (float[]){1.0, 0.0, 1.0, 1.0});
        renderRect((float[]){-0.5, 0.5, 0.2, 0.2}, (float[]){0.0, 1.0, 0.0, 1.0});
        renderRect((float[]){pos[0], pos[1], 0.2, 0.2}, (float[]){0.0, 0.0, 0.0, 1.0});
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 80, 80, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
        glBegin(GL_QUADS);
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(-0.1, -0.1);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(0.1, -0.1);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(0.1, 0.1);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(-0.1, 0.1);
        glEnd();

        glBlendFunc(GL_ZERO, GL_SRC_COLOR);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(-1.0, -1.0);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(1.0, -1.0);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(1.0, 1.0);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(-1.0, 1.0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    free(pixel);
    free(data);
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

void renderRect(float rect[4], float color[4]) {
    glBegin(GL_QUADS);
    glColor4f(color[0], color[1], color[2], color[3]);
    glVertex2f(rect[0] - rect[2] / 2, rect[1] + rect[3] / 2);
    glVertex2f(rect[0] - rect[2] / 2, rect[1] - rect[3] / 2);
    glVertex2f(rect[0] + rect[2] / 2, rect[1] - rect[3] / 2);
    glVertex2f(rect[0] + rect[2] / 2, rect[1] + rect[3] / 2);
    glEnd();
}

void renderStencilCircle(float center[2], float radius, int nVertex) {
    for (int i = 0; i < nVertex; i++) {
        float angle1 = M_PI * 2.0 / nVertex * i, angle2 = M_PI * 2.0 / nVertex * (i + 1);
        float vertex[10] = {
            center[0], center[1],
            center[0] + radius * cos(angle1), center[1] + radius * sin(angle1),
            center[0] + radius * cos(angle2), center[1] + radius * sin(angle2)
        };
        glBegin(GL_TRIANGLES);
        glVertex2f(vertex[0], vertex[1]);
        glVertex2f(vertex[2], vertex[3]);
        glVertex2f(vertex[4], vertex[5]);
        glEnd();
    }
}

void renderLightCircle(float center[2], float radius, int nVertex) {
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
        glColor4f(0.8, 0.8, 0.8, 1.0);
        glVertex2f(vertex[0], vertex[1]);
        glVertex2f(vertex[2], vertex[3]);
        glVertex2f(vertex[6], vertex[7]);
        glEnd();
        glBegin(GL_QUADS);
        glColor4f(0.8, 0.8, 0.8, 1.0);
        glVertex2f(vertex[2], vertex[3]);
        glColor4f(0.0, 0.0, 0.0, 1.0);
        glVertex2f(vertex[4], vertex[5]);
        glColor4f(0.0, 0.0, 0.0, 1.0);
        glVertex2f(vertex[8], vertex[9]);
        glColor4f(0.8, 0.8, 0.8, 1.0);
        glVertex2f(vertex[6], vertex[7]);
        glEnd();
    }
}
