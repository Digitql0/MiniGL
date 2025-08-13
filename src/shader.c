#include "shader.h"

// Vertex shader source (simple pass-through)
const char *mgl_vertexShaderSource = R"glsl(
#version 330 core
layout(location = 0) in vec3 aPos;

uniform float pointSize;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    gl_PointSize = pointSize;
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

unsigned int mgl_ID = 0;

void MGL_makeShader(void) {
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &mgl_vertexShaderSource, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s", infoLog);
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &mgl_fragmentShaderSource, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s", infoLog);
  }

  mgl_ID = glCreateProgram();
  glAttachShader(mgl_ID, vertex);
  glAttachShader(mgl_ID, fragment);
  glLinkProgram(mgl_ID);

  glGetProgramiv(mgl_ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(mgl_ID, 512, NULL, infoLog);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s", infoLog);
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void MGL_use(void) { glUseProgram(mgl_ID); }

void MGL_setBool(const char *name, int value) {
  glUniform1i(glGetUniformLocation(mgl_ID, name), value);
}

void MGL_setInt(const char *name, int value) {
  glUniform1i(glGetUniformLocation(mgl_ID, name), value);
}

void MGL_setFloat(const char *name, float value) {
  glUniform1f(glGetUniformLocation(mgl_ID, name), value);
  printf("%d\n", glGetUniformLocation(mgl_ID, name));
}

void MGL_setVec2(const char *name, const vec2 *value) {
  glUniform2fv(glGetUniformLocation(mgl_ID, name), 1, (const GLfloat *)value);
}

void MGL_setVec2_xy(const char *name, float x, float y) {
  glUniform2f(glGetUniformLocation(mgl_ID, name), x, y);
}

void MGL_setVec3(const char *name, const vec3 *value) {
  glUniform3fv(glGetUniformLocation(mgl_ID, name), 1, (const GLfloat *)value);
}

void MGL_setVec3_xyz(const char *name, float x, float y, float z) {
  glUniform3f(glGetUniformLocation(mgl_ID, name), x, y, z);
}

void MGL_setVec4(const char *name, const vec4 *value) {
  glUniform4fv(glGetUniformLocation(mgl_ID, name), 1, (const GLfloat *)value);
}

void MGL_setVec4_xyzw(const char *name, float x, float y, float z, float w) {
  glUniform4f(glGetUniformLocation(mgl_ID, name), x, y, z, w);
}

void MGL_setMat2(const char *name, const mat2 *mat) {
  glUniformMatrix2fv(glGetUniformLocation(mgl_ID, name), 1, GL_FALSE,
                     (const GLfloat *)mat);
}

void MGL_setMat3(const char *name, const mat3 *mat) {
  glUniformMatrix3fv(glGetUniformLocation(mgl_ID, name), 1, GL_FALSE,
                     (const GLfloat *)mat);
}

void MGL_setMat4(const char *name, const mat4 *mat) {
  glUniformMatrix4fv(glGetUniformLocation(mgl_ID, name), 1, GL_FALSE,
                     (const GLfloat *)mat);
}

void MGL_checkCompileErrors(GLuint shader, const char *type) {
  GLint success;
  GLchar infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      printf(
          "ERROR::SHADER_COMPILATION_ERROR of type: %s\n%s\n "
          "----------------------------------------------------- -- ",
          type, infoLog);
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      printf(
          "ERROR::PROGRAM_LINKING_ERROR of type: %s\n%s\n "
          "--------------------------------------------------------",
          type, infoLog);
    }
  }
}
