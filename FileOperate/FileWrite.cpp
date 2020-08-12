#include "FileWrite.h"

FileWrite::FileWrite(uint32_t height, uint32_t width, std::string format) : height_(height), width_(width),
                                                                            format_(format) {
  if(format_ == "yuv")
  {
    image_size_ = height_ * 3 / 2 * width_;
  } else if(format_ == "bmp"){
    image_size_ = height_ * width_ * 3;
  }
}

FileWrite::~FileWrite() {}

void FileWrite::Write(cv::Mat &image, uint32_t size, std::string file_path) {
  file_path = file_path.substr(0, file_path.length() - 3);
  file_path += format_;
  std::cout <<  __FILE_NAME__ << ":" << __LINE__ << ":" << file_path << std::endl;
  if(format_ == "yuv")
  {
    std::ofstream fp;
    fp.open(file_path, std::ofstream::binary);
    if(fp.fail())
    {
      std::cout << __FILE_NAME__ << ":" << __LINE__ << ":Write file is error!" << std::endl;
      fp.close();
      return;
    }
    cv::Mat bmp_image;
    cv::cvtColor(image, bmp_image, cv::COLOR_BGR2YUV_I420);
    fp.write((const char *)bmp_image.data, image_size_);
    fp.close();
  }
  else
  {
    cv::imwrite(file_path, image);
  }
}