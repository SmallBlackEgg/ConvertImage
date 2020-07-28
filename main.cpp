#include "FileRead.h"
#include <iostream>

std::string FileRead::format_ = "yuv";

int main()
{
 FileRead test(1208, 1920);
 test.Run("/Users/majiali/code/ConvertImage/data/yuv/nm_000001_00000021_08/");
  return  0;
}