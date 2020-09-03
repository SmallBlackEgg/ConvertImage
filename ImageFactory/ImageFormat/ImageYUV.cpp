#include "ImageYUV.h"
#include "parser.h"
#include <fstream>
#include <opencv2/imgproc.hpp>

static void NewHandler() {
  std::cout << __FILE_NAME__ << ":" << __LINE__ << ":Unable to new data!"
            << std::endl;
}

ImageYUV::ImageYUV(uint32_t height, uint32_t width)
    : image_height_(height), image_width_(width), ImageRead() {
  image_size_ = image_height_ * 3 / 2 * image_width_;
  std::set_new_handler(NewHandler);
}

bool ImageYUV::ReadImage(std::string file_path, cv::Mat &image) {
  std::ifstream fp(file_path, std::ifstream::binary);
  cv::Mat yuv_image(image_height_ * 3 / 2, image_width_, CV_8UC1);
  if (fp.fail()) {
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ":The file " << file_path
              << " is error!" << std::endl;
    fp.close();
    return false;
  }

  char *image_data = new char[image_size_];
  fp.read(image_data, image_size_);
  memcpy(yuv_image.data, image_data, image_size_);
  delete[] image_data;
  fp.close();

  if (!RunTimeConfig::GetInstance().GetConvertConfig().is_yuv420) {
    cv::cvtColor(yuv_image, image, cv::COLOR_YUV2BGR_NV12);
  } else {
    cv::cvtColor(yuv_image, image, cv::COLOR_YUV2BGR_I420);
  }
  return true;
}

ImageYUV::~ImageYUV() {}