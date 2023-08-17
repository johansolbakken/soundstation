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
    src/core/image.h src/core/image.cpp
    
    src/renderer/renderer.h src/renderer/renderer.cpp
    src/renderer/rendercommand.h src/renderer/rendercommand.cpp
    src/renderer/texture.h 
    src/renderer/shader.h

    src/platform/opengl/openglcontext.h src/platform/opengl/openglcontext.cpp
    src/platform/opengl/openglrenderapi.h src/platform/opengl/openglrenderapi.cpp
    src/platform/opengl/opengltexture.h src/platform/opengl/opengltexture.cpp
    src/platform/opengl/openglshader.h src/platform/opengl/openglshader.cpp

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
        vendor/glm
        vendor/stb)

target_link_libraries(soundstation 
    PUBLIC 
        fmt::fmt 
        glfw
        glad
        imgui
        stb
        )

# copy assets folder to build directory
add_custom_command(TARGET soundstation POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/soundstation/assets $<TARGET_FILE_DIR:soundstation>/assets)