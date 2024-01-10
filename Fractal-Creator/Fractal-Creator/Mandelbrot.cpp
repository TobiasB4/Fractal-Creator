#include <complex>
#include "Mandelbrot.h"

namespace fractal {
Mandelbrot::Mandelbrot() {}
Mandelbrot::~Mandelbrot() {}
int Mandelbrot::getIterations(double x, double y) { 
  double x0{0}, y0{0}, x1{0}, y1{0};
  int iterations{0};
  do {
    iterations++;
    y0 = 2 * x0 * y0 + y;
    x0 = x1 - y1 + x;
    x1 = x0 * x0;
    y1 = y0 * y0;
  } while (x1 + y1 <= 4 && iterations < MAX_ITERATIONS);
  return iterations;
}
}  // namespace fractal