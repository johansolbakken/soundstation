cmake_minimum_required(VERSION 3.10)

add_subdirectory(vendor)

project(soundstation)

set(CMAKE_CXX_STANDARD 23)

add_executable(soundstation src/main.cpp
    src/core/log.h src/core/log.cpp
    src/core/assert.h
    src/core/application.h src/core/application.cpp
    src/core/layer.h src/core/layer.cpp
    src/core/layerstack.h src/core/layerstack.cpp
    )
target_include_directories(soundstation PUBLIC src vendor/fmt/include)
target_link_libraries(soundstation PUBLIC fmt::fmt)