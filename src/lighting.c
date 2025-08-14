#include "lighting.h"

void initializePointLightVBO();
void enableLight(int a) { mgl_lightEnabled = a; }
void drawLightObjects() {
  if (mgl_lightEnabled == 1) {
    enableLight(0);
    MGL_use(mgl_lightObjectShaderID);
    if (is2D == 1) {
      MGL_activate3D();
      MGL_drawSphereLegacy(light.position[0], light.position[1],
                           light.position[2], light.dimensions[0],
                           light.lightColor[0], light.lightColor[1],
                           light.lightColor[2]);
      MGL_activate2D();
    } else {
      MGL_drawSphereLegacy(light.position[0], light.position[1],
                           light.position[2], light.dimensions[0],
                           light.lightColor[0], light.lightColor[1],
                           light.lightColor[2]);
    }
    enableLight(1);
    MGL_use(mgl_objectShaderID);
  } else {
    if (is2D == 1) {
      MGL_activate3D();
      MGL_drawSphereLegacy(light.position[0], light.position[1],
                           light.position[2], light.dimensions[0],
                           light.lightColor[0], light.lightColor[1],
                           light.lightColor[2]);
      MGL_activate2D();
    } else {
      MGL_drawSphereLegacy(light.position[0], light.position[1],
                           light.position[2], light.dimensions[0],
                           light.lightColor[0], light.lightColor[1],
                           light.lightColor[2]);
    }
  }
}
void setPointLight();
