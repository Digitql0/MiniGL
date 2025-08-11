#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string.h>

#include "RenderGlobals.h"

void MGL_framebuffer_size_callback(GLFWwindow* window, int width, int height);
void MGL_mouse_callback(GLFWwindow* window, double xpos, double ypos);
void MGL_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void MGL_makeWindow(int width, int height, const char* title);
bool MGL_windowShouldClose();
void MGL_closeWindow();

void MGL_glfwSetup();
void MGL_gladSetup();

void MGL_initializeRectangleVAO();
void MGL_initializeCircleVAO(int segments);
void MGL_initializeLineVAO();

#endif
