#include "camera.h"

#define CGLM_FORCE_QUAT
#include <cglm/cglm.h>
#include <cglm/quat.h>

#include "RenderGlobals.h"
#include "utilities.h"

Camera* MGLC_getCamera() { return &camera; }

void MGLC_setPosition(vec3 pos, Camera* cam) {
  cam->position[0] = pos[0];
  cam->position[1] = pos[1];
  cam->position[2] = pos[2];
}

void MGLC_updatePositionLocal(float x, float y, float z, Camera* cam) {
  // Canonical basis vectors
  vec3 forward = {0.0f, 0.0f, -1.0f};
  vec3 right = {1.0f, 0.0f, 0.0f};
  vec3 up = {0.0f, 1.0f, 0.0f};

  vec3 rotatedForward, rotatedRight, rotatedUp;
  // Rotate each by the camera's orientation quaternion
  glm_quat_rotatev(cam->orientation, forward, rotatedForward);
  glm_quat_rotatev(cam->orientation, right, rotatedRight);
  glm_quat_rotatev(cam->orientation, up, rotatedUp);

  // Now update position along local axes, fully respecting pitch/yaw/roll
  for (int i = 0; i < 3; i++) {
    cam->position[i] += rotatedRight[i] * x * cam->speed;
    cam->position[i] += rotatedUp[i] * y * cam->speed;
    cam->position[i] += rotatedForward[i] * z * cam->speed;
  }
}

void MGLC_updatePositionWorld(float x, float y, float z, Camera* cam) {
  cam->position[0] += x * cam->speed;
  cam->position[1] += y * cam->speed;
  cam->position[2] += z * cam->speed;
}

void MGLC_setRotation(vec3 rot, Camera* cam) {
  cam->rotation[0] = glm_clamp(rot[0], -glm_rad(89.0f), glm_rad(89.0f));
  cam->rotation[1] = rot[1];
  cam->rotation[2] = rot[2];
}

void MGLC_updateRotationLocal(float p, float y, float r, Camera* cam) {
  p *= cam->sensitivity;
  y *= cam->sensitivity;
  r *= cam->sensitivity;

  // Update Euler angles by adding deltas
  cam->rotation[0] += p;
  cam->rotation[1] += y;
  cam->rotation[2] += r;

  // Clamp pitch to avoid gimbal lock
  const float pitchLimit = glm_rad(89.0f);
  if (cam->rotation[0] > pitchLimit) cam->rotation[0] = pitchLimit;
  if (cam->rotation[0] < -pitchLimit) cam->rotation[0] = -pitchLimit;

  // Rebuild orientation quaternion from updated Euler angles
  versor qPitch, qYaw, qRoll, temp;

  glm_quatv(qPitch, cam->rotation[0], (vec3){1.0f, 0.0f, 0.0f});  // pitch
  glm_quatv(qYaw, cam->rotation[1], (vec3){0.0f, 1.0f, 0.0f});    // yaw
  glm_quatv(qRoll, cam->rotation[2], (vec3){0.0f, 0.0f, 1.0f});   // roll

  glm_quat_mul(qYaw, qPitch, temp);
  glm_quat_mul(temp, qRoll, cam->orientation);
}

void MGLC_updateRotationWorld(float p, float y, float r, Camera* cam) {
  cam->rotation[0] += p * cam->sensitivity;
  cam->rotation[0] =
      glm_clamp(cam->rotation[0], -glm_rad(89.0f), glm_rad(89.0f));
  cam->rotation[1] += y * cam->sensitivity;
  cam->rotation[2] += r * cam->sensitivity;
}

void MGLC_setFOV(float f, Camera* cam) { cam->fov = f; }

void MGLC_updateFOV(float f, Camera* cam) { cam->fov += f; }

void MGLC_setZoom(float z, Camera* cam) { cam->zoom = z; }

void MGLC_updateZoom(float z, Camera* cam) { cam->zoom += z; }

void MGLC_setAspectRatio(float ar, Camera* cam) { cam->aspectRatio = ar; }

void MGLC_setAspectRatioWidthHeight(float width, float height, Camera* cam) {
  cam->aspectRatio = width / height;
}

void MGLC_setNearPlane(float np, Camera* cam) { cam->nearPlane = np; }

void MGLC_updateNearPlane(float np, Camera* cam) { cam->nearPlane += np; }

void MGLC_setFarPlane(float fp, Camera* cam) { cam->farPlane = fp; }

void MGLC_updateFarPlane(float fp, Camera* cam) { cam->farPlane += fp; }

void MGLC_setPerspective(Perspectives perspective, Camera* cam) {
  cam->perspective = perspective;
}

void MGLC_setSpeed(float s, Camera* cam) { cam->speed = s; }

void MGLC_updateSpeed(float s, Camera* cam) { cam->speed += s; }

void MGLC_setSensitivity(float s, Camera* cam) { cam->sensitivity = s; }

void MGLC_updateSensitivity(float s, Camera* cam) { cam->sensitivity += s; }

void MGLC_hideMouse() {
  glfwSetInputMode(mgl_frame, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void MGLC_showMouse() {
  glfwSetInputMode(mgl_frame, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void MGLC_setCamera(Camera* cam) {
  camera.position[0] = cam->position[0];
  camera.position[1] = cam->position[1];
  camera.position[2] = cam->position[2];
  camera.rotation[0] = cam->rotation[0];
  camera.rotation[1] = cam->rotation[1];
  camera.rotation[2] = cam->rotation[2];
  camera.fov = cam->fov;
  camera.zoom = cam->zoom;
  camera.aspectRatio = cam->aspectRatio;
  camera.nearPlane = cam->nearPlane;
  camera.farPlane = cam->farPlane;
  camera.perspective = cam->perspective;
}

void MGLC_updateMatrices(Camera* cam) {
  if (cam->perspective == Perspective) {
    glm_perspective(glm_rad(cam->fov), cam->aspectRatio, cam->nearPlane,
                    cam->farPlane, cam->projection);
  } else if (cam->perspective == Orthographic) {
    float zoom = cam->zoom;
    float aspect = cam->aspectRatio;
    glm_ortho(-zoom * aspect, zoom * aspect, zoom, -zoom, cam->nearPlane,
              cam->farPlane, cam->projection);

    printf("%f, %f, %d, %d, %d, %d\n", zoom, aspect,
           -mgl_screenWidth / 2 == -zoom * aspect,
           mgl_screenWidth / 2 == zoom * aspect, mgl_screenHeight / 2 == zoom,
           -mgl_screenHeight / 2 == -zoom);
  }

  versor qPitch, qYaw, qRoll, temp;

  glm_quatv(qPitch, cam->rotation[0], (vec3){1.0f, 0.0f, 0.0f});  // pitch
  glm_quatv(qYaw, cam->rotation[1], (vec3){0.0f, 1.0f, 0.0f});    // yaw
  glm_quatv(qRoll, cam->rotation[2], (vec3){0.0f, 0.0f, 1.0f});   // roll

  glm_quat_mul(qYaw, qPitch, temp);
  glm_quat_mul(temp, qRoll, cam->orientation);

  // 2. Convert quaternion to rotation matrix (4x4)
  mat4 rotMat;
  glm_quat_mat4(cam->orientation, rotMat);

  // 3. Transpose rotation matrix to invert rotation (camera rotation → world
  // rotation)
  glm_mat4_transpose(rotMat);

  // 4. Build translation matrix (translate world opposite to camera position)
  mat4 translation;
  glm_mat4_identity(translation);
  glm_translate(translation, (vec3){-cam->position[0], -cam->position[1],
                                    -cam->position[2]});

  // 5. Compose view matrix = rotation * translation
  glm_mat4_mul(rotMat, translation, cam->view);

  // vec4 forward4 = {0.0f, 0.0f, -1.0f, 0.0f};
  // mat4 rot;
  // glm_euler_xyz(cam->rotation, rot);

  // vec4 rotatedForward4;
  // glm_mat4_mulv(rot, forward4, rotatedForward4);

  // vec3 forward3 = {rotatedForward4[0], rotatedForward4[1],
  // rotatedForward4[2]};

  // vec3 target;
  // glm_vec3_add(cam->position, forward3, target);

  // vec3 up = {0.0f, -1.0f, 0.0f};
  // glm_lookat(cam->position, target, up, cam->view);
}
