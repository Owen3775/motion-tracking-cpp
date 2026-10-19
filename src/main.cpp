#include <cstdlib>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "camera.h"
#include "config.h"
#include "debug_view.h"
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
  int lockProgress = 0;
  bool showDebug = true;

  cv::Mat frame;
  while (capture.read(frame)) {
    cv::flip(frame, frame, 1);
    const cv::Rect roi = rect_utils::centerRoi(frame.size());
    const cv::Mat mask = motion::motionMask(*subtractor, frame(roi));/* white = differs from learned background (moving), black = matches background */
    const auto contours = motion::findMotionContours(mask);/*The red outline of a white blob in the mask. Bounding rectangle: The smallest upright box that contains that outline.*/

    if (state == State::Search && frameCount++ >= config::kWarmupFrames) {
      const auto box = motion::findCentralMotionBox(contours, mask.size());
      lockProgress = box ? lockProgress + 1 : 0;
      if (box && lockProgress >= config::kLockFrames) {
        target = *box + roi.tl();
        tracker = tracking::createTracker();
        tracker->init(frame, target);
        state = State::Track;
        lockProgress = 0;
      }
    } else if (state == State::Track && !tracker->update(frame, target)) {
      state = State::Search;
    }

    if (showDebug) debug_view::show(frame(roi), mask);
    overlay::drawContours(frame, contours, roi);/*show what pixels changed, masks, which is where the boxes are based off of*/
    overlay::draw(frame, roi, state, target);
    cv::imshow(config::kWindowName, frame);

    const int key = cv::waitKey(1);
    if (key == config::kQuitKey || key == config::kEscKey) break;
    if (key == config::kResetKey) state = State::Search;
    if (key == config::kDebugKey) {
      showDebug = !showDebug;
      if (!showDebug) debug_view::close();
    }
  }
  return EXIT_SUCCESS;
}
