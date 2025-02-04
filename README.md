# libretro_sdl2_example

## Build Libretro core

```shell
    cmake -Bbuild
    cmake --build build
    retroarch -L build/sdl2_libretro_test.so
```

## Build SDL2 executable

```shell
    cmake -Bbuild
    cmake --build build
    build/sdl2_libretro_test_exe
```