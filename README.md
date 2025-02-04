# libretro_sdl3_example

## Build Libretro core

```shell
    cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug
    cmake --build build
    retroarch -L build/sdl3_libretro_test.so
```

## Build SDL3 executable

```shell
    cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug
    cmake --build build
    build/sdl3_libretro_test_exe
```