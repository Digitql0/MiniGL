#ifndef DRAWING_STYLE_H
#define DRAWING_STYLE_H

#include <string.h>

#include "RenderGlobals.h"

void MGL_stroke(int r, int g, int b, int a);
void MGL_fill(int r, int g, int b, int a);
void MGL_strokeWeight(unsigned int value);
void MGL_translate(float x, float y, float z);
void MGL_push();
void MGL_pop();
void MGL_lineWidth(float width);

#endif
