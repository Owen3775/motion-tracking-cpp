#pragma once

#include <opencv2/core.hpp>
#include <opencv2/video.hpp>

namespace mt::tracking {

// CSRT when the contrib tracking module is available, otherwise MIL.
cv::Ptr<cv::Tracker> createTracker();

}
