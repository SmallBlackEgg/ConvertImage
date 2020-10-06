cmake_minimum_required(VERSION 3.5)
project(Benchmark)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    add_definitions(-D DARWIN)
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_compile_definitions(__FILE_NAME__=__FILE__)
    add_definitions(-D LINUX)
endif ()

file(GLOB OpenCvLIBS
        ${ROOT_DIR}/3rdparty/opencv/lib/${CMAKE_SYSTEM_NAME}/*)

include_directories(${ROOT_DIR}/3rdparty/jsoncpp/include
        ${ROOT_DIR}/3rdparty/benchmark/include
        ${ROOT_DIR}/3rdparty/opencv/include)

link_directories(${ROOT_DIR}/3rdparty/jsoncpp/lib/${CMAKE_SYSTEM_NAME}
        ${ROOT_DIR}/3rdparty/opencv/lib/${CMAKE_SYSTEM_NAME}
        ${ROOT_DIR}/3rdparty/benchmark/lib/${CMAKE_SYSTEM_NAME})

add_executable(PreProcessFileTest PreProcessFileTest.cpp)
add_executable(ImageWriteTest ImageWriteTest.cpp)
target_link_libraries(PreProcessFileTest benchmark pthread ${OpenCvLIBS})
target_link_libraries(ImageWriteTest benchmark pthread ${OpenCvLIBS})