#include "overlay.h"

#include <climits>

#include <opencv2/imgproc.hpp>

#include "config.h"

namespace mt::overlay {

void draw(cv::Mat& frame, const cv::Rect& roi, State state, const cv::Rect& target) {
  cv::rectangle(frame, roi, config::kRoiColor, 1);
  if (state == State::Track) {
    cv::rectangle(frame, target, config::kTargetColor, 2);
  }
  const char* label = state == State::Track ? "TRACKING" : "SEARCHING";
  cv::putText(frame, label, {10, 25}, cv::FONT_HERSHEY_SIMPLEX, 0.7, config::kTargetColor, 2);
}

void drawContours(cv::Mat& frame, const motion::Contours& contours, const cv::Rect& roi) {
  cv::drawContours(frame, contours, -1, config::kContourColor, 2, cv::LINE_8, cv::noArray(), INT_MAX, roi.tl());
}

}
