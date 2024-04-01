#Minimum version & Project Name
cmake_minimum_required(VERSION 3.27)
project(ubuntu_image_info)

#Using c++17
set(CMAKE_CXX_STANDARD 17)

#Include include/
include_directories(include)

add_executable(ubuntu_image_info src/main.cpp)
