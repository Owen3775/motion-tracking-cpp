#pragma once

#include <opencv2/videoio.hpp>

namespace mt::camera {

// Opens the default webcam (AVFoundation). Exits the process if it cannot be opened.
cv::VideoCapture open();

} 
