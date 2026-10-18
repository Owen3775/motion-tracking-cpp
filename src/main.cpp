#include <cstdlib>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "camera.h"
#include "config.h"
#include "motion_detector.h"
#include "object_tracker.h"
#include "overlay.h"
#include "rect_utils.h"
#include "state.h"

int main() {
  using namespace mt;

  cv::VideoCapture capture = camera::open();
  auto subtractor = motion::createSubtractor();
  cv::Ptr<cv::Tracker> tracker;
  cv::Rect target;
  State state = State::Search;
  int frameCount = 0;

  cv::Mat frame;
  while (capture.read(frame)) {
    cv::flip(frame, frame, 1);
    const cv::Rect roi = rect_utils::centerRoi(frame.size());
    const cv::Mat mask = motion::motionMask(*subtractor, frame(roi));

    if (state == State::Search && frameCount++ >= config::kWarmupFrames) {
      if (const auto box = motion::findCentralMotionBox(mask)) {
        target = *box + roi.tl();
        tracker = tracking::createTracker();
        tracker->init(frame, target);
        state = State::Track;
      }
    } else if (state == State::Track && !tracker->update(frame, target)) {
      state = State::Search;
    }

    overlay::draw(frame, roi, state, target);
    cv::imshow(config::kWindowName, frame);

    const int key = cv::waitKey(1);
    if (key == config::kQuitKey || key == config::kEscKey) break;
    if (key == config::kResetKey) state = State::Search;
  }
  return EXIT_SUCCESS;
}
