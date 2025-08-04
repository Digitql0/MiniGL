#include "input.hpp"

bool isKeyPressed(int key) { return glfwGetKey(frame, key) == GLFW_PRESS; }

bool isKeyReleased(int key) { return glfwGetKey(frame, key) == GLFW_RELEASE; }

bool isKeyHeld(int key) { return glfwGetKey(frame, key) == GLFW_REPEAT; }

void processInput(GLFWwindow* window) {}
