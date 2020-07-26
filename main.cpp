#include "ImageRead.h"
#include "ImageFormat/ImageBMP.h"
#include "ImageFormat/ImageYUV.h"
int main()
{
  ImageRead *test;
  ImageBMP bmp(1208, 1920);
  ImageYUV yuv(1208, 1920);
//  test = &bmp;
//  test->ReadImage("/Users/majiali/code/ConvertImage/data/bmp_big/nm_000001_00000021_08/frame_vc1_00.bmp");
  test = &yuv;
  test->ReadImage("/Users/majiali/code/ConvertImage/data/yuv/nm_000001_00000021_08/frame_vc1_03.yuv");

  cv::Mat image = test->GetImage();
  cv::imshow("main", image);
  cv::waitKey(0);
  return 0;
}

