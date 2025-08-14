#include "shader.h"

unsigned int MGL_makeShader(const char *vertexShaderSource,
                            const char *fragmentShaderSource) {
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexShaderSource, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s", infoLog);
  }

  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s", infoLog);
  }

  unsigned int id;

  id = glCreateProgram();
  glAttachShader(id, vertex);
  glAttachShader(id, fragment);
  glLinkProgram(id);

  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(id, 512, NULL, infoLog);
    printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s", infoLog);
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  return id;
}
void MGL_use(unsigned int id) { glUseProgram(id); }
void MGL_setBool(unsigned int id, const char *name, int value) {
  glUniform1i(glGetUniformLocation(id, name), value);
}
void MGL_setInt(unsigned int id, const char *name, int value) {
  glUniform1i(glGetUniformLocation(id, name), value);
}
void MGL_setFloat(unsigned int id, const char *name, float value) {
  glUniform1f(glGetUniformLocation(id, name), value);
  printf("%d\n", glGetUniformLocation(id, name));
}
void MGL_setVec2(unsigned int id, const char *name, const vec2 *value) {
  glUniform2fv(glGetUniformLocation(id, name), 1, (const GLfloat *)value);
}
void MGL_setVec2_xy(unsigned int id, const char *name, float x, float y) {
  glUniform2f(glGetUniformLocation(id, name), x, y);
}
void MGL_setVec3(unsigned int id, const char *name, const vec3 *value) {
  glUniform3fv(glGetUniformLocation(id, name), 1, (const GLfloat *)value);
}
void MGL_setVec3_xyz(unsigned int id, const char *name, float x, float y,
                     float z) {
  glUniform3f(glGetUniformLocation(id, name), x, y, z);
}
void MGL_setVec4(unsigned int id, const char *name, const vec4 *value) {
  glUniform4fv(glGetUniformLocation(id, name), 1, (const GLfloat *)value);
}
void MGL_setVec4_xyzw(unsigned int id, const char *name, float x, float y,
                      float z, float w) {
  glUniform4f(glGetUniformLocation(id, name), x, y, z, w);
}
void MGL_setMat2(unsigned int id, const char *name, const mat2 *mat) {
  glUniformMatrix2fv(glGetUniformLocation(id, name), 1, GL_FALSE,
                     (const GLfloat *)mat);
}
void MGL_setMat3(unsigned int id, const char *name, const mat3 *mat) {
  glUniformMatrix3fv(glGetUniformLocation(id, name), 1, GL_FALSE,
                     (const GLfloat *)mat);
}
void MGL_setMat4(unsigned int id, const char *name, const mat4 *mat) {
  glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE,
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
