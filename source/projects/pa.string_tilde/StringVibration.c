//
// Created by Leonard Eyer on 16.07.20.
//
#include "StringVibration.h"

#define _USE_MATH_DEFINES
#include <math.h> // cos...

#define M_PI_POW_2 9.8696044011f

// ######### Helper functions #############
float heavside(float x) {
  return (float) (x >= 0.f);
}

float k(int i, float L) {
  return M_PI * i / L;
}

float w(int i, float alpha, float c_0, float L) {
  return sqrtf(powf(k(i, L) * c_0, 2.f) - powf(alpha, 2.f));
}
// #######################################

float phase_velocity(string s) {
  return 2 / s.diameter * sqrtf((float) (s.tension / M_PI * s.density));
}

float base_freq(string s) {
  return phase_velocity(s) / (2 * s.length);
}

float u(string s, float x, float t) {
  // Number of frequencies to compute
  int nFreq = 10;
  // The damping factor
  float alpha = 0.2f;
  // TODO: What is this
  float h_0 = 0.2f;
  // Normalized position of plucking
  float b = x / s.length;
  // Phase velocity
  float c_0 = phase_velocity(s);
  // Length
  float L = s.length;

  // Wave equation sampling (https://de.wikipedia.org/wiki/Saitenschwingung#Spektralanalyse_(Fouriertransformation))
  float sum = 0.f;
  for (int i = 1; i <= nFreq; ++i) {
    float part = (float) 2.0f * h_0 * sinf(M_PI * b * i) * sinf(k(i, L) * x) * cosf(w(i, alpha, c_0, L) * t);
    part /= M_PI_POW_2 * powf((float) i, 2.f) * b * L * (1 - b);
    sum += part;
  }
  sum *= powf(M_E, -alpha * t);

  return sum;
}
