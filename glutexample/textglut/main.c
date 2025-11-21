#include "ft2build.h"
#include FT_FREETYPE_H

#include <GL/gl.h>
#include <GL/glut.h>
//#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

FT_Library ft;
FT_Face font;
GLuint texture;

void render();
void handleKey(unsigned char, int, int);

int main(int argc, char** argv) {
    FT_Init_FreeType(&ft);
    FT_New_Face(ft, "font/neodgm.ttf", 0, &font);
    FT_Set_Pixel_Sizes(font, 0, 48);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    int width = 640, height = 640;
    int screen_width = glutGet(GLUT_SCREEN_WIDTH);
    int screen_height = glutGet(GLUT_SCREEN_HEIGHT);
    int xPos = (screen_width - width) / 2;
    int yPos = (screen_height - height) / 2;

    glutInitWindowSize(width, height);
    glutInitWindowPosition(xPos, yPos);
    glutCreateWindow("FreeGLUT Text Test");
    glutKeyboardFunc(handleKey);
    glutDisplayFunc(render);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glViewport(0, 0, width, height);
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

    glutMainLoop();
    return 0;
}

void render() {
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
    glutSwapBuffers();
}

void handleKey(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
}
