add_subdirectory(fmt)
add_subdirectory(glfw)
add_subdirectory(glad)
add_subdirectory(stb)
add_subdirectory(libsndfile)
add_subdirectory(json)

add_library(imgui
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_tables.cpp
)
target_include_directories(imgui PUBLIC imgui)