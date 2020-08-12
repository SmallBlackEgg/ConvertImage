#include "FileRead.h"
#include <iostream>
#include "utils/ImageOperate.h"
std::string FileRead::format_ = "yuv";

int main() {
  FileRead test(1208, 1920, 3, "/Users/majiali/code/ConvertImage/cmake-build-debug/",
                "/Users/majiali/code/ConvertImage/cmake-build-debug/",
                "bmp");
  test.PreProcessFile();
  test.ThreadRead();
  return 0;
}