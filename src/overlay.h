#pragma once

#include <opencv2/core.hpp>

#include "motion_detector.h"
#include "state.h"

namespace mt::overlay {

// Draws the ROI box, the target box while tracking, and a state label.
void draw(cv::Mat& frame, const cv::Rect& roi, State state, const cv::Rect& target);

// Draws the moving-blob outlines, which are in ROI coordinates, onto the full frame.
void drawContours(cv::Mat& frame, const motion::Contours& contours, const cv::Rect& roi);

}
