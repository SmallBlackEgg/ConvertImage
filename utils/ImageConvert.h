#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
class ImageConvert
{
public:
  cv::Mat& GetImageByFormat(cv::Mat &image, const std::string &format);

private:
  cv::Mat& BGR2YUV(cv::Mat &image);
  //TODO:The quality will transport by config
  cv::Mat& BGR2JPG(cv::Mat &image, uint32_t quality = 95);
};