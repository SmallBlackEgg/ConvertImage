#include <iostream>
#include "ImageBMP.h"

ImageBMP::ImageBMP(uint32_t height, uint32_t width):ImageRead() {
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

bool ImageBMP::ReadImage(std::string file_path) {
  *image_ = cv::imread(file_path, cv::IMREAD_UNCHANGED);
  if(!image_)
  {
    std::cout << "Read BMP Image is error!" << std::endl;
    return false;
  }
  return true;
}