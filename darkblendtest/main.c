#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <png.h>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

png_byte* readImage(char*);
void loadTexture(GLuint, png_byte*, int, int);
void renderRect(float[], float[]);
void renderTexture(GLuint, float[]);
void renderLightCircle(float[], float, int);
void renderStencilCircle(float[], float, int);
void keyHandle(GLFWwindow*, int, int, int, int);
void move();

float pos[2] = {0, 0};
int keyPressed[4] = {0, 0, 0, 0};

int main() {
    GLFWmonitor* monitor;
    GLFWwindow* window;
    GLuint texture, texturePlayer, textureGhost, textureObject;
    GLubyte* pixel = NULL;
    png_byte *imagePlayer = NULL, *imageGhost = NULL, *imageObject = NULL;
    imagePlayer = readImage("player.png");
    imageObject = readImage("object.png");
    imageGhost = readImage("ghost.png");

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
    printf("%f %f", xscale, yscale);
    int width = 640, height = 640;
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
    glViewport(0, 0, width * xscale, height * yscale);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glGenTextures(1, &texturePlayer);
    glGenTextures(1, &textureGhost);
    glGenTextures(1, &textureObject);
    loadTexture(texturePlayer, imagePlayer, 80, 80);
    loadTexture(textureGhost, imageGhost, 80, 80);
    loadTexture(textureObject, imageObject, 80, 80);

    while (!glfwWindowShouldClose(window)) {
        move();
        glClearColor(0.0, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        renderTexture(textureGhost, (float[]){0.5, -0.5, 0.2, 0.2});
        renderTexture(textureGhost, (float[]){-0.5, 0.5, 0.2, 0.2});
        glDisable(GL_TEXTURE_2D);
        renderLightCircle(pos, 0.5, 40);
        renderLightCircle((float[]){0.5, 0.0}, 0.2, 40);
        renderLightCircle((float[]){-0.5, 0.0}, 0.2, 40);
        renderLightCircle((float[]){0.0, 0.5}, 0.2, 40);
        renderLightCircle((float[]){0.0, -0.5}, 0.2, 40);
        glBindTexture(GL_TEXTURE_2D, texture);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, width, height, 0);
        
        glClearColor(0.7, 0.7, 0.7, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);        
        glEnable(GL_TEXTURE_2D);
        renderTexture(textureObject, (float[]){-0.5, -0.5, 0.2, 0.2});
        renderTexture(textureObject, (float[]){0.5, 0.5, 0.2, 0.2});
        renderTexture(texturePlayer, (float[]){pos[0], pos[1], 0.2, 0.2});

        glBlendFunc(GL_ZERO, GL_SRC_COLOR);
        glBindTexture(GL_TEXTURE_2D, texture);
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
    free(imagePlayer);
    free(imageObject);
    free(imageGhost);
    free(pixel);
    return 0;
}

png_byte* readImage(char* path) {
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int iwidth, iheight;
    unsigned int imageSize;

    FILE * file = fopen(path, "rb");
    if (!file) { return 0; }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, file);
    png_read_info(png_ptr, info_ptr);
    int width = png_get_image_width(png_ptr, info_ptr);
    int height = png_get_image_height(png_ptr, info_ptr);
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    size_t row_bytes = png_get_rowbytes(png_ptr, info_ptr);
    png_byte* data = (png_byte*)malloc(row_bytes * height);
    for (int y = 0; y < height; y++) {
        png_read_row(png_ptr, &(data[y * row_bytes]), NULL);
    }
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    fclose(file);
    return data;
}

void loadTexture(GLuint texture, png_byte* data, int width, int height) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
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

void renderTexture(GLuint texture, float rect[4]) {
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(rect[0] - rect[2] / 2, rect[1] - rect[3] / 2);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(rect[0] + rect[2] / 2, rect[1] - rect[3] / 2);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(rect[0] + rect[2] / 2, rect[1] + rect[3] / 2);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(rect[0] - rect[2] / 2, rect[1] + rect[3] / 2);
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
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glVertex2f(vertex[0], vertex[1]);
        glVertex2f(vertex[2], vertex[3]);
        glVertex2f(vertex[6], vertex[7]);
        glEnd();
        glBegin(GL_QUADS);
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glVertex2f(vertex[2], vertex[3]);
        glColor4f(0.0, 0.0, 0.0, 1.0);
        glVertex2f(vertex[4], vertex[5]);
        glColor4f(0.0, 0.0, 0.0, 1.0);
        glVertex2f(vertex[8], vertex[9]);
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glVertex2f(vertex[6], vertex[7]);
        glEnd();
    }
}
