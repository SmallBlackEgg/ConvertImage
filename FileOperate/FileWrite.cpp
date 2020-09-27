#include "FileWrite.h"
#include "parser.h"
#include "ImageOperate.h"
#include <fcntl.h>
#include <unistd.h>

static void WriteBmp(const char *data, const char *file_path,
                  const uint32_t image_width, const uint32_t image_height) {
  // Format:Little endian
  // BMP Header (14 bytes)
  const uint32_t bytes_of_per_pixel = 3;
  uint32_t image_size = 54 + image_height * image_width *
                             bytes_of_per_pixel; // 54 is image header size
  unsigned char bmp_file_header[14] = {0x42, 0x4d,   // BM
                                       0x00, 0x00, 0x00, 0x00, // image size
                                       0x00, 0x00, 0x00, 0x00, // reserved bytes
                                       0x36, 0x00, 0x00, 0x00}; // bmp offset
  bmp_file_header[2] = static_cast<unsigned char>(image_size);
  bmp_file_header[3] = static_cast<unsigned char>(image_size >> 8);
  bmp_file_header[4] = static_cast<unsigned char>(image_size >> 16);
  bmp_file_header[5] = static_cast<unsigned char>(image_size >> 24);

  // BitMap header(40 bytes)
  unsigned char bitmap_info_header[40] = {
      0x28, 0x00, 0x00, 0x00,  // bit map size
      0x00, 0x00, 0x00, 0x00,  // image_width
      0x00, 0x00, 0x00, 0x00,  // image_height
      0x01, 0x00,              // planes
      0x18, 0x00,              // bit count
      0x00, 0x00, 0x00, 0x00,  // bit compression 0 is not compression
      0x00, 0x00, 0x00, 0x00,  // bit size image
      0x00, 0x00, 0x00, 0x00,  // horizontal resolution
      0x00, 0x00, 0x00, 0x00,  // vertical resolution
      0x00, 0x00, 0x00, 0x00,  // color used
      0x00, 0x00, 0x00, 0x00}; // color improtant
  bitmap_info_header[4] = static_cast<unsigned char>(image_width);
  bitmap_info_header[5] = static_cast<unsigned char>(image_width >> 8);
  bitmap_info_header[6] = static_cast<unsigned char>(image_width >> 16);
  bitmap_info_header[7] = static_cast<unsigned char>(image_width >> 24);

  bitmap_info_header[8] = static_cast<unsigned char>(image_height);
  bitmap_info_header[9] = static_cast<unsigned char>(image_height >> 8);
  bitmap_info_header[10] = static_cast<unsigned char>(image_height >> 16);
  bitmap_info_header[11] = static_cast<unsigned char>(image_height >> 24);

  unsigned char fill_data[3] = {0x00, 0x00, 0x00}; // BGR

  uint32_t fd = open(file_path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    std::cout << "Open " << file_path << "is failed" << std::endl;
    return;
  }

  write(fd, &bmp_file_header, 14);
  write(fd, &bitmap_info_header, 40);

  for (uint32_t i = 0; i < image_height; i++) {
    // write row data from bottom to top
    write(fd, data + (image_width * (image_height - i - 1) * 3),
          bytes_of_per_pixel * image_width);
    // The bytes in each row must be divisible by 4.Indivisible, fill to
    // multiples of 4
    write(fd, fill_data,
          (4 - image_width * bytes_of_per_pixel % 4) % 4);
  }
}

FileWrite::FileWrite(uint32_t height, uint32_t width, std::string format)
    : height_(height), width_(width), format_(std::move(format)) {
  if (format_ == "yuv") {
    image_size_ = height_ * 3 / 2 * width_;
  } else if (format_ == "bmp") {
    image_size_ = height_ * width_ * 3;
  }
  cut_bottom_ = RunTimeConfig::GetInstance().GetCutConfig().bottom;
  cut_top_ = RunTimeConfig::GetInstance().GetCutConfig().top;
  cut_left_ = RunTimeConfig::GetInstance().GetCutConfig().left;
  cut_right_ = RunTimeConfig::GetInstance().GetCutConfig().right;
  resize_height_ = RunTimeConfig::GetInstance().GetResizeConfig().height;
  resize_width_ = RunTimeConfig::GetInstance().GetResizeConfig().width;
}

FileWrite::~FileWrite() {}

static void YUV_420toNV12(unsigned char *i420_data, unsigned char *nv12_data,
                          uint32_t width, uint32_t height) {
  uint32_t Y_len = width * height;
  uint32_t U_len = Y_len / 4;

  memcpy(nv12_data, i420_data, Y_len);
  for (uint32_t i = 0; i < U_len; i++) {
    nv12_data[Y_len + 2 * i] = i420_data[Y_len + i];
    nv12_data[Y_len + 2 * i + 1] = i420_data[Y_len + U_len + i];
  }
}

void FileWrite::Write(cv::Mat &image, uint32_t size, std::string file_path) {
  file_path = file_path.substr(0, file_path.length() - 3);
  file_path += format_;
  std::cout << __FILE_NAME__ << ":" << __LINE__ << ":" << file_path
            << std::endl;
  if(RunTimeConfig::GetInstance().GetConvertConfig().is_cut)
  {
    utils::ImageCut(image, cut_top_, cut_bottom_, cut_left_, cut_right_);
  }
  if(RunTimeConfig::GetInstance().GetConvertConfig().is_resize)
  {
    utils::ImageResize(image, resize_width_, resize_height_);
  }
  if (format_ == "yuv") {
    std::ofstream fp;
    fp.open(file_path, std::ofstream::binary);
    if (fp.fail()) {
      std::cout << __FILE_NAME__ << ":" << __LINE__ << ":Write file is error!"
                << std::endl;
      fp.close();
      return;
    }
    cv::Mat yuv_i420_image;
    cv::Mat yuv_nv12_image;
    cv::cvtColor(image, yuv_i420_image, cv::COLOR_BGR2YUV_I420);
    if (!RunTimeConfig::GetInstance().GetConvertConfig().is_yuv420) {
      YUV_420toNV12(yuv_i420_image.data, yuv_nv12_image.data,
                    yuv_i420_image.cols, yuv_i420_image.rows);
      fp.write((const char *)yuv_nv12_image.data, image_size_);
    } else {
      fp.write((const char *)yuv_i420_image.data, image_size_);
    }
    fp.close();
  } else {
    WriteBmp((const char *)image.data, file_path.c_str(), image.cols, image.rows);
  }
}