#version 450

in vec2 fragTexCoord;
in vec4 fragColor;

uniform vec2 zoomTarget;
uniform float zoomFactor;
uniform int mandel;
uniform vec2 offset;

#define loopCount 512

out vec4 finalColor;

float distSqred = 100 * 100;

dvec2 mulComp(dvec2 a, dvec2 b) {
    return dvec2(a.x * b.x - (a.y * b.y), 2 * a.x * b.y);
  }

dvec3 mandelCalc(dvec2 n) {
    dvec2 z = offset;
    float i = 0;
    for(; i < loopCount; i++) {
      z = mulComp(z, z) + n;
      if(z.x * z.x + z.y * z.y >= distSqred)
        break;
      }
    return dvec3(z, i);
  }

dvec3 juliusCalc(dvec2 n) {
    dvec2 z = n;
    float i = 0;
    for(; i < loopCount; i++) {
        z = mulComp(z, z) + offset;
        if(z.x * z.x + z.y * z.y > distSqred)
          break;
      }
    return dvec3(z, i);
  }

vec4 calcColour(dvec2 endingPos, double time) {
  if(time == loopCount)
    return vec4(0);
  double perc = time / loopCount;
  return vec4(perc * .5, perc * .5, perc, 1);
  }

void main() {
  //this is gonna be a little brute forced.
  dvec2 zoomTargetD = dvec2(zoomTarget);
  double zoomFactorD = zoomFactor;
  dvec2 scaledPos = (((fragTexCoord - dvec2(.5, .5)) * 4.0) / zoomFactorD) + zoomTargetD;
  dvec3 time;
  if(mandel == 1)
    time = mandelCalc(scaledPos);
  else
    time = juliusCalc(scaledPos);
  finalColor = calcColour(time.xy, time.z);
}
