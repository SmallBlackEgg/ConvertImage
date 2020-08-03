#pragma once
#include "ImageRead.h"
#include <string>
class ImageFactory {
public:
  ImageFactory(uint32_t height, uint32_t width);
  virtual ~ImageFactory();
  ImageRead *GetImageFormat(std::string format);

private:
  uint32_t image_height_;
  uint32_t image_width_;
};



