#ifndef CAMERA_H
#define CAMERA_H

#include "RenderGlobals.h"

// DO NOT FREE THIS POINTER
Camera* MGLC_getCamera();

void MGLC_setPosition(vec3 pos, Camera* cam);
void MGLC_updatePositionLocal(float x, float y, float z, Camera* cam);
void MGLC_updatePositionWorld(float x, float y, float z, Camera* cam);
void MGLC_setRotation(vec3 rot, Camera* cam);
void MGLC_updateRotationLocal(float p, float y, float r, Camera* cam);
void MGLC_updateRotationWorld(float p, float y, float r, Camera* cam);
void MGLC_setFOV(float f, Camera* cam);
void MGLC_updateFOV(float f, Camera* cam);
void MGLC_setZoom(float z, Camera* cam);
void MGLC_updateZoom(float z, Camera* cam);
void MGLC_setAspectRatio(float ar, Camera* cam);
void MGLC_setAspectRatioWidthHeight(float width, float height, Camera* cam);
void MGLC_setNearPlane(float np, Camera* cam);
void MGLC_updateNearPlane(float np, Camera* cam);
void MGLC_setFarPlane(float fp, Camera* cam);
void MGLC_updateFarPlane(float fp, Camera* cam);
void MGLC_setPerspective(Perspectives perspective, Camera* cam);
void MGLC_setSpeed(float s, Camera* cam);
void MGLC_updateSpeed(float s, Camera* cam);
void MGLC_setSensitivity(float s, Camera* cam);
void MGLC_updateSensitivity(float s, Camera* cam);
void MGLC_hideMouse();
void MGLC_showMouse();
void MGLC_setCamera(Camera* cam);
void MGLC_updateMatrices(Camera* cam);

#endif
