#include "object_tracker.h"

#if __has_include(<opencv2/tracking.hpp>)
#include <opencv2/tracking.hpp>
#define HAS_CSRT_TRACKER 1
#endif

namespace mt::tracking {

cv::Ptr<cv::Tracker> createTracker() {
#ifdef HAS_CSRT_TRACKER
  return cv::TrackerCSRT::create();
#else
  return cv::TrackerMIL::create();
#endif
}

}
