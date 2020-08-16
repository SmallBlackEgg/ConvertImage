#include "FileWrite.h"
#include "parser.h"

FileWrite::FileWrite(uint32_t height, uint32_t width, std::string format) : height_(height), width_(width),
                                                                            format_(std::move(format)) {
  if(format_ == "yuv")
  {
    image_size_ = height_ * 3 / 2 * width_;
  } else if(format_ == "bmp"){
    image_size_ = height_ * width_ * 3;
  }
}

FileWrite::~FileWrite() {}

static void YUV_420toNV12(unsigned char *i420_data, unsigned char *nv12_data, uint32_t width, uint32_t height)
{
  uint32_t Y_len = width * height;
  uint32_t U_len = Y_len / 4;

  memcpy(nv12_data, i420_data, Y_len);
  for(uint32_t i = 0; i < U_len; i++) {
    nv12_data[Y_len + 2 * i] = i420_data[Y_len + i];
    nv12_data[Y_len + 2 * i + 1] = i420_data[Y_len + U_len + i];
  }
}

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
    cv::Mat yuv_i420_image;
    cv::Mat yuv_nv12_image;
    cv::cvtColor(image, yuv_i420_image, cv::COLOR_BGR2YUV_I420);
    if(!RunTimeConfig::GetInstance().GetConvertConfig().is_yuv420){
      YUV_420toNV12(yuv_i420_image.data, yuv_nv12_image.data, yuv_i420_image.cols, yuv_i420_image.rows);
      fp.write((const char *)yuv_nv12_image.data, image_size_);
    } else{
      fp.write((const char *)yuv_i420_image.data, image_size_);
    }
    fp.close();
  }
  else
  {
    cv::imwrite(file_path, image);
  }
}