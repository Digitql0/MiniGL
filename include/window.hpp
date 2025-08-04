#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "RenderGlobals.hpp"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void MakeWindow(int width, int height, const char *title);
bool WindowShouldClose();
void CloseWindow();

void glfwSetup();
void GLADSetup();

void initializeRectangleVAO();
void initializeCircleVAO(int segments = 32);
void initializeLineVAO();

#endif
