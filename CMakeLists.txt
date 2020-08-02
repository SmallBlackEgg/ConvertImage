cmake_minimum_required(VERSION 3.5)
project(ConvertImage)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

include_directories(ImageFactory
        FileOperate)

file(GLOB SRC_DIR
        main.cpp
        ImageFactory/*.cpp
        ImageFactory/ImageFormat/*.cpp
        FileOperate/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_DIR} utils/ImageConvert.cpp utils/ImageConvert.h)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} pthread)