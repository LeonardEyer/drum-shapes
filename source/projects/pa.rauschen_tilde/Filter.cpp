//
// Csreated by Leonard Eyer on 2019-06-04.
//

#include <memory.h>
#include "Filter.hpp"

// init all coefficients and the buffer to zero
Filter::Filter(int tap_count, double learning_rate = 0.1) : coefficients(new double[tap_count]),
                                                            buffer(new double[tap_count]),
                                                            mu(learning_rate),
                                                            taps(tap_count) {
  zeroCoeff();
  reset();
}

double Filter::process(double in) {

  // Point to start of coeff array
  double *coeff = coefficients;
  // Current buffer position
  double *buf_val = buffer + offset;

  // Store new sample
  *buf_val = in;
  double out = 0;

  // Sum all buffer values with corresponding coefficients
  for (unsigned i = 0; i < taps; ++i) {

    out += *buf_val-- * *coeff++;

    // Wrap around
    if (buf_val < buffer)
      buf_val = buffer + taps - 1;
  }

  // Offset increment
  if (++offset >= taps)
    offset = 0;

  return out;
}

double *Filter::get_coeffs() {
  return coefficients;
}

void Filter::update_weights(double err) {
  /*
  double nu = mu / (eps + vb.norm());
  vc = vc + nu * err * vb;
   */

  // Current buffer position
  double *buf_val = buffer + offset;
  double *coeff = coefficients;

  // ####### Normalize learning rate #######
  // Compute norm of input signal vector
  double norm = 0;
  for (unsigned i = 0; i < taps; ++i)
    norm += buffer[i] * buffer[i];

  // Normalized learning rate
  double nu = mu / (eps + norm);

  // ####### Apply coefficient update #######
  for (unsigned i = 0; i < taps; ++i) {

    // Update coefficients
    *coeff++ += *buf_val-- * err * nu;

    // Wrap around
    if (buf_val < buffer)
      buf_val = buffer + taps - 1;
  }
}

void Filter::print_coeffs() const {

  std::cout << "Coefficients: ";
  for (unsigned i = 0; i < taps; ++i) {
    std::cout << coefficients[i] << ", ";
  }
  std::cout << std::endl;
}

void Filter::print_buff() const {
  std::cout << "Buffer: ";
  for (unsigned i = 0; i < taps; ++i) {
    std::cout << buffer[i] << ", ";
  }
  std::cout << std::endl;
}

void Filter::print_config() {
  std::cout << "mu " << mu << "\t eps " << eps << "\ttaps " << taps << std::endl;
}

void Filter::reset() {
  memset(buffer, 0, sizeof(double) * taps);
  offset = 0;
}

void Filter::zeroCoeff() {
  memset(coefficients, 0, sizeof(double) * taps);
  offset = 0;
}

void Filter::set_mu(double newMu) {
  mu = newMu;
}


