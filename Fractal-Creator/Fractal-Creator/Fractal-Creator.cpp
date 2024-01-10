#include <iostream>
#include "Bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

int main() {
  const int WIDTH = 800;
  const int HEIGHT = 600;
  bitmap::Bitmap bmp(WIDTH, HEIGHT);
  bmp.setPixel(WIDTH / 2, HEIGHT / 2, 255, 255, 255);
  bmp.write("test.bmp");
  std::cout << "Finished." << std::endl;
  return 0;
}
