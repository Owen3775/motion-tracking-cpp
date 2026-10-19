#pragma once

#include <optional>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/video.hpp>

namespace mt::motion {

using Contours = std::vector<std::vector<cv::Point>>;

cv::Ptr<cv::BackgroundSubtractor> createSubtractor();

// Foreground mask of the given frame region; also updates the background model.
cv::Mat motionMask(cv::BackgroundSubtractor& subtractor, const cv::Mat& roiFrame);

// Outlines (in mask coordinates) of the moving blobs that are big enough to matter.
Contours findMotionContours(const cv::Mat& mask);

// Box (in mask coordinates) of the contour closest to the center of a mask of the given size.
std::optional<cv::Rect> findCentralMotionBox(const Contours& contours, const cv::Size& maskSize);

}
