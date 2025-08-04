#include <iostream>

#include "MiniGL.hpp"

int main() {
  std::cout << "Making Window..." << std::endl;
  MGL_makeWindow(800, 600, "Lol how did i do this");

  MGL_lineWidth(2.5);

  while (!MGL_windowShouldClose()) {
    // std::cout << "Beginning Drawing..." << std::endl;
    MGL_beginDrawing();

    // std::cout << "Clearing Background..." << std::endl;
    MGL_clearBackground(0, 0, 0);

    // std::cout << "Drawing Rectangle..." << std::endl;
    MGL_drawRectangle(60, 60, 100.0f, 100.0f, 255 / 2, 255, 0);
    MGL_drawRectangle(10, 10, 100.0f, 100.0f, 255, 0, 0);

    MGL_drawCircle(10, 10, 100.0f, 255, 255, 0, Anchor::Center);
    MGL_drawCircle(10, 10, 50.0f, 2, 255, 0, Anchor::TopLeft);

    MGL_drawLine(0, 0, mgl_screenWidth, mgl_screenHeight, 255, 255, 255);
    MGL_drawLine(200, 50, 2, 680, 255, 0, 255);

    // std::cout << "Ending Drawing..." << std::endl;
    MGL_endDrawing();
  }

  std::cout << "Closing Window..." << std::endl;
  MGL_closeWindow();

  return 0;
}
