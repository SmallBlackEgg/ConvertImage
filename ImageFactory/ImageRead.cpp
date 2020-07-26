#include "ImageRead.h"

ImageRead::ImageRead(uint32_t height, uint32_t width): image_height_(height), image_width_(width) {
//  image_ = new cv::Mat(image_height_, image_width_, CV_8UC3);
};

ImageRead::~ImageRead() {
//  if(image_)
//  {
//    delete image_;
//    image_ = nullptr;
//  }
}