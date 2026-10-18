#pragma once

#include <opencv2/core.hpp>

#include "state.h"

namespace mt::overlay {

// Draws the ROI box, the target box while tracking, and a state label.
void draw(cv::Mat& frame, const cv::Rect& roi, State state, const cv::Rect& target);

}
