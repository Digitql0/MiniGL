#include "input.h"

int MGL_isKeyPressed(int key) {
  return glfwGetKey(mgl_frame, key) == GLFW_PRESS;
}
int MGL_isKeyReleased(int key) {
  return glfwGetKey(mgl_frame, key) == GLFW_RELEASE;
}
int MGL_isKeyHeld(int key) { return glfwGetKey(mgl_frame, key) == GLFW_REPEAT; }
void MGL_setInputFunction(void (*func)(void)) { MGL_processInput = func; }
