#include <iostream>

#include "MiniGL.hpp"

int main() {
  std::cout << "Making Window..." << std::endl;
  MakeWindow(800, 600, "Lol how did i do this");

  while (!WindowShouldClose()) {
    // std::cout << "Beginning Drawing..." << std::endl;
    BeginDrawing();

    // std::cout << "Clearing Background..." << std::endl;
    ClearBackground(0, 0, 0);

    // std::cout << "Drawing Rectangle..." << std::endl;
    drawRectangle(60, 60, 100.0f, 100.0f, 255 / 2, 255, 0);
    drawRectangle(10, 10, 100.0f, 100.0f, 255, 0, 0);

    drawCircle(10, 10, 100.0f, 255, 255, 0, Anchor::Center);
    drawCircle(10, 10, 50.0f, 2, 255, 0, Anchor::TopLeft);

    // std::cout << "Ending Drawing..." << std::endl;
    EndDrawing();
  }

  std::cout << "Closing Window..." << std::endl;
  CloseWindow();

  return 0;
}
