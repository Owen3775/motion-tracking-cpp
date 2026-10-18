#pragma once

#include <opencv2/core.hpp>

namespace mt::config {

inline constexpr int kRoiSize = 350;
inline constexpr int kWarmupFrames = 30;
inline constexpr double kMinContourArea = 400.0;

inline constexpr int kMogHistory = 500;
inline constexpr double kMogVarThreshold = 25.0;
inline constexpr int kBlurKernelSize = 5;
inline constexpr double kMaskThreshold = 200.0;
inline constexpr int kDilateIterations = 2;

inline constexpr int kCameraIndex = 0;
inline constexpr char kWindowName[] = "Motion Tracker";

inline constexpr int kQuitKey = 'q';
inline constexpr int kResetKey = 'r';
inline constexpr int kEscKey = 27;

inline const cv::Scalar kRoiColor(255, 200, 0);
inline const cv::Scalar kTargetColor(0, 255, 0);

}
