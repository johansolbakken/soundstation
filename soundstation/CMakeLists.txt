cmake_minimum_required(VERSION 3.10)

add_subdirectory(vendor)

project(soundstation)

set(CMAKE_CXX_STANDARD 23)

if(APPLE)
    set(PLATFORM_SOURCE 
        src/platform/macos/macosaudiodevice.h src/platform/macos/macosaudiodevice.mm
        src/platform/macos/macosaudiodevicelist.h src/platform/macos/macosaudiodevicelist.mm)
    set(PLATFORM_LIBS "-framework CoreAudio" "-framework AudioToolbox" "-framework AudioUnit" "-framework CoreServices")
endif()

add_executable(soundstation 
    src/main.cpp
    
    src/core/log.h src/core/log.cpp
    src/core/assert.h
    src/core/application.h src/core/application.cpp
    src/core/layer.h src/core/layer.cpp
    src/core/layerstack.h src/core/layerstack.cpp
    src/core/window.h src/core/window.cpp
    src/core/image.h src/core/image.cpp
    src/core/time.h src/core/time.cpp
    src/core/splash.h src/core/splash.cpp
    
    src/renderer/renderer.h src/renderer/renderer.cpp
    src/renderer/rendercommand.h src/renderer/rendercommand.cpp
    src/renderer/texture.h 
    src/renderer/shader.h
    src/renderer/framebuffer.h
    src/renderer/textrenderer.h src/renderer/textrenderer.cpp
    src/renderer/buffer.h
    
    src/audio/audiofile.h src/audio/audiofile.cpp
    src/audio/audiobuffer.h src/audio/audiobuffer.cpp
    src/audio/audiodevice.h
    src/audio/audiofilewriter.h src/audio/audiofilewriter.cpp
    src/audio/audiodevicelist.h

    src/platform/opengl/openglcontext.h src/platform/opengl/openglcontext.cpp
    src/platform/opengl/openglrenderapi.h src/platform/opengl/openglrenderapi.cpp
    src/platform/opengl/opengltexture.h src/platform/opengl/opengltexture.cpp
    src/platform/opengl/openglshader.h src/platform/opengl/openglshader.cpp
    src/platform/opengl/openglframebuffer.h src/platform/opengl/openglframebuffer.cpp
    src/platform/opengl/openglbuffer.h src/platform/opengl/openglbuffer.cpp
    ${PLATFORM_SOURCE}

    src/layers/playerlayer.h src/layers/playerlayer.cpp
    src/layers/audiodevicemanagerlayer.h src/layers/audiodevicemanagerlayer.cpp
    src/layers/filereaderwriterlayer.h src/layers/filereaderwriterlayer.cpp
    src/layers/toolbarlayer.h src/layers/toolbarlayer.cpp
    src/layers/audiolibrarylayer.h src/layers/audiolibrarylayer.cpp
    src/layers/menubarlayer.h src/layers/menubarlayer.cpp

    src/serializer/serializer.h src/serializer/serializer.cpp
    
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
        vendor/stb
        vendor/libsndfile/include
        vendor/json/include
        vendor/freetype/include)

target_link_libraries(soundstation 
    PUBLIC 
        fmt::fmt 
        glfw
        glad
        imgui
        stb
        sndfile
        nlohmann_json::nlohmann_json
        freetype
        ${PLATFORM_LIBS}
        )

# copy assets folder to build directory
add_custom_command(TARGET soundstation POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/soundstation/assets $<TARGET_FILE_DIR:soundstation>/assets)