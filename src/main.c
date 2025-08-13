#include "MiniGL.h"
#include "RenderGlobals.h"
#include "camera.h"
#include "drawing.h"
#include "input.h"

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
  cam = MGLC_getCamera();
  MGL_setInputFunction(input);

  printf("Making Window...");
  MGL_makeWindow(500, 500, "Lol how did i do this");

  MGLC_hideMouse();

  printf("Setting Line Width");
  MGL_lineWidth(2.5);

  printf("Entering Window Loop");

  // MGLC_setZoom(1000, cam);
  oldMouse[0] = mgl_mousex;
  oldMouse[1] = mgl_mousey;

  MGLC_setPerspective(Perspective, cam);
  MGLC_updatePositionLocal(0, 0, -30, cam);

  while (!MGL_windowShouldClose()) {
    MGL_beginDrawing();
    printf("Vertex floats: %zu\n", mgl_cubeVertexCount);
    printf("Index count: %zu\n", mgl_cubeIndexCount);

    MGL_clearBackground(0, 0, 0);

    MGL_stroke(0, 0, 255, 255);
    MGL_strokeWeight(5);
    MGL_fill(0, 255, 0, 255);

    // MGL_activate2D();
    // MGL_drawRectangleLegacy(60, 60, 100.0f, 100.0f, 255 / 2, 255, 0);
    // MGL_drawRectangleLegacy(10, 10, 100.0f, 100.0f, 255, 0, 0);
    // MGL_drawCircleLegacy(10, 10, 100.0f, 255, 255, 0, Center);
    // MGL_drawCircleLegacy(10, 10, 50.0f, 2, 255, 0, TopLeft);
    // MGL_drawLineLegacy(0, 0, mgl_screenWidth, mgl_screenHeight, 255, 255,
    // 255); MGL_drawLineLegacy(200, 50, 2, 680, 255, 0, 255);
    // MGL_lineWidth(20);
    // MGL_drawLineLegacy(0, 0, mgl_screenWidth, mgl_screenHeight, 255, 255,
    // 255); MGL_drawCircle(0, 0, 20);

    MGL_activate2D();
    MGL_drawRectangle(0, 0, 50, 50);
    MGL_drawCircle(100, 0, 50);
    MGL_drawLine(200, 0, 250, 0);
    MGL_drawDot(300, 0);

    MGL_activate3D();
    MGL_drawCube(0, 100, 0, 50, 50, 50);
    MGL_drawSphere(100, 100, 0, 50);
    MGL_drawRay(200, 100, 0, 250, 100, 0);
    MGL_drawPoint(300, 100, 0);

    printf("Position: %f, %f, %f\n", cam->position[0], cam->position[1],
           cam->position[2]);
    printf("Rotation: %f, %f, %f\n", cam->rotation[0], cam->rotation[1],
           cam->rotation[2]);
    printf("Zoom: %f\n", cam->zoom);

    MGL_endDrawing();
  }

  printf("Closing Window...\n");
  MGL_closeWindow();

  return 0;
}
