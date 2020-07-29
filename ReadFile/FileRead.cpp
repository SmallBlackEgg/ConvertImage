#include "FileRead.h"

FileRead::FileRead(uint32_t height, uint32_t width) {
  image_adapter_ = std::make_shared<ImageFactory>(height, width);
  image_read_ = image_adapter_->GetImageFormat(format_);
}

int FileRead::FileNameFilter(const struct dirent *cur_dir) {
  std::string file_name(cur_dir->d_name);
  if(file_name.find("." + format_) != std::string::npos) {
    return 1;
  }
  return 0;
}

void FileRead::Run(std::string file_path) {

  int n = scandir(file_path.c_str(), &file_name_list_, FileNameFilter, alphasort);
  if(n < 0) {
    std::cout << "Read file name is error!" << std::endl;
  }
  std::string full_path;
  bool is_read_success;
  for(int i = 0; i < n; i++) {
    std::cout << file_name_list_[i]->d_name << std::endl;
    full_path = file_path + file_name_list_[i]->d_name;
    is_read_success = image_read_->ReadImage(full_path);
    if(is_read_success)
    {
      cv::imshow("main", image_read_->GetImage());
    } else{
      std::cout << "Read Image is error!" << std::endl;
      return;
    }
    free(file_name_list_[i]);
  }
  free(file_name_list_);
}