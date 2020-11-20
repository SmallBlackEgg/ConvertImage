#include "FileRead.h"
#include "parser.h"
#include <unistd.h>
FileRead::FileRead() {}

std::string FileRead::
    format_; // https://en.cppreference.com/w/cpp/language/initialization

void FileRead::Init() {

  uint32_t image_height =
      RunTimeConfig::GetInstance().GetConvertConfig().image_height;
  uint32_t image_width =
      RunTimeConfig::GetInstance().GetConvertConfig().image_width;
  file_path_in_ = RunTimeConfig::GetInstance().GetConvertConfig().file_path_in;
  file_path_out_ =
      RunTimeConfig::GetInstance().GetConvertConfig().file_path_out;
  format_out_ = RunTimeConfig::GetInstance().GetConvertConfig().convert_out;
  thread_num_ = RunTimeConfig::GetInstance().GetConvertConfig().thread_num;
  format_ = RunTimeConfig::GetInstance().GetConvertConfig().convert_in;

  if (access(file_path_in_.c_str(), F_OK) != 0) {
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ":The file path in \""
              << file_path_in_.c_str() << "\" is not exist!" << std::endl;
    file_path_in_.clear();
    return;
  }
  if (access(file_path_out_.c_str(), F_OK) != 0) {
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ":The file path out \""
              << file_path_out_.c_str() << "\" is not exist!" << std::endl;
    file_path_out_.clear();
    return;
  }

  file_path_in_ += "/";
  file_path_out_ += "/";

  image_adapter_ = std::make_shared<ImageFactory>(image_height, image_width);
  file_write_ =
      std::make_shared<FileWrite>(image_height, image_width, format_out_);
  image_read_ = image_adapter_->GetImageFormat(format_);

  // TODO:How to reasonably open up space？
  file_path_list_.reserve(100);
  file_name_.reserve(100);
}

int FileRead::FileNameFilter(const struct dirent *cur_dir) {
  std::string file_name(cur_dir->d_name);
  if (file_name.find("." + format_) != std::string::npos) {
    return 1;
  }
  return 0;
}

int FileRead::FileSortById(const struct dirent **left_file, const struct dirent **right_file) {
  std::string left_file_name((*left_file)->d_name);
  std::string right_file_name((*right_file)->d_name);
  int32_t left_begin_pos = left_file_name.rfind('_') + 1;
  int32_t left_end_pos = left_file_name.rfind('.');
  int32_t right_begin_pos = right_file_name.rfind('_') + 1;
  int32_t right_end_pos = right_file_name.rfind('.');
  if(left_begin_pos == std::string::npos || left_end_pos == std::string::npos ||
      right_begin_pos == std::string::npos || right_end_pos == std::string::npos) {
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ":The file "
              << left_file_name.c_str() << " ----- " <<right_file_name.c_str() << " is not exist!" << std::endl;
  }

  if(std::atoi(left_file_name.substr(left_begin_pos, left_end_pos - left_begin_pos).c_str()) <
      std::atoi(right_file_name.substr(right_begin_pos, right_end_pos - right_begin_pos).c_str()))
  {
    return -1;
  }
  return 1;
}

/*
alpha source code 
int alphasort (const struct dirent **a, const struct dirent **b)
{
  return strcoll ((*a)->d_name, (*b)->d_name);
}
*/

void FileRead::Read(uint32_t start, uint32_t file_num) {
  bool is_read_success = false;
  cv::Mat bmp_image;
  for (uint32_t i = start; i < start + file_num; i++) {
    is_read_success = image_read_->ReadImage(file_path_list_[i], bmp_image);
    std::string out_file_path = file_path_out_ + file_name_[i];
    if (is_read_success) {
      file_write_->Write(bmp_image,
                         bmp_image.channels() * bmp_image.cols * bmp_image.rows,
                         out_file_path);
    } else {
      std::cout << __FILE_NAME__ << ":" << __LINE__ << ":Read Image "
                << file_path_list_[i] << " is error!" << std::endl;
      return;
    }
  }
}

void FileRead::ThreadRead() {
  uint32_t file_count = file_path_list_.size();
  uint32_t per_thread_file_num = file_count / thread_num_;
  uint32_t last_thread_read = 0;
  uint32_t start_read = 0;
  last_thread_read = file_count % thread_num_;
  for (uint32_t i = 0; i < thread_num_; i++) {
    std::thread thread_func =
        std::thread(&FileRead::Read, this, start_read, per_thread_file_num);
    thread_vec_.emplace_back(std::move(thread_func));
    start_read += per_thread_file_num;
  }
  if (last_thread_read != 0) {
    std::thread thread_func =
        std::thread(&FileRead::Read, this, start_read, last_thread_read);
    thread_vec_.emplace_back(std::move(thread_func));
  }
  std::for_each(thread_vec_.begin(), thread_vec_.end(),
                std::mem_fn(&std::thread::join));
}

bool FileRead::PreProcessFile() {
  if (file_path_in_.empty()) {
    return false;
  }
  uint32_t file_count = scandir(file_path_in_.c_str(), &file_name_list_,
                                FileNameFilter, FileSortById);//alphasort
  if (file_count < 0) {
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ":Read file name is error!"
              << std::endl;
  }
  std::string full_path;
  for (uint32_t i = 0; i < file_count; i++) {
    full_path = file_path_in_ + std::string(file_name_list_[i]->d_name);
    file_path_list_.emplace_back(std::move(full_path));
    file_name_.emplace_back(file_name_list_[i]->d_name);
    free(file_name_list_[i]);
  }
  free(file_name_list_);
  return true;
}

void FileRead::Run() {
  Init();
  if (!PreProcessFile()) {
    return;
  }
  ThreadRead();
}
