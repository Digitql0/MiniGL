#include "utilities.h"

vec2* MGL_getTranslation() {
  if (mgl_translationHistorySize != 0) {
    return (vec2*)mgl_translationHistory[mgl_translationHistorySize - 1];
  } else {
    return NULL;
  }
}

void MGL_euler_to_quat(float pitch, float yaw, float roll, versor q) {
  float cy = cosf(yaw * 0.5f);
  float sy = sinf(yaw * 0.5f);
  float cp = cosf(pitch * 0.5f);
  float sp = sinf(pitch * 0.5f);
  float cr = cosf(roll * 0.5f);
  float sr = sinf(roll * 0.5f);

  q[0] = sr * cp * cy - cr * sp * sy;  // x
  q[1] = cr * sp * cy + sr * cp * sy;  // y
  q[2] = cr * cp * sy - sr * sp * cy;  // z
  q[3] = cr * cp * cy + sr * sp * sy;  // w
}
