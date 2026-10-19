#pragma once

#include <opencv2/core.hpp>

namespace mt::debug_view {

// Gradient magnitude: bright where brightness changes fast (edges), dark on flat areas.
cv::Mat gradientMagnitude(const cv::Mat& bgrImage);

// Shows the motion mask and the gradient/edge image of the ROI in their own windows.
void show(const cv::Mat& roiFrame, const cv::Mat& mask);

void close();

}
