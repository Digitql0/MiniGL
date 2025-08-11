#include "MiniGL.h"

int main() {
  printf("Making Window...");
  MGL_makeWindow(800, 600, "Lol how did i do this");

  printf("Setting Line Width");
  MGL_lineWidth(2.5);

  printf("Entering Window Loop");

  while (!MGL_windowShouldClose()) {
    printf("Beginning Drawing...\n");
    MGL_beginDrawing();

    printf("Clearing Background...\n");
    MGL_clearBackground(0, 0, 0);

    printf("Drawing Rectangle...\n");
    MGL_drawRectangle(60, 60, 100.0f, 100.0f, 255 / 2, 255, 0);

    printf("Drawing Rectangle...\n");
    MGL_drawRectangle(10, 10, 100.0f, 100.0f, 255, 0, 0);

    printf("Drawing Circle...\n");
    MGL_drawCircle(10, 10, 100.0f, 255, 255, 0, Center);

    printf("Drawing Circle...\n");
    MGL_drawCircle(10, 10, 50.0f, 2, 255, 0, TopLeft);

    printf("Drawing Line...\n");
    MGL_drawLine(0, 0, mgl_screenWidth, mgl_screenHeight, 255, 255, 255);

    printf("Drawing Line...\n");
    MGL_drawLine(200, 50, 2, 680, 255, 0, 255);

    printf("Ending Drawing...\n");
    MGL_endDrawing();
  }

  printf("Closing Window...\n");
  MGL_closeWindow();

  return 0;
}
