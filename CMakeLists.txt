cmake_minimum_required(VERSION 3.5)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

include_directories(ImageFactory
                    ReadFile)

file(GLOB SRC_DIR
        main.cpp
        ImageFactory/*.cpp
        ImageFactory/ImageFormat/*.cpp)

message(${SRC_DIR})
add_executable(rgb2bmp ${SRC_DIR})
target_link_libraries(rgb2bmp ${OpenCV_LIBS})
#target_link_libraries(untitled pthread)