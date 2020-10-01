cmake_minimum_required(VERSION 3.5)
project(ConvertImage)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ROOT_DIR}/bin)

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    add_definitions(-D DARWIN)
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_compile_definitions(__FILE_NAME__=__FILE__)
    add_definitions(-D LINUX)
endif()

include_directories(ImageFactory
        FileOperate
        utils
        3rdparty/jsoncpp/include)

link_directories(3rdparty/jsoncpp/lib/${CMAKE_SYSTEM_NAME})

add_subdirectory(benchmark)

file(GLOB SRC_DIR
        main.cpp
        ImageFactory/*.cpp
        ImageFactory/ImageFormat/*.cpp
        FileOperate/*.cpp
        LiveImage/*.cpp
        utils/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_DIR})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} jsoncpp pthread)
