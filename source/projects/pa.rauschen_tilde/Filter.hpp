//
// Created by Leonard Eyer on 2019-06-04.
//

#ifndef AKSYNTH_PROJECT_FILTER_H
#define AKSYNTH_PROJECT_FILTER_H

#include <cstdlib>
#include <cstring>

#include <limits>
#include <iostream>

/**
 * Adaptive finite impulse response filter
 * Using NLMS Algorithm for weight updates
 */
class Filter {

 public:
  /**
   * Constructor
   * @param tap_count Amount of taps/coefficients
   */
  Filter(int tap_count, double learning_rate);

  /**
   * Filters input signal by applying filter response
   * @param in
   * @return
   */
  double process(double in);

  /**
   * Updates the weights to minimize err
   * @param err
   */
  void update_weights(double err);

  /**
   * Sets new mu
   * @param mu
   */
  void set_mu(double newMu);

  void reset();
  void zeroCoeff();
  void print_coeffs() const;
  void print_buff() const;
  void print_config();

  double *get_coeffs();
 private:
  double *coefficients;
  double *buffer;
  double mu;
  unsigned taps;
  unsigned offset = 0;
  const float eps = 1.0;
};

#endif //AKSYNTH_PROJECT_FILTER_H
