#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float time = 0, a = 0, b = 0;

void render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(sin(time), 0.5f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-0.5f, -0.5f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.5f, -0.5f);
    glEnd();
    glutSwapBuffers();
}

void handleKey(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
}

void handleScene() {
    time += 0.01;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    int width = 800, height = 600;
    int screen_width = glutGet(GLUT_SCREEN_WIDTH);
    int screen_height = glutGet(GLUT_SCREEN_HEIGHT);
    int initial_x = (screen_width - width) / 2;
    int initial_y = (screen_height - height) / 2;

    glutInitWindowSize(width, height);
    glutInitWindowPosition(initial_x, initial_y);

    glutCreateWindow("FreeGLUT Test");
    glutDisplayFunc(render);
    glutKeyboardFunc(handleKey);
    glutIdleFunc(handleScene);

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    glutMainLoop();
    glViewport(0, 0, width, height);
    return 0;
}
