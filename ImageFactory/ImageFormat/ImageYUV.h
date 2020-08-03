#include "ImageRead.h"
#include <opencv2/imgproc.hpp>
#include <fstream>
#include <iostream>

class ImageYUV: public ImageRead{
public:
  ImageYUV(uint32_t height, uint32_t width);
  ~ImageYUV();

  bool ReadImage(std::string file_path) override;
  cv::Mat& GetImage() override {return bmp_image_;}

private:
  cv::Mat *image_;
  cv::Mat bmp_image_;
  std::ifstream fp_;
  uint32_t image_height_;
  uint32_t image_width_;
  uint32_t image_size_;
  unsigned char *image_data_;
};