#pragma once

#include <dirent.h>
#include <iostream>
#include <vector>
#include <thread>
#include "ImageFactory.h"
#include "FileWrite.h"

class FileRead {
public:
  FileRead(uint32_t height, uint32_t width, uint32_t thread_num, const char *file_path_in, const char *file_path_out, const char *format_out);
  void PreProcessFile();
  void ThreadRead();
  static void Read(uint32_t  start, uint32_t file_num, FileRead *this_ptr);
private:
  //TODO : How to deliver this format？
  static int FileNameFilter(const struct dirent *cur_dir);
private:
  std::shared_ptr<ImageFactory> image_adapter_;
  std::shared_ptr<FileWrite> file_write_;
  ImageRead *image_read_;
  static std::string format_;
  std::string file_path_in_;
  std::string file_path_out_;
  std::string format_out_;
  struct dirent **file_name_list_;
  std::vector<std::string> file_path_list_;
  std::vector<std::string> file_name_;
  std::vector<std::thread> thread_vec_;
  uint32_t thread_num_;
};



