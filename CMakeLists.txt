cmake_minimum_required(VERSION 3.14)
project(sdl2_example)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

# Fetch SDL2
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.32.4
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL2)

# Fetch SDL2_image
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.8.8
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL2_image)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_compile_definitions(USE_HARDWARE=true)  # Toggle this

# Make Libretro library
add_library(${PROJECT_NAME} SHARED libretro.hpp libretro.cpp game.cpp game.hpp)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image)

# Make exe
add_executable(${PROJECT_NAME}_exe main.cpp game.cpp game.hpp)
target_link_libraries(${PROJECT_NAME}_exe SDL2 SDL2_image)

# Copy the image file to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/image.bmp DESTINATION ${CMAKE_BINARY_DIR})