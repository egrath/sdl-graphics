cmake_minimum_required(VERSION 3.13)

project(sdl-graphics)

add_subdirectory(${CMAKE_SOURCE_DIR}/imgui)

find_package(SDL2 REQUIRED)
find_package(SDL_image REQUIRED)
find_package(SDL_ttf REQUIRED)

add_executable(${CMAKE_PROJECT_NAME} sdl-graphics.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC SDL2 SDL2_image SDL2_ttf imgui)
target_link_libraries(${CMAKE_PROJECT_NAME} SDL2 SDL2_image SDL2_ttf imgui)

file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR})
