#include "FileRead.h"
#include <iostream>

std::string FileRead::format_ = "bmp";

int main() {
  FileRead test(1208, 1920, 3);
  test.PreProcessFile("/Users/majiali/code/ConvertImage/data/bmp_big/nm_000001_00000021_08/");
  test.ThreadRead();
  return 0;
}
