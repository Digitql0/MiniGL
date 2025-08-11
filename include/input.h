#ifndef INPUT_HPP
#define INPUT_HPP

#include "RenderGlobals.h"

int MGL_isKeyPressed(int key);
int MGL_isKeyReleased(int key);
int MGL_isKeyHeld(int key);
void MGL_processInput(GLFWwindow* window);

#endif
