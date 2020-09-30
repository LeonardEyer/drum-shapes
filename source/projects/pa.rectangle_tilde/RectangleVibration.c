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
  float lambda_nm = M_PI_POW_2*pow(n,2)/pow(a,2) + M_PI_POW_2*pow(m,2)/pow(b,2);
  return lambda_nm;
}
  
float spaceVibration(int n, int m, float x, float y) {
  float vibration = 0.f;
  vibration = sinf(M_PI*n*x/a)*sin(M_PI*m*x/b);
  return vibration;
}

float coef_a(int n, int m) {
  float alpha = 0.1;
  return (alpha*4/M_PI_POW_2)*sin(M_PI*m)*sin(M_PI*n)/((pow(m,2)-1)*(pow(n,2)-1));
}

float coef_b(int n, int m) {
  float mu = sqrtf(eigenValue(n,m));
  return coef_a(n,m)/mu;
}

float timeVibration(int n, int m, float t) {
  float vibration = 0.f;
  float mu = sqrtf(eigenValue(n,m));
  vibration = coef_a(n,m)*cos(mu*t)+coef_b(n,m)*sin(mu*t);
  return vibration;
}

float vibration(float x, float y, float t) {
  float vibration = 0.f;
  for(int n=1; n<=10; n++) {
    for(int m=1; m<=10; m++) {
      vibration += spaceVibration(n, m, x, y)*timeVibration(n,m,t);
    }
  }
  return vibration;
}

