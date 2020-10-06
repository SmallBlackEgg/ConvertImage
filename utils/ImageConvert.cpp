#include "ImageConvert.h"

using namespace utils;
// TODO: Modify file write instance
cv::Mat &ImageConvert::GetImageByFormat(cv::Mat &image,
                                        const std::string &format) {
  if (format == "yuv") {
    return BGR2YUV(image);
  } else if (format == "jpg") {
    return BGR2JPG(image);
  }
  std::cout << __FILE_NAME__ << ":" << __LINE__
            << ":Image convert format is error!" << std::endl;
  return image;
}

cv::Mat &ImageConvert::BGR2JPG(cv::Mat &image, uint32_t quality) {
  std::vector<uchar> buff;
  std::vector<int> params;
  params.push_back(cv::IMWRITE_JPEG_QUALITY);
  params.push_back(quality);
  cv::imencode(".jpg", image, buff, params);
  image = cv::imdecode(buff, -1);
  return image;
}

cv::Mat &ImageConvert::BGR2YUV(cv::Mat &image) {
  cv::cvtColor(image, image, cv::COLOR_BGR2YUV_I420);
  return image;
}