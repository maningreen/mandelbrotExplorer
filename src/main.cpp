#include <cmath>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "camera.h"
#include "include.h"

#define max(a, b) (a > b ? a : b)
#define vec2(x, y) (Vector2){x, y}

#define incCX KEY_UP
#define decCX KEY_DOWN
#define incCY KEY_LEFT
#define decCY KEY_RIGHT

//relative to zoom
#define incCSpeed 5.0f

#define mandelToggle KEY_SPACE

int main() {
  InitWindow(600, 600, "Mandelbrot set");
  SetTargetFPS(60);
  cameraD cam = {{0}, 1};
  Shader shad = LoadShader(0, "src/test.fs");
  Texture2D texture;
  Image blnk;

  blnk = LoadImageFromScreen();
  texture = LoadTextureFromImage(blnk);

  int zoomCenterPos = GetShaderLocation(shad, "zoomTarget");
  int mandelPos = GetShaderLocation(shad, "mandel");
  int camZoomPos = GetShaderLocation(shad, "zoomFactor");
  int cOffsetPos = GetShaderLocation(shad, "offset");
  int mandel = 1;

  Vector2 c = vec2(0, 0);

  while(!WindowShouldClose()) {
    float delta = GetFrameTime();

    Vector2 KeyC;
    KeyC.x = IsKeyDown(incCX) - IsKeyDown(decCX);
    KeyC.y = IsKeyDown(incCY) - IsKeyDown(decCY);
    c = Vector2Add(c, Vector2Scale(KeyC, incCSpeed * delta / cam.zoom));

    if(IsKeyPressed(mandelToggle))
      mandel = !mandel;

    manageCamera(cam,delta);
    float camPosF[2] = {(float)cam.position[0] / GetScreenWidth(), -(float)cam.position[1] / GetScreenHeight()};
    float camZoom = cam.zoom;
    SetShaderValue(shad, zoomCenterPos, camPosF, SHADER_UNIFORM_VEC2);
    SetShaderValue(shad, camZoomPos, &camZoom, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shad, mandelPos, &mandel, SHADER_UNIFORM_INT);
    SetShaderValue(shad, cOffsetPos, &c, SHADER_UNIFORM_VEC2);

    BeginDrawing();
    ClearBackground(BLACK);

    BeginShaderMode(shad);

    DrawTexture(texture, 0, 0, WHITE);

    EndShaderMode();

    DrawText(TextFormat("Offset real %.02f", c.x), 0, 0, 15, WHITE);
    DrawText(TextFormat("Offset imag %.02f", c.y), 0, MeasureTextEx(GetFontDefault(), "A", 15, GetFontDefault().baseSize).y, 15, WHITE);

    EndDrawing();
  }

  CloseWindow();
  return 0;
}
