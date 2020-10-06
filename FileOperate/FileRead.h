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
  virtual void Run();
  virtual ~FileRead(){};

private:
  virtual void Init();
  void ThreadRead();
  virtual void Read(uint32_t start, uint32_t file_num);
  static int FileNameFilter(const struct dirent *cur_dir);

protected:
  static std::string format_;
  std::shared_ptr<ImageFactory> image_adapter_;
  std::vector<std::string> file_path_list_;
  std::vector<std::string> file_name_;
  std::string file_path_in_;
  bool PreProcessFile();

private:
  std::shared_ptr<FileWrite> file_write_;
  uint32_t thread_num_;
  ImageRead *image_read_;
  std::string file_path_out_;
  std::string format_out_;
  struct dirent **file_name_list_;
  std::vector<std::thread> thread_vec_;
};
