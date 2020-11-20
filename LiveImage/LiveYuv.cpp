#include "LiveYuv.h"
#include "parser.h"
#include <signal.h>
#include <unistd.h>
bool g_is_run = false;
static void SigHandler(int sig_num) {
  g_is_run = false;
  exit(sig_num);
}

LiveYUV::LiveYUV(const char *file_path) {
  signal(SIGINT, SigHandler);
  format_ = RunTimeConfig::GetInstance().GetConvertConfig().convert_in;
  image_height_ = RunTimeConfig::GetInstance().GetConvertConfig().image_height;
  image_width_ = RunTimeConfig::GetInstance().GetConvertConfig().image_width;
  file_path_in_ = file_path;
  if (access(file_path_in_.c_str(), F_OK) != 0) {
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ":The file path in \""
              << file_path_in_.c_str() << "\" is not exist!" << std::endl;
    file_path_in_.clear();
    return;
  }
  g_is_run = true;
  file_path_in_ += "/";
}

void LiveYUV::Init() {
  image_adapter_ = std::make_shared<ImageFactory>(image_height_, image_width_);
  image_read_ = image_adapter_->GetImageFormat(format_);
}

void LiveYUV::Read(uint32_t start, uint32_t file_num) {
  bool is_read_success = false;
  cv::Mat bmp_image;
  uint32_t i = start;
  int32_t base_line = 0;
  cv::namedWindow("LiveYuv", cv::WINDOW_AUTOSIZE);
  while (g_is_run) {
    is_read_success = image_read_->ReadImage(file_path_list_[i], bmp_image);
    cv::putText(bmp_image, file_name_[i], cv::Point(0, 40),
                cv::FONT_HERSHEY_COMPLEX, 1.0, cv::Scalar(0, 0, 255), 2);
    cv::imshow("LiveYuv", bmp_image);
    int key = cv::waitKeyEx(0);
#ifdef DARWIN
    if (key == 63232 || key == 63234) // 63232 is up, 63234 is left
    {
      if (i == 0) {
        i = file_path_list_.size();
      }
      i--;
    } else if (key == 63233 || key == 63235) // 63233 is down, 63235 is right
    {
      i++;
      if (i == file_path_list_.size()) {
        i = 0;
      }
    }
#endif
#ifdef LINUX
    if (key == 65361 || key == 65362) // 65362 is up, 65361 is left
    {
      if (i == 0) {
        i = file_path_list_.size();
      }
      i--;
    } else if (key == 65364 || key == 65363) // 65364 is down, 65363 is right
    {
      i++;
      if (i == file_path_list_.size()) {
        i = 0;
      }
    }
#endif
    else if (key == 27) {
      g_is_run = false;
    }
  }
  cv::destroyWindow("LiveYuv");
}

void LiveYUV::Run() {
  Init();
  if (!PreProcessFile()) {
    return;
  }
  for(auto it : file_path_list_)
  {
    std::cout << it << std::endl;
  }
  // The mac os can not support child thread create GUI
 Read(0, file_path_list_.size());
}
