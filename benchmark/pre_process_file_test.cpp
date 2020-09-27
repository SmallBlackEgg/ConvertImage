#include <iostream>
#include "benchmark.h"
#include <dirent.h>
#include <vector>

const std::string file_path_in1_= "/Users/majiali/code/ConvertImage/cmake-build-debug/";
std::vector<std::string> file_name1_;
std::vector<std::string> file_path_list1_;

static void PreProcessFileTest1(benchmark::State &state) {
  for(auto _ : state){
    DIR *dir = nullptr;
    struct dirent * file_name_list;
    dir = opendir(file_path_in1_.c_str());
    while ((file_name_list = readdir(dir)) != nullptr)
    {
      std::string full_file_path = file_path_in1_ + file_name_list->d_name;
      if(full_file_path.find(".yuv") != std::string::npos){
        file_name1_.emplace_back(file_name_list->d_name);
        file_path_list1_.emplace_back(std::move(full_file_path));
      }
    }
    std::sort(file_name1_.begin(), file_name1_.end());
    std::sort(file_path_list1_.begin(), file_path_list1_.end());

    state.PauseTiming();
    std::vector<std::string> empty_temp1;
    std::vector<std::string> empty_temp2;
    file_path_list1_.swap(empty_temp1);
    file_name1_.swap(empty_temp2);
    file_name1_.clear();
    file_path_list1_.clear();
    state.ResumeTiming();
  }
}

BENCHMARK(PreProcessFileTest1)->Iterations(10000);


struct dirent **file_name_list_;
std::vector<std::string> file_path_list_;
std::vector<std::string> file_name_;
const std::string file_path_in_= "/Users/majiali/code/ConvertImage/cmake-build-debug/";

std::string format_ = "yuv";
int FileNameFilter(const struct dirent *cur_dir) {
  std::string file_name(cur_dir->d_name);
  if(file_name.find("." + format_) != std::string::npos) {
    return 1;
  }
  return 0;
}


void PreProcessFile(benchmark::State &state) {
  for(auto _ : state)
  {
    uint32_t file_count= scandir(file_path_in_.c_str(), &file_name_list_, FileNameFilter, alphasort);
    if(file_count < 0) {
      std::cout << __FILE_NAME__ << ":" << __LINE__ << ":Read file name is error!" << std::endl;
    }
    std::string full_path;
    for(uint32_t i = 0; i < file_count; i++) {
      full_path = file_path_in_ + std::string(file_name_list_[i]->d_name);
      file_path_list_.emplace_back(std::move(full_path));
      file_name_.emplace_back(file_name_list_[i]->d_name);
      free(file_name_list_[i]);
    }
    free(file_name_list_);
  }

}
BENCHMARK(PreProcessFile)->Iterations(10000);

const std::string file_path_in= "/Users/majiali/code/ConvertImage/cmake-build-debug/";
std::vector<std::string> file_name_v;
std::vector<std::string> file_path_list;
void PreProcessFileTest2(benchmark::State &state) {
  for(auto _ : state)
  {
    char file_name[256]={0};
    char cmd_buf[256]={0};
    FILE *pipe_ptr = nullptr;
    sprintf(cmd_buf,"ls %s | sort -t \"_\" -k3 -n", file_path_in.c_str());

    if((pipe_ptr=popen(cmd_buf,"r"))==NULL)
    {
      std::cout<<"pipe create error"<<std::endl;
      return;
    }

    while(fgets(file_name, 256, pipe_ptr)) {
      std::string full_file_path = file_path_in + file_name;
      if(full_file_path.find(".yuv") != std::string::npos)
      {
        file_name_v.emplace_back(file_name);
        file_path_list.emplace_back(std::move(full_file_path.substr(0, full_file_path.size() - 1)));
      }
    }
    fclose(pipe_ptr);
  }
}

BENCHMARK(PreProcessFileTest2)->Iterations(10000);
BENCHMARK(PreProcessFileTest2)->Iterations(10000);

BENCHMARK_MAIN();
