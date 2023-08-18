cmake_minimum_required(VERSION 3.10)

project(sound440)

set(CMAKE_CXX_STANDARD 23)

add_executable(sound440 src/main.mm)
target_link_libraries(sound440 "-framework AudioToolbox" "-framework CoreAudio" "-framework CoreFoundation")