#pragma once
#include "ImageRead.h"
#include <iostream>

class ImageYUV : public ImageRead {
public:
  ImageYUV(uint32_t height, uint32_t width);
  ~ImageYUV();

  bool ReadImage(std::string file_path, cv::Mat &image) override;

private:
  uint32_t image_height_;
  uint32_t image_width_;
  uint32_t image_size_;
};