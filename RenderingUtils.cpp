#define _USE_MATH_DEFINES
#include <cmath>
#include "RenderingUtils.h"

#pragma warning(disable:4505)     // remove local functions warning
#include "glut.h"


void DrawLine(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

void DrawLineStipple(float x1, float y1, float x2, float y2)
{
    glEnable(GL_LINE_STIPPLE);
    glPushAttrib(GL_LINE_BIT);
    glLineStipple(3, 0xAAAA);
        DrawLine(x1, y1, x2, y2);
    glPopAttrib();
    glDisable(GL_LINE_STIPPLE);
}

void DrawArrow(float x1, float y1, float x2, float y2, float sizeX, float sizeY)
{
    // main line
    DrawLine(x1, y1, x2, y2);

    // triangle at the end of the line
    float angle = atan2((double)(y2 - y1), (double)(x2 - x1)) * 180 / M_PI - 90;
    glPushMatrix();
    glTranslatef(x2, y2, 0);
    glRotatef(angle, 0, 0, 1);
    DrawTriangle(-sizeX / 2, -sizeY, sizeX / 2, -sizeY, 0, 0);
    glPopMatrix();
}

void DrawRectangle(float x1, float y1, float x2, float y2)
{
    glBegin(GL_QUADS);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
    glEnd();
}

void DrawRectangleBorder(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINE_STRIP);
        glVertex2f(x1, y1);
        glVertex2f(x2, y1);
        glVertex2f(x2, y2);
        glVertex2f(x1, y2);
        glVertex2f(x1, y1);
    glEnd();
}

void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();
}

void DrawCircle(float x, float y, float radiusX, float radiusY, int step)
{
    glBegin(GL_POLYGON);
        for (int i = 0; i < step; ++ i)
        {
            float angle = (float)i / step * 2 * M_PI;
            float xi = radiusX * cos(angle) - 0 * sin(angle);
            float yi = 0 * cos(angle) + radiusY * sin(angle);
            glVertex2f(x + xi, y + yi);
        }
    glEnd();
}

void DrawCircleBorder(float x, float y, float radiusX, float radiusY, int step)
{
    glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= step; ++ i)
        {
            float angle = (float)i / step * 2 * M_PI;
            float xi = radiusX * cos(angle);
            float yi = radiusY * sin(angle);
            glVertex2f(x + xi, y + yi);
        }
    glEnd();
}