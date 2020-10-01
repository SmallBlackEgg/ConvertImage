#include <iostream>
#include "benchmark.h"
#include <dirent.h>
#include <vector>

struct dirent **g_file_name_list;
std::vector<std::string> g_file_path_vec;
std::vector<std::string> g_file_name_vec;
std::string g_format = "yuv";
const std::string g_file_path_in= "../test_data/yuv420/";

static void PreProcessFileByReadDir(benchmark::State &state) {
  for(auto _ : state){
    DIR *dir = nullptr;
    struct dirent * g_file_name_list;
    dir = opendir(g_file_path_in.c_str());
    while ((g_file_name_list = readdir(dir)) != nullptr)
    {
      std::string full_file_path = g_file_path_in + g_file_name_list->d_name;
      if(full_file_path.find(".yuv") != std::string::npos){
        g_file_name_vec.emplace_back(g_file_name_list->d_name);
        g_file_path_vec.emplace_back(std::move(full_file_path));
      }
    }
    std::sort(g_file_name_vec.begin(), g_file_name_vec.end());
    std::sort(g_file_path_vec.begin(), g_file_path_vec.end());

    state.PauseTiming();
    std::vector<std::string> empty_temp1;
    std::vector<std::string> empty_temp2;
    g_file_path_vec.swap(empty_temp1);
    g_file_name_vec.swap(empty_temp2);
    state.ResumeTiming();
  }
}


int FileNameFilter(const struct dirent *cur_dir) {
  std::string g_file_name(cur_dir->d_name);
  if(g_file_name.find("." + g_format) != std::string::npos) {
    return 1;
  }
  return 0;
}

void PreProcessFileByScanDir(benchmark::State &state) {
  for(auto _ : state)
  {
    uint32_t file_count= scandir(g_file_path_in.c_str(), &g_file_name_list, FileNameFilter, alphasort);
    if(file_count < 0) {
      std::cout << __FILE_NAME__ << ":" << __LINE__ << ":Read file name is error!" << std::endl;
    }
    std::string full_path;
    for(uint32_t i = 0; i < file_count; i++) {
      full_path = g_file_path_in + std::string(g_file_name_list[i]->d_name);
      g_file_path_vec.emplace_back(std::move(full_path));
      g_file_name_vec.emplace_back(g_file_name_list[i]->d_name);
      free(g_file_name_list[i]);
    }
    free(g_file_name_list);

    state.PauseTiming();
    std::vector<std::string> empty_temp1;
    std::vector<std::string> empty_temp2;
    g_file_path_vec.swap(empty_temp1);
    g_file_name_vec.swap(empty_temp2);
    state.ResumeTiming();
  }

}

void PreProcessFileTestByPipe(benchmark::State &state) {
  for(auto _ : state)
  {
    char file_name[256]={0};
    char cmd_buf[256]={0};
    FILE *pipe_ptr = nullptr;
    sprintf(cmd_buf,"ls %s | sort -t \"_\" -k3 -n", g_file_path_in.c_str());

    if((pipe_ptr=popen(cmd_buf,"r"))==NULL)
    {
      std::cout<<"pipe create error"<<std::endl;
      return;
    }

    while(fgets(file_name, 256, pipe_ptr)) {
      std::string full_file_path = g_file_path_in + file_name;
      if(full_file_path.find(".yuv") != std::string::npos)
      {
        g_file_name_vec.emplace_back(file_name);
        g_file_path_vec.emplace_back(std::move(full_file_path.substr(0, full_file_path.size() - 1)));
      }
    }
    pclose(pipe_ptr);

    state.PauseTiming();
    std::vector<std::string> empty_temp1;
    std::vector<std::string> empty_temp2;
    g_file_path_vec.swap(empty_temp1);
    g_file_name_vec.swap(empty_temp2);
    state.ResumeTiming();
  }
}

BENCHMARK(PreProcessFileByReadDir)->Iterations(1000);
BENCHMARK(PreProcessFileByScanDir)->Iterations(1000);
BENCHMARK(PreProcessFileTestByPipe)->Iterations(1000);

BENCHMARK_MAIN();
