#Minimum version & Project Name
cmake_minimum_required(VERSION 3.27)
project(ubuntu_image_info)

#Using c++17
set(CMAKE_CXX_STANDARD 17)

#Include include/
include_directories(include)

#Include curl and nlohmann/json
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
include_directories(external/json)

add_executable(ubuntu_image_info src/main.cpp
        include/ubuntu_image_info.h
        src/ubuntu_image_info.cpp)

target_link_libraries(ubuntu_image_info ${CURL_LIBRARIES})
