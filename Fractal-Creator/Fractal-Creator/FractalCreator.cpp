#include "FractalCreator.h"
#include <iostream>

namespace fractal {

void FractalCreator::run() {
  addZoom(fractal::Zoom(295, _height - 202, 0.1));
  addZoom(fractal::Zoom(312, _height - 304, 0.1));

  calculateIteration();
  calculateTotalIterations();
  calculateRangeTotals();
  drawFractal();
  writeBitmap("test.bmp");
}

void FractalCreator::addRange(double rangeEnd, const colour::RGB& rgb) {
  _ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
  _colours.push_back(rgb);

  if (_bGotFirstRange) {
    _rangeTotals.push_back(0);
  }

  _bGotFirstRange = true;
}

void FractalCreator::addZoom(const Zoom& zoom) { _zoomList.add(zoom); }

FractalCreator::FractalCreator(int width, int height)
    : _width(width),
      _height(height),
      _histogram(new int[Mandelbrot::MAX_ITERATIONS]{0}),
      _fractalIterations(new int[width * height]{0}),
      _bmp(width, height),
      _zoomList(width, height) {
  _zoomList.add(fractal::Zoom(_width / 2, _height / 2, 4. / _width));
}

FractalCreator::~FractalCreator() {}

void FractalCreator::calculateIteration() {
  for (int x = 0; x < _width; x++) {
    for (int y = 0; y < _height; y++) {
      std::pair<double, double> coords = _zoomList.doZoom(x, y);

      int iterations =
          fractal::Mandelbrot::getIterations(coords.first, coords.second);
      _fractalIterations[y * _width + x] = iterations;
      if (iterations != fractal::Mandelbrot::MAX_ITERATIONS) {
        _histogram[iterations]++;
      }
      uint8_t colour =
          static_cast<uint8_t>(256 * static_cast<double>(iterations) /
                               fractal::Mandelbrot::MAX_ITERATIONS);
    }
  }
}

void FractalCreator::calculateRangeTotals() { 
  int rangeIndex = 0;
  for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
    int pixels = _histogram[i];
    if (i >= _ranges[rangeIndex + 1]) {
      rangeIndex++;
    }
    _rangeTotals[rangeIndex] += pixels;
  }
}

void FractalCreator::calculateTotalIterations() {
  for (int i = 0; i < fractal::Mandelbrot::MAX_ITERATIONS; i++) {
    _total += _histogram[i];
  }
}

void FractalCreator::drawFractal() {
  for (int i = 0; i < fractal::Mandelbrot::MAX_ITERATIONS; i++) {
    _total += _histogram[i];
  }
  for (int x = 0; x < _width; x++) {
    for (int y = 0; y < _height; y++) {
      int iterations = _fractalIterations[y * _width + x];

      int range = getRange(iterations);
      int rangeTotal = _rangeTotals[range];
      int rangeStart = _ranges[range];

      colour::RGB& startColour = _colours[range];
      colour::RGB& endColour = _colours[range+1];
      colour::RGB colourDiff = endColour - startColour;

      uint8_t red{0};
      uint8_t green{0};
      uint8_t blue{0};

      if (iterations != fractal::Mandelbrot::MAX_ITERATIONS) {
        int totalPixels = 0;

        for (int i = rangeStart; i <= iterations; i++) {
          totalPixels += _histogram[i];
        }

        red = startColour.r +
              colourDiff.r * static_cast<double>(totalPixels) / rangeTotal;
        green = startColour.g +
                colourDiff.g * static_cast<double>(totalPixels) / rangeTotal;
        blue = startColour.b +
               colourDiff.b * static_cast<double>(totalPixels) / rangeTotal;
      }

      _bmp.setPixel(x, y, red, green, blue);
    }
  }
}

void FractalCreator::writeBitmap(std::string name) { _bmp.write(name); }

int FractalCreator::getRange(int iterations) const {
  int range = 0;
  for (int i = 0; i < _ranges.size(); i++) {
    range = i;
    if (_ranges[i] >= iterations) {
      break;
    }
  }
  range--;
  return range;
}

}  // namespace fractal
