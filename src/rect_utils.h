#pragma once

#include <opencv2/core.hpp>

namespace mt::rect_utils {

// Centered box of config::kRoiSize, clamped to the frame.
cv::Rect centerRoi(const cv::Size& frameSize);

cv::Point center(const cv::Rect& rect);

double squaredDistance(const cv::Point& a, const cv::Point& b);

}
