#include <iostream>
#include "Renderer.h"
#include "glut.h"

int win;
int width;
int height;
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

    glutInitWindowSize(500, 500);

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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, width, height);

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
        renderer->Keypressed(key);
}

void reshape(int w, int h)
{
    width = w;
    height = h;
}