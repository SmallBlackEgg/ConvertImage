#pragma once
#include <iostream>
#include <opencv2/highgui.hpp>
#include "FileRead.h"

class LiveYUV : public FileRead{
public:
  LiveYUV(const char *file_path);
  ~LiveYUV(){}
  LiveYUV(){}
private:
  void Init() override;
  void Read(uint32_t  start, uint32_t file_num) override;
  void Run() override;
private:
  ImageRead *image_read_;
  uint32_t image_width_;
  uint32_t image_height_;
};