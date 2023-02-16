cmake_minimum_required(VERSION 3.13)

message("working on: ${CMAKE_CURRENT_LIST_DIR}")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_library(imgui STATIC
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_impl_sdl2.cpp
    imgui_impl_sdlrenderer.cpp
    imgui_demo.cpp
)

target_include_directories(imgui PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(imgui SDL2 SDL2_image SDL2_ttf)

