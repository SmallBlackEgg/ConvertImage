#include "parser.h"
#include "json/json.h"
#include <fstream>

bool GetBoolValue(Json::Value &value, bool *result) {
  if (value.type() != Json::booleanValue) {
    if (value.type() == Json::nullValue) {
      *result = false;
      return true;
    }
    return false;
  }
  *result = value.asBool();
  return true;
}

bool GetIntValue(Json::Value &value, uint32_t *result) {
  if (value.type() != Json::intValue) {
    return false;
  }

  *result = static_cast<int>(value.asLargestInt());
  return true;
}

bool GetStringValue(Json::Value &value, unsigned int buf_size, char *result) {
  if (value.type() != Json::stringValue || value.asString().empty() ||
      value.asString().size() >= buf_size) {
    return false;
  }

  strcpy(result, value.asString().c_str());
  return true;
}

ConvertConfig &RunTimeConfig::GetConvertConfig() { return convert_config_; }

CutConfig &RunTimeConfig::GetCutConfig() { return cut_config_; }

ResizeConfig &RunTimeConfig::GetResizeConfig() { return resize_config_; }

RunTimeConfig &RunTimeConfig::GetInstance() {
  static RunTimeConfig config;
  static bool is_initialized = false;
  if (!is_initialized) {
    is_initialized = true;
    memset(&config, 0, sizeof(RunTimeConfig));
  }
  return config;
}

bool ParserConfig::SetConvertConfig(Json::Value &root) {
  return GetStringValue(
             root["convert"]["file_path_in"], MAX_STRING_SIZE,
             RunTimeConfig::GetInstance().GetConvertConfig().file_path_in) &&
         GetStringValue(
             root["convert"]["file_path_out"], MAX_STRING_SIZE,
             RunTimeConfig::GetInstance().GetConvertConfig().file_path_out) &&
         GetStringValue(
             root["convert"]["convert_in"], MAX_STRING_SIZE,
             RunTimeConfig::GetInstance().GetConvertConfig().convert_in) &&
         GetStringValue(
             root["convert"]["convert_out"], MAX_STRING_SIZE,
             RunTimeConfig::GetInstance().GetConvertConfig().convert_out) &&
         GetIntValue(
             root["convert"]["image_height"],
             &(RunTimeConfig::GetInstance().GetConvertConfig().image_height)) &&
         GetIntValue(
             root["convert"]["image_width"],
             &(RunTimeConfig::GetInstance().GetConvertConfig().image_width)) &&
         GetBoolValue(
             root["convert"]["is_yuv420"],
             &(RunTimeConfig::GetInstance().GetConvertConfig().is_yuv420)) &&
         GetBoolValue(
             root["convert"]["is_cut"],
             &(RunTimeConfig::GetInstance().GetConvertConfig().is_cut)) &&
         GetBoolValue(
             root["convert"]["is_resize"],
             &(RunTimeConfig::GetInstance().GetConvertConfig().is_resize)) &&
         GetIntValue(
             root["convert"]["thread_num"],
             &(RunTimeConfig::GetInstance().GetConvertConfig().thread_num));
}

bool ParserConfig::SetCutConfig(Json::Value &root) {
  return GetIntValue(root["cut"]["bottom"],
                     &(RunTimeConfig::GetInstance().GetCutConfig().bottom)) &&
         GetIntValue(root["cut"]["left"],
                     &(RunTimeConfig::GetInstance().GetCutConfig().left)) &&
         GetIntValue(root["cut"]["right"],
                     &(RunTimeConfig::GetInstance().GetCutConfig().right)) &&
         GetIntValue(root["cut"]["top"],
                     &(RunTimeConfig::GetInstance().GetCutConfig().top));
}

bool ParserConfig::SetResizeConfig(Json::Value &root) {
  return GetIntValue(
             root["resize"]["height"],
             &(RunTimeConfig::GetInstance().GetResizeConfig().height)) &&
         GetIntValue(root["resize"]["width"],
                     &(RunTimeConfig::GetInstance().GetResizeConfig().width));
}

ParserConfig &ParserConfig::GetInstance() {
  static ParserConfig config;
  static bool is_initialized = false;
  if (!is_initialized) {
    is_initialized = true;
    memset(&config, 0, sizeof(ParserConfig));
  }
  return config;
}

void ParserConfig::ReadJsonFile(const std::string &file_path,
                                Json::Value &root) {
  std::ifstream fp(file_path);
  if (fp.fail()) {
    std::cout << __FILE_NAME__ << ":" << __LINE__
              << ":The config path is error!" << std::endl;
    return;
  }
  Json::CharReaderBuilder builder;
  JSONCPP_STRING errors;
  if (!parseFromStream(builder, fp, &root, &errors)) {
    std::cout << errors << std::endl;
    return;
  }
  return;
}

bool ParserConfig::ParseConfigFile(const std::string &file_path) {
  if (is_parse_) {
    std::cout << __FILE__ << ":" << __LINE__ << ":The config file is parsed!"
              << std::endl;
    return false;
  }
  is_parse_ = true;
  Json::Value root;
  ReadJsonFile(file_path, root);

  return SetConvertConfig(root) && SetCutConfig(root) && SetResizeConfig(root);
}