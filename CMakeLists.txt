cmake_minimum_required(VERSION 3.14)
project(SDL3_libretro_test)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

# Fetch SDL3
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.2
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL3)

# Fetch SDL3_image
FetchContent_Declare(
    SDL3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-3.2.0
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL3_image)

# Manually set include directories
set(SDL3_INCLUDE_DIRS ${SDL3_SOURCE_DIR}/include)
set(SDL3_IMAGE_INCLUDE_DIRS ${SDL3_image_SOURCE_DIR}/include)

message("SDL3_INCLUDE_DIRS=${SDL3_INCLUDE_DIRS}
SDL3_IMAGE_INCLUDE_DIRS=${SDL3_IMAGE_INCLUDE_DIRS}"
)

include_directories(${SDL3_INCLUDE_DIRS} ${SDL3_IMAGE_INCLUDE_DIRS})

add_compile_definitions(USE_HARDWARE=true)  # Toggle this

# Make Libretro library
add_library(${PROJECT_NAME} SHARED libretro.hpp libretro.cpp game.cpp game.hpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

# Make exe
add_executable(${PROJECT_NAME}_exe main.cpp game.cpp game.hpp)
target_link_libraries(${PROJECT_NAME}_exe PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

# Copy the image file to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/image.bmp DESTINATION ${CMAKE_BINARY_DIR})