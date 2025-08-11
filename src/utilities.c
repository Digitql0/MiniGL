#include "utilities.h"

vec2* MGL_getTranslation() {
  if (mgl_translationHistorySize != 0) {
    return (vec2*)mgl_translationHistory[mgl_translationHistorySize - 1];
  } else {
    return NULL;
  }
}
