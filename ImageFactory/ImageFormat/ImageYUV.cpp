#pragma once

#include "ImageYUV.h"

ImageYUV::ImageYUV(uint32_t height, uint32_t width) : image_height_(height),
                                                      image_width_(width), ImageRead() {
  image_size_ = image_height_ * 3 / 2 * image_width_;
  image_ = new cv::Mat(height * 3 / 2, width, CV_8UC1);
  image_data_ = new char[image_size_];
  if(!(image_ && image_data_)) {
    std::cout << "The YUV construct is error!" << std::endl;
    return;
  }
}

bool ImageYUV::ReadImage(std::string file_path) {
  fp_.open(file_path, std::ifstream::binary);
  if(fp_.fail()) {
    std::cout << "The file " << file_path << "is error!" << std::endl;
    return false;
  }
  fp_.read(image_data_, image_size_);
  image_->data = (unsigned char *) image_data_;
  cv::cvtColor(*image_, bmp_image_, cv::COLOR_YUV2BGR_I420);
  return  true;
}

ImageYUV::~ImageYUV() {
  if(image_) {
    delete image_;
    image_ = nullptr;
  }

  if(image_data_) {
    delete[]image_data_;
    image_data_ = nullptr;
  }

  if(fp_) {
    fp_.close();
  }
}