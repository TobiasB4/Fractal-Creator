#include "Bitmap.h"
#include "BitmapInfoHeader.h"
#include "BitmapFileHeader.h"
#include <fstream>

namespace bitmap {
Bitmap::Bitmap(int width, int height)
    : _width(width),
      _height(height),
      _pPixels(new uint8_t[width * height * 3]{}){}


Bitmap::~Bitmap() {

}

bool Bitmap::write(std::string filename) { 
  BitmapFileHeader fileHeader;
  BitmapInfoHeader infoHeader;

  fileHeader.fileSize =
      sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + _width * _height * 3;
  fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

  infoHeader.width = _width;
  infoHeader.height = _height;

  std::fstream outputFile;

  outputFile.open(filename, std::ios::out|std::ios::binary);

  if (!outputFile) {
    return false;
  }

  outputFile.write(reinterpret_cast<const char *>(&fileHeader), sizeof(fileHeader));
  outputFile.write(reinterpret_cast<const char *>(&infoHeader), sizeof(infoHeader));
  outputFile.write(reinterpret_cast<const char *>(_pPixels.get()), _width*_height*3);

  outputFile.close();
  if (!outputFile) {
    return false;
  }
  return true;
}


void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
  uint8_t *pPixel = _pPixels.get();
  pPixel += (y * _width + x) * 3;

  // bitmap is little endian so RGB is reversed
  pPixel[0] = blue;
  pPixel[1] = green;
  pPixel[2] = red;
}

}