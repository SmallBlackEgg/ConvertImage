#pragma once

#include "FileWrite.h"
#include "ImageFactory.h"
#include <dirent.h>
#include <iostream>
#include <thread>
#include <vector>

class FileRead {
public:
  FileRead();
  void Run();

private:
  virtual void Init();
  void PreProcessFile();
  void ThreadRead();
  virtual void Read(uint32_t start, uint32_t file_num);
  // TODO : How to deliver this format？
  static int FileNameFilter(const struct dirent *cur_dir);

protected:
  uint32_t thread_num_;
  static std::string format_;
  std::shared_ptr<ImageFactory> image_adapter_;
  std::vector<std::string> file_path_list_;

private:
  std::shared_ptr<FileWrite> file_write_;
  ImageRead *image_read_;
  std::string file_path_in_;
  std::string file_path_out_;
  std::string format_out_;
  struct dirent **file_name_list_;
  std::vector<std::string> file_name_;
  std::vector<std::thread> thread_vec_;
};
