#ifndef MINIGL_HPP
#define MINIGL_HPP

// OpenGL
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.hpp"
#include "RenderGlobals.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void MakeWindow(int width, int height, const char *title);
void drawRectangle(float posx, float posy, float width, float height, int r, int g, int b);
void drawCircle(float posx, float posy, float radius, int r, int g, int b, Anchor anchor = Anchor::Center);
void drawLine(float x1, float y1, float x2, float y2, int r, int g, int b);
void lineWidth(float width);
void setPerspective(Perspectives perspective);
bool WindowShouldClose();
void BeginDrawing();
void ClearBackground(int r, int g, int b);
void EndDrawing();
void CloseWindow();
void glfwSetup();
void GLADSetup();
void processInput(GLFWwindow* window);
void initializeRectangleVAO();
void initializeCircleVAO(int segments = 32);
void initializeLineVAO();

#endif //MINIGL_HPP
