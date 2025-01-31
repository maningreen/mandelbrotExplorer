#include "camera.h"
#include <raylib.h>
#include <raymath.h>

void manageCameraZoom(cameraD& cam, float& delta) {
  //basically we don't want this to slow down as it gets bigger
  char keyZ /*key zoom*/ = IsKeyDown(zoomOutKey) - IsKeyDown(zoomInKey);
  cam.zoom += cam.zoom * keyZ * delta * zoomSpeed;
}

void manageCameraMovement(cameraD& cam, float& delta) {
  //i mean... what do i say?
  char keyY = IsKeyDown(upKey) - IsKeyDown(downKey);
  char keyX = IsKeyDown(rightKey) - IsKeyDown(leftKey);
  cam.position[0] += keyX * cameraSpeed * delta / cam.zoom;
  cam.position[1] += keyY * cameraSpeed * delta / cam.zoom;
}

void manageCamera(cameraD& cam, float& delta) {
  manageCameraMovement(cam, delta);
  manageCameraZoom(cam, delta);
}
