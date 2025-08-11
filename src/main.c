#include "MiniGL.h"
#include "RenderGlobals.h"
#include "drawing.h"

int main() {
  printf("Making Window...");
  MGL_makeWindow(800, 600, "Lol how did i do this");

  printf("Setting Line Width");
  MGL_lineWidth(2.5);

  printf("Entering Window Loop");

  int x = 0;

  while (!MGL_windowShouldClose()) {
    printf("Beginning Drawing...\n");
    MGL_beginDrawing();

    printf("Clearing Background...\n");
    MGL_clearBackground(255, 255, 255);

    // printf("Drawing Rectangle...\n");
    // MGL_drawRectangleLegacy(60, 60, 100.0f, 100.0f, 255 / 2, 255, 0);

    // printf("Drawing Rectangle...\n");
    // MGL_drawRectangleLegacy(10, 10, 100.0f, 100.0f, 255, 0, 0);

    // printf("Drawing Circle...\n");
    // MGL_drawCircleLegacy(10, 10, 100.0f, 255, 255, 0, Center);

    // printf("Drawing Circle...\n");
    // MGL_drawCircleLegacy(10, 10, 50.0f, 2, 255, 0, TopLeft);

    // printf("Drawing Line...\n");
    // MGL_drawLineLegacy(0, 0, mgl_screenWidth, mgl_screenHeight, 255, 255,
    // 255);

    // printf("Drawing Line...\n");
    // MGL_drawLineLegacy(200, 50, 2, 680, 255, 0, 255);

    // MGL_stroke(255, 255, 255, 255);
    // MGL_fill(0, 0, 255, 255);
    // MGL_translate(mgl_screenWidth / 2, mgl_screenHeight / 2);
    // MGL_drawRectangle(0, 0, 300, 300);

    if (x > 30) {
      MGL_pop();
    } else {
      MGL_translate(x, x);
      MGL_push();
    }

    x++;

    MGL_drawRectangle(0, 0, 20, 20);

    printf("Ending Drawing...\n");
    MGL_endDrawing();
  }

  printf("Closing Window...\n");
  MGL_closeWindow();

  return 0;
}
