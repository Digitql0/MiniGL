#ifndef INPUT_HPP
#define INPUT_HPP

#include "RenderGlobals.hpp"
#include <GLFW/glfw3.h>

bool MGL_isKeyPressed(int key);
bool MGL_isKeyReleased(int key);
bool MGL_isKeyHeld(int key);
void MGL_processInput(GLFWwindow* window);

#endif
