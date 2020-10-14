#pragma once
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace utils {
class ImageConvert {
public:
  void GetImageByFormat(cv::Mat &image_input, cv::Mat &image_output, const std::string &format);

private:
  void YUV420toNV12(unsigned char *i420_data, unsigned char *nv12_data,
                    uint32_t width, uint32_t height);
  cv::Mat &BGR2YUV(cv::Mat &image);
  // TODO:The quality will transport by config
  cv::Mat &BGR2JPG(cv::Mat &image, uint32_t quality = 95);
};
} // namespace utils