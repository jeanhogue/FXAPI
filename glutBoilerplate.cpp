#include <iostream>
#include "glut.h"
#include "Renderer.h"
#include "RenderingUtils.h"

int win;
int width;
int height;
float borderX = 60;
float borderY = 40;
Renderer *renderer;

void disp();
void keyb(unsigned char key, int x, int y);
void reshape(int w, int h);


void StartRendering(int argc, char **argv, Renderer *_renderer)
{
    renderer = _renderer; 

    // initialize glut
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

    glutInitWindowSize(800, 600);

    win = glutCreateWindow("FXAPI");

    glutDisplayFunc(disp);
    glutKeyboardFunc(keyb);
    glutReshapeFunc(reshape);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glutMainLoop();
}

void disp()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, width, height);

    float normBorderX = borderX / width;
    float normBorderY = borderY / height;

    renderer->RenderBorders(normBorderX, normBorderY);

    glViewport(width * normBorderX, height * normBorderY, width - 2 * (width * normBorderX), height - 2 * (height * normBorderY));

    renderer->Render();

    glFlush();
}

void keyb(unsigned char key, int x, int y)
{
    if (key == 'q')
    {
        glutDestroyWindow(win);
        exit(0);
    }
    else
        renderer->KeyPressed(key);
}

void reshape(int w, int h)
{
    width = w;
    height = h;
    renderer->SetDimensions(width, height);
}