#include "FileOperate.h"

std::mutex g_lock;

FileOperate::FileOperate(uint32_t height, uint32_t width, uint32_t thread_num): thread_num_(thread_num) {
  image_adapter_ = std::make_shared<ImageFactory>(height, width);
  image_read_ = image_adapter_->GetImageFormat(format_);

  //TODO:How to reasonably open up space？
  file_path_list_.reserve(100);
}

int FileOperate::FileNameFilter(const struct dirent *cur_dir) {
  std::string file_name(cur_dir->d_name);
  if(file_name.find("." + format_) != std::string::npos) {
    return 1;
  }
  return 0;
}

void FileOperate::Read(uint32_t start, uint32_t file_num, FileOperate *this_ptr) {
  std::atomic_bool is_read_success(false);
  for(uint32_t i = start; i < start + file_num; i++)
  {
    is_read_success = this_ptr->image_read_->ReadImage(this_ptr->file_path_list_[i]);
    static uint32_t frame = 0;
    char file_name[16] = {};
    sprintf(file_name, "./%d.bmp",frame++);
    if(is_read_success)
    {
      std::lock_guard<std::mutex> lock(g_lock);
      cv::Mat image = this_ptr->image_read_->GetImage();
      cv::imwrite(file_name,this_ptr->image_read_->GetImage());
    } else{
      std::cout << "Read Image " << this_ptr->file_path_list_[i] <<" is error!" << std::endl;
      return;
    }
  }
}

void FileOperate::ThreadRead() {
  uint32_t file_count = file_path_list_.size();
  uint32_t per_thread_file_num = file_count / thread_num_;
  uint32_t last_thread_read = 0;
  uint32_t start_read = 0;
  last_thread_read = file_count % thread_num_;
  for (uint32_t i = 0; i < thread_num_; i++)
  {
    std::thread thread_func = std::thread(&FileOperate::Read, start_read, per_thread_file_num, this);
    thread_vec_.emplace_back(std::move(thread_func));
    start_read += per_thread_file_num;
  }
  if(last_thread_read != 0)
  {
    std::thread thread_func = std::thread(&FileOperate::Read, start_read, last_thread_read, this );
    thread_vec_.emplace_back(std::move(thread_func));
  }
  std::for_each(thread_vec_.begin(), thread_vec_.end(), std::mem_fn(&std::thread::join));
}

void FileOperate::PreProcessFile(const char *file_path) {

  uint32_t file_count= scandir(file_path, &file_name_list_, FileNameFilter, alphasort);
  if(file_count < 0) {
    std::cout << "Read file name is error!" << std::endl;
  }
  std::string full_path;
  for(uint32_t i = 0; i < file_count; i++) {
    std::cout << file_name_list_[i]->d_name << std::endl;
    full_path = file_path + std::string(file_name_list_[i]->d_name);
    file_path_list_.emplace_back(std::move(full_path));
    free(file_name_list_[i]);
  }
  free(file_name_list_);
}