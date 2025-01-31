#include "complex.hpp"
#include "include.h"
#include <cmath>
#include <raylib.h>
#include <raymath.h>

complexNumber complexNumber::I(0, M_PI / 2.0f);
complexNumber complexNumber::One(sqrt(2), M_PI / 4.0f);
complexNumber complexNumber::Zero(0, 0);

complexNumber::complexNumber(float r, float theta) {
  R = r;
  Theta = theta;
}

complexNumber::complexNumber(Vector2 coordinates) {
  *this = complexNumber::fromAbi(coordinates);
}

complexNumber complexNumber::operator*(complexNumber b) const {
  return complexNumber(R * b.R, Theta + b.Theta);
}

complexNumber complexNumber::operator/(complexNumber b) const {
  return complexNumber(R / b.R, Theta + b.Theta);
}

complexNumber complexNumber::operator-(complexNumber b) const {
  //so the thing here is we end up using sqrts :(.
  //we convert to abi and then back which hurts my soul.
  return complexNumber::fromAbi(Vector2Subtract(toAbi(), b.toAbi()));
}

complexNumber complexNumber::operator*(float scalar) const {
  return complexNumber(R * scalar, Theta);
}

complexNumber complexNumber::operator/(float scalar) const {
  return complexNumber(R / scalar, Theta);
}

complexNumber complexNumber::operator+(complexNumber b) const {
  //this still hurts
  return complexNumber::fromAbi(Vector2Add(toAbi(), b.toAbi()));
}

complexNumber complexNumber::operator-() const {
  return complexNumber(R, -Theta);
}

Vector2 complexNumber::toAbi() const {
  return (Vector2){cosf(Theta) * R, sinf(Theta) * R};
}

complexNumber complexNumber::fromAbi(Vector2 abi) {
  return complexNumber(Vector2Length(abi), atan2f(abi.x, abi.y));
}

void complexNumber::draw(Colour col) const {
  Vector2 abi = toAbi();
  DrawPixelV(Vector2Add((Vector2){-abi.y, abi.x}, (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f}) , col);
}

void complexNumber::draw(Colour col, Vector2 screenDimensions) const {
  Vector2 abi = toAbi();
  DrawPixelV(Vector2Add((Vector2){-abi.y, abi.x}, screenDimensions), col);
}

void complexNumber::draw(Colour col, Camera2D& cam) const {
  Vector2 abi = toAbi();
  DrawCircleV(Vector2Add((Vector2){-abi.y, abi.x}, (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f}), 1.0f / cam.zoom, col);
}
