#ifndef __COLORS_H__
#define __COLORS_H__

#include "glut.h"


class Color
{
public:
    Color() : r(1), g(1), b(1) {}
    Color(int _r, int _g, int _b) : r(_r / 255.0f), g(_g / 255.0f), b(_b / 255.0f) {}

    void SetColor(int _r, int _g, int _b) 
    {
        r = _r / 255.0f;
        g = _g / 255.0f;
        b = _b / 255.0f;
    }

    void SetOGLColor()
    {
        glColor3f(r, g, b);
    }

    float r, g, b;
};

#endif