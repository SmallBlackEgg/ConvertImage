#include "ImageBMP.h"
#include <iostream>

ImageBMP::ImageBMP(uint32_t height, uint32_t width) : ImageRead() {}

ImageBMP::~ImageBMP() {}

bool ImageBMP::ReadImage(std::string file_path, cv::Mat &image) {
  image = cv::imread(file_path, cv::IMREAD_UNCHANGED);
  if (image.empty()) {
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ":Read BMP Image is error!"
              << std::endl;
    return false;
  }
  return true;
}