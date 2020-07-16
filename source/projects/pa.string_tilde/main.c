//
// Created by Leonard Eyer on 16.07.20.
//
#include <stdio.h>
#include "StringVibration.h"

int main(int argc, char **argv) {
  for (int j = 0; j < 10; ++j) {
    float x = (float) 0.25;
    float t = (float) j / 10.f;
    printf("u(%f,%f) = %f\n", x, t, u(x, t));
  }
}
