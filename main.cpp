#include "FileRead.h"
#include <iostream>

std::string FileRead::format_ = "bmp";

int main() {
  FileRead test(1208, 1920, 3, "/Users/majiali/code/ConvertImage/data/bmp_big/nm_000001_00000021_08/",
                "/Users/majiali/code/ConvertImage/cmake-build-debug/",
                "yuv");
  test.PreProcessFile();
  test.ThreadRead();
  return 0;
}
