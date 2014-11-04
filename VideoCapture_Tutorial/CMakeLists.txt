cmake_minimum_required(VERSION 2.8.4)
project(VideoCapture_Tutorial)
find_package( OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(VideoCapture_Tutorial ${SOURCE_FILES})
target_link_libraries( VideoCapture_Tutorial ${OpenCV_LIBS} )