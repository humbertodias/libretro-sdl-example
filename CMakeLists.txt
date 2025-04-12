cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_OBJC_COMPILER /usr/bin/clang++)

project(sdl3_example)



include(FetchContent)

# Fetch SDL3
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.10
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL3)

# Fetch SDL3_image
FetchContent_Declare(
    SDL3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-3.2.4
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL3_image)

# Add a definition to toggle hardware rendering
add_compile_definitions(USE_HARDWARE=1)

# Shared library target
add_library(${PROJECT_NAME} SHARED
    libretro.hpp libretro.cpp
    game.hpp game.cpp
)
message(STATUS "SDL3_SOURCE_DIR: ${SDL3_SOURCE_DIR}")
message(STATUS "SDL3_image_SOURCE_DIR: ${SDL3_image_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL3_SOURCE_DIR}/include ${SDL3_image_SOURCE_DIR}/include)

# Executable target
add_executable(${PROJECT_NAME}_exe main.cpp game.cpp game.hpp)
target_link_libraries(${PROJECT_NAME}_exe PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)
target_include_directories(${PROJECT_NAME}_exe PRIVATE ${SDL3_SOURCE_DIR}/include ${SDL3_image_SOURCE_DIR}/include)

# Copy assets
file(COPY ${CMAKE_SOURCE_DIR}/image.bmp DESTINATION ${CMAKE_BINARY_DIR})
