#include "drawing_render.h"

void MGL_beginDrawing() {
  if (MGL_processInput != NULL) {
    MGL_processInput();  // Compute Input
  }

  if (mgl_lightEnabled == 1) {
    MGL_use(mgl_objectShaderID);
  } else {
    MGL_use(mgl_lightObjectShaderID);
  }

  if (mgl_lightEnabled == 1) {
    MGL_setVec3(mgl_objectShaderID, "lightColor", &light.lightColor);
    MGL_setVec3(mgl_objectShaderID, "lightPos", &light.position);
    printf("%f, %f, %f\n", light.position[0], light.position[1],
           light.position[2]);
  }

  mgl_currentTranslate[0] = 0;
  mgl_currentTranslate[1] = 0;
  mgl_currentTranslate[2] = 0;
}

void MGL_activate2D() {
  glDisable(GL_DEPTH_TEST);
  is2D = 1;
}

void MGL_activate3D() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  is2D = 0;
}

void MGL_clearBackground(int r, int g, int b) {
  glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MGL_endDrawing() {
  Camera* cam = MGLC_getCamera();
  MGLC_updateMatrices(cam);

  MGL_use(mgl_objectShaderID);
  MGL_setMat4(mgl_objectShaderID, "projection", &cam->projection);
  MGL_setMat4(mgl_objectShaderID, "view", &cam->view);
  MGL_use(mgl_lightObjectShaderID);
  MGL_setMat4(mgl_lightObjectShaderID, "projection", &cam->projection);
  MGL_setMat4(mgl_lightObjectShaderID, "view", &cam->view);

  glfwSwapBuffers(mgl_frame);
  glfwPollEvents();
}
