#include "debug_view.h"

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "config.h"

namespace mt::debug_view {

cv::Mat gradientMagnitude(const cv::Mat& bgrImage) {
  cv::Mat gray;
  cv::Mat blurred;
  cv::Mat gradX;
  cv::Mat gradY;
  cv::Mat absGradX;
  cv::Mat absGradY;
  cv::Mat magnitude;
  cv::cvtColor(bgrImage, gray, cv::COLOR_BGR2GRAY);
  cv::GaussianBlur(gray, blurred, {3, 3}, 0);
  cv::Sobel(blurred, gradX, CV_16S, 1, 0);
  cv::Sobel(blurred, gradY, CV_16S, 0, 1);
  cv::convertScaleAbs(gradX, absGradX);
  cv::convertScaleAbs(gradY, absGradY);
  cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0, magnitude);
  return magnitude;
}

void show(const cv::Mat& roiFrame, const cv::Mat& mask) {
  cv::imshow(config::kMaskWindowName, mask);
  cv::imshow(config::kEdgeWindowName, gradientMagnitude(roiFrame));
}

void close() {
  cv::destroyWindow(config::kMaskWindowName);
  cv::destroyWindow(config::kEdgeWindowName);
}

}
