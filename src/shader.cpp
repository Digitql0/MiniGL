#include "shader.hpp"

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <sstream>

// Vertex shader source (simple pass-through)
const char *mgl_vertexShaderSource = R"glsl(
#version 330 core
layout(location = 0) in vec2 aPos;

uniform mat4 model;
uniform mat4 projection;

void main() {
    gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
}
)glsl";

// Fragment shader source (uniform color)
const char *mgl_fragmentShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;

uniform vec3 color;

void main() {
    FragColor = vec4(color, 1.0);
}
)glsl";

Shader::Shader() { std::cout << "SHADER LOL" << std::endl; }

void Shader::MGL_makeShader() {
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &mgl_vertexShaderSource, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &mgl_fragmentShaderSource, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  mgl_ID = glCreateProgram();
  glAttachShader(mgl_ID, vertex);
  glAttachShader(mgl_ID, fragment);
  glLinkProgram(mgl_ID);

  glGetProgramiv(mgl_ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(mgl_ID, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}
void Shader::MGL_use() { glUseProgram(mgl_ID); }
void Shader::MGL_setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(mgl_ID, name.c_str()), (int)value);
}
void Shader::MGL_setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(mgl_ID, name.c_str()), value);
}
void Shader::MGL_setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(mgl_ID, name.c_str()), value);
}
void Shader::MGL_setVec2(const std::string &name,
                         const glm::vec2 &value) const {
  glUniform2fv(glGetUniformLocation(mgl_ID, name.c_str()), 1, &value[0]);
}
void Shader::MGL_setVec2(const std::string &name, float x, float y) const {
  glUniform2f(glGetUniformLocation(mgl_ID, name.c_str()), x, y);
}
void Shader::MGL_setVec3(const std::string &name,
                         const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(mgl_ID, name.c_str()), 1, &value[0]);
}
void Shader::MGL_setVec3(const std::string &name, float x, float y,
                         float z) const {
  glUniform3f(glGetUniformLocation(mgl_ID, name.c_str()), x, y, z);
}
void Shader::MGL_setVec4(const std::string &name,
                         const glm::vec4 &value) const {
  glUniform4fv(glGetUniformLocation(mgl_ID, name.c_str()), 1, &value[0]);
}
void Shader::MGL_setVec4(const std::string &name, float x, float y, float z,
                         float w) const {
  glUniform4f(glGetUniformLocation(mgl_ID, name.c_str()), x, y, z, w);
}
void Shader::MGL_setMat2(const std::string &name, const glm::mat2 &mat) const {
  glUniformMatrix2fv(glGetUniformLocation(mgl_ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
void Shader::MGL_setMat3(const std::string &name, const glm::mat3 &mat) const {
  glUniformMatrix3fv(glGetUniformLocation(mgl_ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
void Shader::MGL_setMat4(const std::string &name, const glm::mat4 &mat) const {
  glUniformMatrix4fv(glGetUniformLocation(mgl_ID, name.c_str()), 1, GL_FALSE,
                     &mat[0][0]);
}
void Shader::MGL_checkCompileErrors(GLuint shader, std::string type) {
  GLint success;
  GLchar infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      std::cout
          << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
          << infoLog
          << "\n ----------------------------------------------------- -- "
          << std::endl;
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      std::cout
          << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
          << infoLog
          << "\n ----------------------------------------------------- -- "
          << std::endl;
    }
  }
}
