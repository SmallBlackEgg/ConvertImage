#include "ImageFactory.h"
#include "ImageFormat/ImageYUV.h"
#include "ImageFormat/ImageBMP.h"

ImageFactory::ImageFactory(uint32_t height, uint32_t width):image_height_(height), image_width_(width) {}

ImageFactory::~ImageFactory() {}

ImageRead * ImageFactory::GetImageFormat(std::string format) {
  if(format == "yuv")
  {
    return new ImageYUV(image_height_, image_width_);
  }
  else if(format == "bmp")
  {
    return new ImageBMP(image_height_, image_width_);
  }
  std::cout << "The format is error!" << std::endl;
  return nullptr;
}