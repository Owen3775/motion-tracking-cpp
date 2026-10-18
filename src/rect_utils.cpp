#include "rect_utils.h"

#include <algorithm>

#include "config.h"

namespace mt::rect_utils {

cv::Rect centerRoi(const cv::Size& frameSize) {
  const int width = std::min(config::kRoiSize, frameSize.width);
  const int height = std::min(config::kRoiSize, frameSize.height);
  return {(frameSize.width - width) / 2, (frameSize.height - height) / 2, width, height};
}

cv::Point center(const cv::Rect& rect) {
  return {rect.x + rect.width / 2, rect.y + rect.height / 2};
}

double squaredDistance(const cv::Point& a, const cv::Point& b) {
  const cv::Point delta = a - b;
  return static_cast<double>(delta.dot(delta));
}

}
