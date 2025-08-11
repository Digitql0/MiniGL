#include "input.h"

int MGL_isKeyPressed(int key) {
  return glfwGetKey(mgl_frame, key) == GLFW_PRESS;
}

int MGL_isKeyReleased(int key) {
  return glfwGetKey(mgl_frame, key) == GLFW_RELEASE;
}

int MGL_isKeyHeld(int key) {
  if (glfwGetKey(mgl_frame, key) == GLFW_REPEAT) {
    return 1;
  } else {
    return 0;
  }
}

void MGL_processInput(GLFWwindow* window) {}
