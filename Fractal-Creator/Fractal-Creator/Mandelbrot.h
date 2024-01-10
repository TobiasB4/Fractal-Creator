#ifndef MANDELBROT_H_
#define MANDELBROT_H_
namespace fractal {
class Mandelbrot {
 private:
 public:
  static const int MAX_ITERATIONS = 10000;
 public:
  Mandelbrot();
  virtual ~Mandelbrot();
  static int getIterations(double x, double y);
};
}  // namespace fractal
#endif
