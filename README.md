# libretro_sdl2_example

## Build Libretro core

```shell
cmake -Bbuild
cmake --build build
retroarch -L build/libsdl2_example.so
```

## Build executable

```shell
cmake -Bbuild
cmake --build build
build/sdl2_example_exe
```