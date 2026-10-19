#include "motion_detector.h"

#include <limits>

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
  cv::GaussianBlur(roiFrame, blurred, kernel, 0);/*Blur averages each pixel with its neighbors. This hides tiny random noise from the camera sensor.*/
  subtractor.apply(blurred, mask);// each time done, it will learn what background anf foreground are
  cv::threshold(mask, mask, config::kMaskThreshold, 255, cv::THRESH_BINARY);
  cv::dilate(mask, mask, cv::Mat(), {-1, -1}, config::kDilateIterations);
  return mask;
}

Contours findMotionContours(const cv::Mat& mask) {
  Contours all;
  cv::findContours(mask, all, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

  Contours large;
  for (auto& contour : all) {
    if (cv::contourArea(contour) >= config::kMinContourArea) large.push_back(std::move(contour));
  }
  return large;
}

std::optional<cv::Rect> findCentralMotionBox(const Contours& contours, const cv::Size& maskSize) {
  const cv::Point maskCenter(maskSize.width / 2, maskSize.height / 2);
  std::optional<cv::Rect> best;
  double bestDistance = std::numeric_limits<double>::max();
  for (const auto& contour : contours) {
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
