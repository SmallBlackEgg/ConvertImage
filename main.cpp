#include "FileRead.h"
#include "LiveImage/LiveYuv.h"
#include "parser.h"
#include <iostream>

int main(int argc, char *argv[]) {

  if (argc != 2) {
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ":The parameter is error!"
              << std::endl;
    return -1;
  }
  std::string arg = argv[1];
  std::size_t pos = arg.find("--");
  if (pos == std::string::npos) {
    std::cout << __FILE_NAME__ << ":" << __LINE__
              << ":The command line is error!" << std::endl;
    return -1;
  }
  arg = arg.substr(pos + 2);
  std::size_t equal_pos = arg.find_first_of("=");
  if (equal_pos == std::string::npos || equal_pos == 0 ||
      (equal_pos >= arg.length() - 1)) {
    std::cout << __FILE_NAME__ << ":" << __LINE__
              << ":The command line is error!" << std::endl;
    return -1;
  }
  std::string run_flag = arg.substr(0, equal_pos);
  std::string file_path = arg.substr(equal_pos + 1);
  bool is_convert = true;
  if (run_flag.compare("live") == 0) {
    is_convert = false;
  } else if (run_flag.compare("convert") == 0) {
    is_convert = true;
  }
  if (!ParserConfig::GetInstance().ParseConfigFile(file_path)) {
    std::cout << __FILE_NAME__ << ":" << __LINE__
              << ":The config parse is failed!" << std::endl;
    return -1;
  }

  FileRead *file_read_ptr = nullptr;
  if (is_convert) {
    file_read_ptr = new FileRead();
  } else {
    file_read_ptr = new LiveYUV(
        RunTimeConfig::GetInstance().GetConvertConfig().file_path_in);
  }
  file_read_ptr->Run();
  delete file_read_ptr;
  return 0;
}
