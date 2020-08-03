#pragma once
#include "ImageRead.h"

class ImageBMP: public ImageRead {
public:
  ImageBMP(uint32_t height, uint32_t width);
  ~ImageBMP();
  bool ReadImage(std::string file_path, cv::Mat &image) override ;
};



