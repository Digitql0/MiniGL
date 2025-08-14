#include "drawing_style.h"

void MGL_stroke(int r, int g, int b, int a) {
  mgl_strokeColor[0] = r;
  mgl_strokeColor[1] = g;
  mgl_strokeColor[2] = b;
  mgl_strokeColor[3] = a;
}
void MGL_fill(int r, int g, int b, int a) {
  mgl_fillColor[0] = r;
  mgl_fillColor[1] = g;
  mgl_fillColor[2] = b;
  mgl_fillColor[3] = a;
}
void MGL_strokeWeight(unsigned int value) { mgl_strokeWidth = value; }
void MGL_translate(float x, float y, float z) {
  mgl_currentTranslate[0] += x;
  mgl_currentTranslate[1] += y;
  mgl_currentTranslate[2] += z;
}
void MGL_push() {
  mgl_translationHistorySize++;
  vec3* temp_ptr = realloc(mgl_translationHistory,
                           sizeof(vec3) * mgl_translationHistorySize);

  if (temp_ptr == NULL) {
    printf("Translation Allocation Error");
    return;
  }

  mgl_translationHistory = temp_ptr;

  memcpy(&mgl_translationHistory[mgl_translationHistorySize - 1],
         mgl_currentTranslate, sizeof(vec3));
}
void MGL_pop() {
  if (mgl_translationHistorySize <= 0) {
    return;
  }
  mgl_translationHistorySize--;

  mgl_currentTranslate[0] =
      mgl_translationHistory[mgl_translationHistorySize - 1][0];
  mgl_currentTranslate[1] =
      mgl_translationHistory[mgl_translationHistorySize - 1][1];
  mgl_currentTranslate[2] =
      mgl_translationHistory[mgl_translationHistorySize - 1][2];
}
void MGL_lineWidth(float width) { glLineWidth(width); }
