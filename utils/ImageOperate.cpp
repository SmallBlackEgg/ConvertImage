#include "ImageOperate.h"
#include <opencv2/imgproc.hpp>
namespace utils{

cv::Mat &ImageCut(cv::Mat &image, uint32_t top, uint32_t bottom, uint32_t left, uint32_t right)
{
  cv::Rect target_rect(left, top, image.cols - left -right, image.rows - top -bottom);
  image = image(target_rect);
  return image;
}

cv::Mat &ImageResize(cv::Mat &image, uint32_t width, uint32_t height)
{
  cv::resize(image, image, cv::Size(width, height));
  return image;
}

}
