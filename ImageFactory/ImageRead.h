#pragma once
#include <opencv2/highgui.hpp>

class ImageRead {
public:
  ImageRead(uint32_t height, uint32_t width);
  virtual ~ImageRead();

  virtual void ReadImage(std::string file_path) = 0;
  virtual cv::Mat& GetImage() = 0;
  ImageRead(const ImageRead&) = delete;
  ImageRead& operator=(const ImageRead&) = delete;
private:
  uint32_t image_height_;
  uint32_t image_width_;
  cv::Mat *image_;
};



