//
// Created by Leonard Eyer on 16.07.20.
//
#include "RectangleVibration.h"

#define _USE_MATH_DEFINES
#include <math.h> // cos...

#define M_PI_POW_2 9.8696044011f

//vibration(x,y,t)=spaceVibration(x,y)*timeVibration(t)
float a, b;

void setBorders(float left, float right) {
  a = left;
  b = right;
}
float eigenValue(int n, int m) {
  float lambda_nm = M_PI_POW_2*sqrt(n)/sqrtf(a) + M_PI_POW_2*sqrt(m)/sqrtf(b);
  return lambda_nm;
}
  
float spaceVibration(int n, int m, float x, float y) {
  float vibration = 0.f;
  vibration = sinf(M_PI*n*x/a)*sin(M_PI*m*x/b);
  return vibration;
}

float timeVibration(int n, int m, float t) {
  float vibration = 0.f;
  float mu = sqrtf(eigenValue(n,m));
  vibration = a*cos(mu*t)+b*sin(mu*t);
  return vibration;
}

float Vibration(int n, int m, float x, float y, float t) {
  float vibration = 0.f;
  vibration = spaceVibration(n, m, x, y)*timeVibration(n,m,t);
  return vibration;
}

