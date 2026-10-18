#include "motion_detector.h"

#include <limits>
#include <vector>

#include <opencv2/imgproc.hpp>
#if __has_include(<opencv2/geometry.hpp>)
#include <opencv2/geometry.hpp>  // OpenCV 5 moved contourArea/boundingRect here
#endif

#include "config.h"
#include "rect_utils.h"

namespace mt::motion {

cv::Ptr<cv::BackgroundSubtractor> createSubtractor() {
  return cv::createBackgroundSubtractorMOG2(config::kMogHistory, config::kMogVarThreshold, false);
}

cv::Mat motionMask(cv::BackgroundSubtractor& subtractor, const cv::Mat& roiFrame) {
  cv::Mat blurred;
  cv::Mat mask;
  const cv::Size kernel(config::kBlurKernelSize, config::kBlurKernelSize);
  cv::GaussianBlur(roiFrame, blurred, kernel, 0);
  subtractor.apply(blurred, mask);
  cv::threshold(mask, mask, config::kMaskThreshold, 255, cv::THRESH_BINARY);
  cv::dilate(mask, mask, cv::Mat(), {-1, -1}, config::kDilateIterations);
  return mask;
}

std::optional<cv::Rect> findCentralMotionBox(const cv::Mat& mask) {
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

  const cv::Point maskCenter(mask.cols / 2, mask.rows / 2);
  std::optional<cv::Rect> best;
  double bestDistance = std::numeric_limits<double>::max();
  for (const auto& contour : contours) {
    if (cv::contourArea(contour) < config::kMinContourArea) continue;
    const cv::Rect box = cv::boundingRect(contour);
    const double distance = rect_utils::squaredDistance(rect_utils::center(box), maskCenter);
    if (distance < bestDistance) {
      bestDistance = distance;
      best = box;
    }
  }
  return best;
}

}
