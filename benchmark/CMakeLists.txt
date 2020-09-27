cmake_minimum_required(VERSION 3.5)
project(Benchmark)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    add_definitions(-D DARWIN)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_compile_definitions(__FILE_NAME__=__FILE__)
    add_definitions(-D LINUX)
endif()

include_directories(../3rdparty/benchmark/include)
link_directories(../3rdparty/benchmark/lib/${CMAKE_SYSTEM_NAME})

add_executable(pre_process_file_test pre_process_file_test.cpp)
add_executable(image_write_test image_write_test.cpp)
target_link_libraries(pre_process_file_test benchmark pthread ${OpenCV_LIBS})
target_link_libraries(image_write_test benchmark pthread ${OpenCV_LIBS})