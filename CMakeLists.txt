cmake_minimum_required(VERSION 3.5)
project(ConvertImage)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")

elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_compile_definitions(__FILE_NAME__=__FILE__)
endif()

include_directories(ImageFactory
        FileOperate
        utils
        3rdparty/jsoncpp/include)

link_directories(3rdparty/jsoncpp/lib/${CMAKE_SYSTEM_NAME})

file(GLOB SRC_DIR
        main.cpp
        ImageFactory/*.cpp
        ImageFactory/ImageFormat/*.cpp
        FileOperate/*.cpp
        utils/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_DIR})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} jsoncpp pthread)
