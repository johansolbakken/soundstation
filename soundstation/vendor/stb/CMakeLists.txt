cmake_minimum_required(VERSION 3.10)

project(stb)

set(CMAKE_CXX_STANDARD 17)

add_library(stb stb_image.cpp stb_image.h)