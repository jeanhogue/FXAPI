#ifndef __RenderingUtils_H__
#define __RenderingUtils_H__

#include <string>

void DrawLine(float x1, float y1, float x2, float y2);
void DrawLineStipple(float x1, float y1, float x2, float y2);
void DrawArrow(float x1, float y1, float x2, float y2, float sizeX, float sizeY);
void DrawRectangle(float x1, float y1, float x2, float y2);
void DrawRectangleBorder(float x1, float y1, float x2, float y2);
void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
void DrawCircle(float x, float y, float radiusX, float radiusY, int step = 30);
void DrawCircleBorder(float x, float y, float radiusX, float radiusY, int step = 30);

#endif