
#include "benchmark.h"
#include <fcntl.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <opencv2/highgui.hpp>

void WriteBmpByStream(const char *data, const char *file_path,
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

  std::ofstream fp(file_path);
  if (fp.fail()) {
    std::cout << "Open " << file_path << "is failed" << std::endl;
    return;
  }

  fp.write((const char *)bmp_file_header, 14);
  fp.write((const char *)bitmap_info_header, 40);

  for (uint32_t i = 0; i < image_height; i++) {
    // write row data from bottom to top
    fp.write(data + (image_width * (image_height - i - 1) * 3),
             bytes_of_per_pixel * image_width);
    // The bytes in each row must be divisible by 4.Indivisible, fill to
    // multiples of 4
    fp.write((const char *)fill_data,
             (4 - image_width * bytes_of_per_pixel % 4) % 4);
  }
  fp.close();
}

void WriteBmpByFd(const char *data, const char *file_path,
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
    std::cout << "Open " << file_path << " is failed" << std::endl;
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
  close(fd);
}

static void WriteImageByBinaryStream(benchmark::State &state) {
  cv::Mat image = cv::imread(
      "../test_data/bmp/frame_vc1_01.bmp");

  for (auto it : state) {
    WriteBmpByStream((const char *)image.data, "image_code_stream.bmp", 1920, 1208);
  }
}

static void WriteImageByBinaryFd(benchmark::State &state) {
  cv::Mat image = cv::imread(
      "../test_data/bmp/frame_vc1_01.bmp");

  for (auto it : state) {
    WriteBmpByFd((const char *)image.data, "image_code_fd.bmp", 1920, 1208);
  }
}

static void WriteImageByCv(benchmark::State &state) {
  cv::Mat image = cv::imread(
      "../test_data/bmp/frame_vc1_01.bmp");
  for (auto it : state) {
    cv::imwrite("image_cv.bmp", image);
  }
}

BENCHMARK(WriteImageByBinaryStream);
BENCHMARK(WriteImageByBinaryFd);
BENCHMARK(WriteImageByCv);
BENCHMARK_MAIN();