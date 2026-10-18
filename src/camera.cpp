#include "camera.h"

#include <cstdlib>
#include <iostream>

#include "config.h"

namespace mt::camera {

cv::VideoCapture open() {
  cv::VideoCapture capture(config::kCameraIndex, cv::CAP_AVFOUNDATION);
  if (!capture.isOpened()) {
    std::cerr << "Could not open the webcam. Check System Settings > Privacy & Security > Camera.\n";
    std::exit(EXIT_FAILURE);
  }
  return capture;
}

}  
