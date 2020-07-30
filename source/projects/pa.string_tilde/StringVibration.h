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

/**
 * For given string compute it's phase velocity
 * @param s the string
 * @return the velocity
 */
float phase_velocity(string s);

/**
 * Base frequency of the string vibration
 * @param s the string
 * @return lowest frequency
 */
float base_freq(string s);

/**
 * Evaluation of the wave equation
 * @param s string
 * @param x position of plucking
 * @param t time
 * @return string displacement
 */
float u(string s, float x, float t);

#endif //DRUM_SHAPES_SOURCE_PROJECTS_PA_STRING_TILDE_STRINGVIBRATION_H_
