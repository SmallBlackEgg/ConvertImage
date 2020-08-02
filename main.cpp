#include "FileOperate.h"
#include <iostream>
#include "utils/ImageConvert.h"

std::string FileOperate::format_ = "yuv";

int main() {
  FileOperate test(1208, 1920, 3);
  test.PreProcessFile("/Users/majiali/code/ConvertImage/data/yuv/nm_000001_00000021_08/");
  test.ThreadRead();

//  ImageConvert test;
//  cv::Mat image = cv::imread("/Users/majiali/code/ConvertImage/cmake-build-debug/1.bmp");
//  cv::Mat dest = test.GetImageByFormat(image, "jpg");
//  cv::imshow("dest", dest);
//  cv::waitKey(0);
  return 0;
}
