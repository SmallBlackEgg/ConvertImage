#pragma once

#include "json/value.h"
#include <cstring>
#include <iostream>

#define MAX_STRING_SIZE 256

typedef struct Convert {
  char file_path_in[MAX_STRING_SIZE];
  char file_path_out[MAX_STRING_SIZE];
  char convert_in[MAX_STRING_SIZE];
  char convert_out[MAX_STRING_SIZE];
  bool is_yuv420 = false;
  bool is_cut = false;
  bool is_resize = false;
  uint32_t thread_num = 1;
  uint32_t image_height = 0;
  uint32_t image_width = 0;
} ConvertConfig;

typedef struct Cut {
  uint32_t bottom = 0;
  uint32_t left = 0;
  uint32_t right = 0;
  uint32_t top = 0;
} CutConfig;

typedef struct Resize {
  uint32_t height = 0;
  uint32_t width = 0;
} ResizeConfig;

class RunTimeConfig {
public:
  static RunTimeConfig &GetInstance();
  ConvertConfig &GetConvertConfig();
  CutConfig &GetCutConfig();
  ResizeConfig &GetResizeConfig();
  bool SetConvertConfig(Json::Value &root);
  bool SetCutConfig(Json::Value &root);
  bool SetResizeConfig(Json::Value &root);

private:
  RunTimeConfig() = default;
  ConvertConfig convert_config_;
  CutConfig cut_config_;
  ResizeConfig resize_config_;
};

class ParserConfig {
public:
  bool ParseConfigFile(const std::string &file_path);
  static ParserConfig &GetInstance();

private:
  ParserConfig() = default;
  void ReadJsonFile(const std::string &file_path, Json::Value &root);
  bool is_parse_;
};
