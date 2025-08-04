#ifndef INPUT_HPP
#define INPUT_HPP

#include "RenderGlobals.hpp"
#include <GLFW/glfw3.h>

bool isKeyPressed(int key);
bool isKeyReleased(int key);
bool isKeyHeld(int key);
void processInput(GLFWwindow* window);

#endif
