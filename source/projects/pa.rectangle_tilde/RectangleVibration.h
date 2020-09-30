//
// Created by Leonard Eyer on 16.07.20.
//
/** @file
 * Rectangle membran Vibration model
 * */

#ifndef DRUM_SHAPES_SOURCE_PROJECTS_PA_STRING_TILDE_STRINGVIBRATION_H_
#define DRUM_SHAPES_SOURCE_PROJECTS_PA_STRING_TILDE_STRINGVIBRATION_H_

typedef struct string {
  float length; ///< Length L
  float tension; ///< Tension psi
  float diameter; ///< Diameter D
  float density; ///< Density rho

} string;

/**
 * For given string compute it's phase velocity
 * @param s the string
 * @return the velocity
 */
float phase_velocity(string s);

/**
 * @brief Base frequency of the string vibration
 * @param s the string
 * @return lowest frequency
 */
float base_freq(string s);

/**
 * @brief Evaluation of the wave equation
 * @param s string
 * @param x position of plucking
 * @param t time
 * @return string displacement
 */
float vibration(float x, float y, float t);

#endif //DRUM_SHAPES_SOURCE_PROJECTS_PA_STRING_TILDE_STRINGVIBRATION_H_
