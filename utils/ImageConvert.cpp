#include "ImageConvert.h"

using namespace utils;
// TODO: Modify file write instance
void ImageConvert::GetImageByFormat(cv::Mat &image_input, cv::Mat &image_output,
                                        const std::string &format) {
  if (format == "yuv420") {
    image_output = BGR2YUV(image_input);
    return;
  } else if (format == "jpg") {
    image_output = BGR2JPG(image_input);
    return;
  } else if (format == "nv12") {
    YUV420toNV12(BGR2YUV(image_input).data, image_output.data,
        image_input.cols, image_input.rows);
    return;
  }
  std::cout << __FILE_NAME__ << ":" << __LINE__
            << ":Image convert format is error!" << std::endl;
  return;
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

void ImageConvert::YUV420toNV12(unsigned char *i420_data, unsigned char *nv12_data,
                          uint32_t width, uint32_t height) {
  uint32_t Y_len = width * height;
  uint32_t U_len = Y_len / 4;

  memcpy(nv12_data, i420_data, Y_len);
  for (uint32_t i = 0; i < U_len; i++) {
    nv12_data[Y_len + 2 * i] = i420_data[Y_len + i];
    nv12_data[Y_len + 2 * i + 1] = i420_data[Y_len + U_len + i];
  }
}