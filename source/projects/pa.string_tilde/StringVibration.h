//
// Created by Leonard Eyer on 16.07.20.
//

#ifndef DRUM_SHAPES_SOURCE_PROJECTS_PA_STRING_TILDE_STRINGVIBRATION_H_
#define DRUM_SHAPES_SOURCE_PROJECTS_PA_STRING_TILDE_STRINGVIBRATION_H_

typedef struct string {
  // L
  float length;
  // psi
  float tension;
  // D
  float diameter;
  // rho
  float density;

} string;

float base_freq(string s);

float u(string s, float x, float t);

#endif //DRUM_SHAPES_SOURCE_PROJECTS_PA_STRING_TILDE_STRINGVIBRATION_H_
