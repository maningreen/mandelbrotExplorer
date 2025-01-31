#ifndef complex_hpp
#define complex_hpp

#include <cmath>
#include <raylib.h>
#include "include.h"

#define sqrt(n) sqrtf(n) //i'm *way* too lazy to type f

//we will be using r * e^(theta * i) for these complex numbers
//(it's easier to implement than a + bi funnily enough (except with +- we swap to abi temporarily))

class complexNumber {
  public:
    float R;
    float Theta;

    complexNumber(float r, float theta);
    complexNumber(Vector2 abi);

    complexNumber operator*(complexNumber b) const;
    complexNumber operator+(complexNumber b) const;
    complexNumber operator-(complexNumber b) const;
    complexNumber operator/(complexNumber b) const;
    complexNumber operator*(float scalar) const;
    complexNumber operator/(float scalar) const;
    complexNumber operator-() const;

    void draw(Colour col) const;
    void draw(Colour col, Vector2 screenDimensions) const;
    void draw(Colour col, Camera2D& cam) const;
    void draw(Colour col, Camera2D& cam, Vector2 screenDimensions) const;

    Vector2 toAbi() const;
    static complexNumber fromAbi(Vector2 abi);

    static complexNumber I;
    static complexNumber One;
    static complexNumber Zero;
};


#endif
