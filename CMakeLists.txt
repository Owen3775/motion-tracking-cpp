cmake_minimum_required(VERSION 3.20)
project(motion_tracker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)

add_executable(motion_tracker
  src/main.cpp
  src/camera.cpp
  src/motion_detector.cpp
  src/object_tracker.cpp
  src/overlay.cpp
  src/rect_utils.cpp
)
target_include_directories(motion_tracker PRIVATE src ${OpenCV_INCLUDE_DIRS})
target_link_libraries(motion_tracker PRIVATE ${OpenCV_LIBS})
target_compile_options(motion_tracker PRIVATE -Wall -Wextra)
