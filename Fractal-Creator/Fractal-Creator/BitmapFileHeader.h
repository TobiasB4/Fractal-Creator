#ifndef BITMAP_FILE_HEADER_H_
#define BITMAP_FILE_HEADER_H_
#include <cstdint>
#pragma pack(2)
namespace bitmap {
struct BitmapFileHeader {
  char header[2]{'B', 'M'};
  int32_t fileSize;
  int32_t reserved{0};
  int32_t dataOffset;
};
}  // namespace bitmap
#endif