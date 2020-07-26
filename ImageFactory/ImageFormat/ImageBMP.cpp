#include <iostream>
#include "ImageBMP.h"

ImageBMP::ImageBMP(uint32_t height, uint32_t width):ImageRead(height, width) {
  image_ = new cv::Mat(height, width, CV_8UC3);
  if(!image_)
  {
    std::cout << "Alloc BMP image is error" << std::endl;
    return;
  }
}

ImageBMP::~ImageBMP() {
  if(image_)
  {
    delete image_;
    image_ = nullptr;
  }
}

void ImageBMP::ReadImage(std::string file_path) {
  *image_ = cv::imread(file_path, cv::IMREAD_UNCHANGED);
}