cmake_minimum_required(VERSION 3.13)
project(sdl-graphics)

# append the cmake directory to the path where cmake looks for modules, as there
# we have stored FindSDL2_image and FindSDL2_ttf
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
message("CMAKE_MODULE_PATH=[${CMAKE_MODULE_PATH}]")

add_subdirectory(${CMAKE_SOURCE_DIR}/imgui)

# required libraries, SDL2 itself provides the necessary Find-module out
# of the box, the later two are covered by ones provided within the 
# above mentioned cmake directory
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# on Windows, we need to pass this preprocessor definition, else
# the linker complains because we haven't defined WinMain but main
if(MINGW)
	add_definitions("-DSDL_MAIN_HANDLED")
endif()

add_executable(${CMAKE_PROJECT_NAME} sdl-graphics.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC SDL2 SDL2_image SDL2_ttf imgui)
target_link_libraries(${CMAKE_PROJECT_NAME} SDL2 SDL2_image SDL2_ttf imgui)

file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR})
