#include "input.hpp"

bool MGL_isKeyPressed(int key) {
  return glfwGetKey(mgl_frame, key) == GLFW_PRESS;
}

bool MGL_isKeyReleased(int key) {
  return glfwGetKey(mgl_frame, key) == GLFW_RELEASE;
}

bool MGL_isKeyHeld(int key) {
  return glfwGetKey(mgl_frame, key) == GLFW_REPEAT;
}

void MGL_processInput(GLFWwindow* window) {}
