#pragma once

#include <optional>

#include <opencv2/core.hpp>
#include <opencv2/video.hpp>

namespace mt::motion {

cv::Ptr<cv::BackgroundSubtractor> createSubtractor();

// Foreground mask of the given frame region; also updates the background model.
cv::Mat motionMask(cv::BackgroundSubtractor& subtractor, const cv::Mat& roiFrame);

// Box (in mask coordinates) of the moving blob closest to the mask center.
std::optional<cv::Rect> findCentralMotionBox(const cv::Mat& mask);

}
