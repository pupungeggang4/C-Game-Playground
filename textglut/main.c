#include "ft2build.h"
#include FT_FREETYPE_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

FT_Library ft;
FT_Face font;

int main() {
    FT_Init_FreeType(&ft);
    FT_New_Face(ft, "font/neodgm.ttf", 0, &font);
    FT_Set_Pixel_Sizes(font, 0, 48);

    GLFWwindow* window;
    GLFWmonitor* monitor;
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
    int width = 640, height = 640;
    #ifndef __APPLE__
    window = glfwCreateWindow(width * xscale, height * yscale, "Text render example", NULL, NULL);
    #else
    window = glfwCreateWindow(width, height, "Text render example", NULL, NULL);
    #endif
    if (!window) {
        printf("Failed to create window.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glViewport(0, 0, width * xscale, height * yscale);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, texture);
    FT_Load_Char(font, 'A', FT_LOAD_RENDER);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        FT_Load_Char(font, 'A', FT_LOAD_RENDER);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ONE, font->glyph->bitmap.width, font->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, font->glyph->bitmap.buffer);
        glBegin(GL_QUADS);
        glColor4f(1.0, 1.0, 1.0, 1.0);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(-0.1, -0.1);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(0.1, -0.1);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(0.1, 0.1);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(-0.1, 0.1);
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
