#include "ImageFactory.h"
#include <iostream>
int main()
{
  ImageFactory image_adapter(1208, 1920);
  ImageRead *image_ptr = image_adapter.GetImageFormat("yuv");
  bool is_success = image_ptr->ReadImage("/Users/majiali/code/ConvertImage/data/yuv/nm_000001_00000021_08/frame_vc1_00.yuv");
  if (is_success)
  {
    cv::imshow("main", image_ptr->GetImage());
    cv::waitKey(0);
    return 0;
  }
  else{
    std::cout << "Read File is error!" << std::endl;
    return 0;
  }
}

