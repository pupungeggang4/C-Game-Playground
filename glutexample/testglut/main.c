#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void render();
void handleKey(unsigned char, int, int);
void handleScene();
void timer(int);

float time = 0;
int frameCurrent = 0, framePrevious = 0, delta = 0;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    int width = 800, height = 600;
    int screen_width = glutGet(GLUT_SCREEN_WIDTH);
    int screen_height = glutGet(GLUT_SCREEN_HEIGHT);
    int xPos = (screen_width - width) / 2;
    int yPos = (screen_height - height) / 2;

    glutInitWindowSize(width, height);
    glutInitWindowPosition(xPos, yPos);

    glutCreateWindow("FreeGLUT Test");
    glutDisplayFunc(render);
    glutKeyboardFunc(handleKey);
    glutTimerFunc(16, handleScene, 1);

    glViewport(0, 0, width, height);
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    glutMainLoop();

    return 0;
}

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

void handleScene(int value) {
    frameCurrent = glutGet(GLUT_ELAPSED_TIME);
    int dt = frameCurrent - framePrevious;
    framePrevious = glutGet(GLUT_ELAPSED_TIME);
    time += 0.01;
    glutPostRedisplay();
    if (dt < 16) {
        delta = 16;
        glutTimerFunc(16 - dt, handleScene, 1);
    } else {
        delta = dt;
        glutTimerFunc(0, handleScene, 1);
    }
}
