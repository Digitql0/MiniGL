#include "MiniGL.h"

int x = 0;
int y = 1;
Camera* cam;
vec2 oldMouse = {0, 0};
vec2 newMouse = {0, 0};
vec2 offsetMouse = {0, 0};

void input() {
  x += y;
  newMouse[0] = mgl_mousex;
  newMouse[1] = mgl_mousey;

  glm_vec2_sub(newMouse, oldMouse, offsetMouse);

  if (MGL_isKeyPressed(GLFW_KEY_W)) {
    MGLC_updatePositionLocal(0, 0, 1, cam);  // Forward
  }
  if (MGL_isKeyPressed(GLFW_KEY_S)) {
    MGLC_updatePositionLocal(0, 0, -1, cam);  // Backward
  }
  if (MGL_isKeyPressed(GLFW_KEY_A)) {
    MGLC_updatePositionLocal(-1, 0, 0, cam);  // Left
  }
  if (MGL_isKeyPressed(GLFW_KEY_D)) {
    MGLC_updatePositionLocal(1, 0, 0, cam);  // Right
  }
  if (MGL_isKeyPressed(GLFW_KEY_SPACE)) {
    MGLC_updatePositionLocal(0, -1, 0, cam);  // Up
  }
  if (MGL_isKeyPressed(GLFW_KEY_LEFT_SHIFT) ||
      MGL_isKeyPressed(GLFW_KEY_RIGHT_SHIFT)) {
    MGLC_updatePositionLocal(0, 1, 0, cam);  // Down
  }

  MGLC_updateRotationLocal(-offsetMouse[1], -offsetMouse[0], 0, cam);
  printf("%d\n", x);
  // if (x > 89 || x < -89) {
  //   y *= -1;
  // }
  // MGLC_updateRotationLocal(offsetMouse[1], offsetMouse[0], 0.0f, cam);

  oldMouse[0] = newMouse[0];
  oldMouse[1] = newMouse[1];
}

int main() {
  MGL_makeWindow(1000, 1000, "Lol how did i do this");
  cam = MGLC_getCamera();
  MGLC_setPerspective(Perspective, cam);
  MGLC_setNearPlane(0.1f, cam);
  MGLC_setFarPlane(1000.0f, cam);
  float camPos[] = {0.0f, 0.0f, 100.0f};
  MGLC_setPosition(camPos, cam);
  // MGLC_setZoom(1000, cam);
  oldMouse[0] = mgl_mousex;
  oldMouse[1] = mgl_mousey;
  MGLC_setAspectRatio(mgl_screenWidth / mgl_screenHeight, cam);

  MGL_setInputFunction(input);
  MGL_lineWidth(2.5);

  MGLC_hideMouse();

  enableLight(1);

  while (!MGL_windowShouldClose()) {
    MGL_beginDrawing();
    glEnable(GL_DEPTH_TEST);
    MGL_clearBackground(0, 0, 0);

    MGL_activate3D();
    glDisable(GL_CULL_FACE);
    MGL_fill(255, 100, 100, 255);
    
    // Debug: Print camera info
    printf("Camera pos: %f, %f, %f\n", cam->position[0], cam->position[1], cam->position[2]);
    printf("Camera rot: %f, %f, %f\n", cam->rotation[0], cam->rotation[1], cam->rotation[2]);
    printf("Near/Far: %f, %f\n", cam->nearPlane, cam->farPlane);
    printf("FOV: %f\n", cam->fov);
    printf("Projection matrix: %f, %f, %f, %f\n", cam->projection[0][0], cam->projection[0][1], cam->projection[0][2], cam->projection[0][3]);
    printf("View matrix: %f, %f, %f, %f\n", cam->view[0][0], cam->view[0][1], cam->view[0][2], cam->view[0][3]);
    
    MGL_drawCube(0, 0, 0, 50, 50, 50);
    glEnable(GL_CULL_FACE);
    // drawLightObjects();

    MGL_endDrawing();
  }

  MGL_closeWindow();

  return 0;
}

// printf("Position: %f, %f, %f\n", cam->position[0], cam->position[1],
//        cam->position[2]);
// printf("Rotation: %f, %f, %f\n", cam->rotation[0], cam->rotation[1],
//        cam->rotation[2]);
// printf("Zoom: %f\n", cam->zoom);
