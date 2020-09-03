#pragma once
#include <opencv2/highgui.hpp>

class ImageRead {
public:
  ImageRead();
  virtual ~ImageRead();
  virtual bool ReadImage(std::string file_path, cv::Mat &image) = 0;

  ImageRead(const ImageRead &) = delete;
  ImageRead &operator=(const ImageRead &) = delete;
};
