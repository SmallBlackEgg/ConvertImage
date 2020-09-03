#pragma once
#include <fstream>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
class FileWrite {
public:
  FileWrite(uint32_t height, uint32_t width, std::string format);
  ~FileWrite();
  void Write(cv::Mat &image, uint32_t size, std::string file_path);

private:
  uint32_t image_size_;
  uint32_t height_;
  uint32_t width_;
  std::string format_;
};
