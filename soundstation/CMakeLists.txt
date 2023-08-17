cmake_minimum_required(VERSION 3.10)

add_subdirectory(vendor)

project(soundstation)

set(CMAKE_CXX_STANDARD 23)

add_executable(soundstation 
    src/main.cpp
    
    src/core/log.h src/core/log.cpp
    src/core/assert.h
    src/core/application.h src/core/application.cpp
    src/core/layer.h src/core/layer.cpp
    src/core/layerstack.h src/core/layerstack.cpp
    src/core/window.h src/core/window.cpp
    
    src/renderer/renderer.h src/renderer/renderer.cpp
    src/renderer/rendercommand.h src/renderer/rendercommand.cpp

    src/platform/opengl/openglcontext.h src/platform/opengl/openglcontext.cpp
    src/platform/opengl/openglrenderapi.h src/platform/opengl/openglrenderapi.cpp

    src/layers/playerlayer.h src/layers/playerlayer.cpp
    
    src/imgui/buildimgui.cpp
    src/imgui/imguilayer.h src/imgui/imguilayer.cpp)

target_include_directories(soundstation 
    PUBLIC 
        src 
        vendor/fmt/include 
        vendor/glfw/include
        vendor/glad/include
        vendor/imgui
        vendor/imgui/backends
        vendor/glm)

target_link_libraries(soundstation 
    PUBLIC 
        fmt::fmt 
        glfw
        glad
        imgui
        )