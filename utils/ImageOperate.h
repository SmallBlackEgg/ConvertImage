#pragma once

#include <opencv2/highgui.hpp>

namespace utils{
  cv::Mat &ImageCut(cv::Mat &image, uint32_t top, uint32_t bottom, uint32_t left, uint32_t right);
  cv::Mat &ImageResize(cv::Mat &image, uint32_t width, uint32_t height);
}