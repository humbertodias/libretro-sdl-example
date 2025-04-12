# libretro_sdl3_example

## Build Libretro core

```shell
cmake -Bbuild
cmake --build build
retroarch -L build/libsdl3_example.so
```

## Build executable

```shell
cmake -Bbuild
cmake --build build
build/sdl3_example_exe
```