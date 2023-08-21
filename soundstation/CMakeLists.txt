cmake_minimum_required(VERSION 3.10)

add_subdirectory(vendor)

project(soundstation)

set(CMAKE_CXX_STANDARD 23)

if(APPLE)
    add_library(soundstation_platform 
        src/platform/macos/macosaudiodevice.h src/platform/macos/macosaudiodevice.mm
        src/platform/macos/macosaudiodevicelist.h src/platform/macos/macosaudiodevicelist.mm
        src/platform/macos/macosplatform.mm)
    target_include_directories(soundstation_platform PUBLIC src vendor/fmt/include)
    target_link_libraries(soundstation_platform PUBLIC "-framework CoreAudio" "-framework AudioToolbox" "-framework AudioUnit" "-framework CoreServices")
endif()

add_executable(soundstation 
    src/main.cpp
    src/pch.cpp
    
    src/core/log.h src/core/log.cpp
    src/core/assert.h
    src/core/application.h src/core/application.cpp
    src/core/layer.h src/core/layer.cpp
    src/core/layerstack.h src/core/layerstack.cpp
    src/core/window.h src/core/window.cpp
    src/core/image.h src/core/image.cpp
    src/core/time.h src/core/time.cpp
    src/core/splash.h src/core/splash.cpp
    src/core/project.h src/core/project.cpp
    src/core/platform.h
    
    src/renderer/renderer.h src/renderer/renderer.cpp
    src/renderer/rendercommand.h src/renderer/rendercommand.cpp
    src/renderer/texture.h 
    src/renderer/shader.h
    src/renderer/framebuffer.h
    src/renderer/textrenderer.h src/renderer/textrenderer.cpp
    src/renderer/buffer.h
    
    src/audio/audiofile.h src/audio/audiofile.cpp
    src/audio/audiobuffer.h src/audio/audiobuffer.cpp
    src/audio/audiodevice.h src/audio/audiodevice.cpp
    src/audio/audiofilewriter.h src/audio/audiofilewriter.cpp
    src/audio/audiodevicelist.h src/audio/audiodevicelist.cpp

    src/platform/opengl/openglcontext.h src/platform/opengl/openglcontext.cpp
    src/platform/opengl/openglrenderapi.h src/platform/opengl/openglrenderapi.cpp
    src/platform/opengl/opengltexture.h src/platform/opengl/opengltexture.cpp
    src/platform/opengl/openglshader.h src/platform/opengl/openglshader.cpp
    src/platform/opengl/openglframebuffer.h src/platform/opengl/openglframebuffer.cpp
    src/platform/opengl/openglbuffer.h src/platform/opengl/openglbuffer.cpp

    src/layers/playerlayer.h src/layers/playerlayer.cpp
    src/layers/audiodevicemanagerlayer.h src/layers/audiodevicemanagerlayer.cpp
    src/layers/filereaderwriterlayer.h src/layers/filereaderwriterlayer.cpp
    src/layers/toolbarlayer.h src/layers/toolbarlayer.cpp
    src/layers/audiolibrarylayer.h src/layers/audiolibrarylayer.cpp
    src/layers/menubarlayer.h src/layers/menubarlayer.cpp
    src/layers/projectlayer.h src/layers/projectlayer.cpp

    src/serializer/serializer.h src/serializer/serializer.cpp
    
    src/imgui/buildimgui.cpp
    src/imgui/imguilayer.h src/imgui/imguilayer.cpp)

target_precompile_headers(soundstation PUBLIC src/pch.h)

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
        soundstation_platform
        )

if(APPLE)
    set_target_properties(soundstation PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_DISPLAY_NAME "Sound Station"
        MACOSX_BUNDLE_BUNDLE_NAME "Sound Station"
        MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.johansolbakken.soundstation"
        MACOSX_BUNDLE_LONG_VERSION_STRING "1.0"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
        MACOSX_BUNDLE_COPYRIGHT "Johan Solbakken"
        MACOSX_BUNDLE_ICON_FILE "assets/images/AppIcon.icns"
        )

    file(COPY ${CMAKE_SOURCE_DIR}/soundstation/assets DESTINATION ${CMAKE_BINARY_DIR}/soundstation/soundstation.app/Contents/Resources)

    install(TARGETS soundstation DESTINATION /Applications)

else()

# copy assets folder to build directory
add_custom_command(TARGET soundstation POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/soundstation/assets $<TARGET_FILE_DIR:soundstation>/assets)

endif()