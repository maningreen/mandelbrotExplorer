#ifndef camera_h
#define camera_h

#include <raylib.h>

#define upKey KEY_W
#define downKey KEY_S
#define leftKey KEY_A
#define rightKey KEY_D

typedef struct {
  double position[2];
  double zoom;
} cameraD;

//this is relative to zoom
#define cameraSpeed 1000

#define zoomInKey KEY_Q
#define zoomOutKey KEY_E

#define zoomSpeed 1

void manageCameraMovement(cameraD& cam, float& delta);
void manageCameraZoom(cameraD& cam, float& delta);
void manageCamera(cameraD& cam, float& delta);

#endif
