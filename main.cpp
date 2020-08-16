#include "FileRead.h"
#include <iostream>
#include <parser.h>

int main(int argc, char * argv[]) {


  if(argc != 2)
  {
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ":The paramter is error!" << std::endl;
    return -1;
  }
  std::string config_path = argv[1];
  std::string config_flag = "--config_file=";
  if(config_path.find(config_flag))
  {
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ":The config file is error!" << std::endl;
    return -1;
  }
  else
  {
    std::string file_path = config_path.substr(config_flag.size());
    if(!ParserConfig::GetInstance().ParseConfigFile(file_path))
    {
      std::cout << __FILE_NAME__ << ":" << __LINE__ << ":The config parse is failed!" << std::endl;
      return -1;
    }

    FileRead test;

    test.Run();
  }

  return 0;
}