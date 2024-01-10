#include <iostream>
#include "FractalCreator.h"


int main() {
  fractal::FractalCreator fractalCreator(800, 600);
  fractalCreator.addRange(0., colour::RGB(0, 0, 0));
  fractalCreator.addRange(0.3, colour::RGB(255, 0, 0));
  fractalCreator.addRange(0.5, colour::RGB(255, 255, 0));
  fractalCreator.addRange(1., colour::RGB(255, 255, 255));
  fractalCreator.run();
  std::cout << "Finished." << std::endl;
  return 0;
}
