#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_
#include <string>
#include <cstdint>
#include <memory>
#include <math.h>
#include <vector>
#include "Zoom.h"
#include "ZoomList.h"
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "RGB.h"
namespace fractal {
class FractalCreator {
 private:
  int _width{0};
  int _height{0};
  std::unique_ptr<int[]> _histogram;
  std::unique_ptr<int[]> _fractalIterations;
  bitmap::Bitmap _bmp;
  fractal::ZoomList _zoomList;
  int _total{0};

  std::vector<int> _ranges;
  std::vector<colour::RGB> _colours;
  std::vector<int> _rangeTotals;

  bool _bGotFirstRange{false};

 private:
  void calculateIteration();
  void calculateTotalIterations();
  void drawFractal();
  void addZoom(const Zoom& zoom);
  void writeBitmap(std::string name);
  void calculateRangeTotals();
  int getRange(int iterations) const;

 public:
  FractalCreator(int width, int height);
  void addRange(double rangeEnd, const colour::RGB &rgb);
  virtual ~FractalCreator();
  void run();
};
}  // namespace fractal
#endif
