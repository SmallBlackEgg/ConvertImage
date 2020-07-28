#pragma once

#include <dirent.h>
#include <iostream>
#include "ImageFactory.h"
class FileRead {
public:
  FileRead(uint32_t height, uint32_t width);
  void Run(std::string file_path);

private:
  //TODO : How to deliver this format？
  static int FileNameFilter(const struct dirent *cur_dir);
private:
  std::shared_ptr<ImageFactory> image_adapter_;
  ImageRead *image_read_;
  static std::string format_;
  struct dirent **file_name_list_;
};



