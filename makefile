RETROARCH=$(shell which retroarch)
OS := $(shell uname)
ifeq ($(OS),Darwin)
    RETROARCH=/Applications/RetroArch.app/Contents/MacOS/RetroArch
endif

.PHONY: build

CMAKE := $(shell which cmake)
CC    := $(shell which gcc)
CXX   := $(shell which g++)
build:
	$(CMAKE) -Bbuild -DCMAKE_C_COMPILER=$(CC) -DCMAKE_CXX_COMPILER=$(CXX) -DCMAKE_BUILD_TYPE=Debug
	$(CMAKE) --build build

EXT = .dll
ifeq ($(OS),Darwin)
	EXT = .dylib
else ifeq ($(OS),Linux)
	EXT = .so
endif

run/core: build
	$(RETROARCH) -L build/libsdl3_example$(EXT)

run/exe: build
	build/sdl3_example_exe

clean:
	rm -rf build

libretroh:
	curl -L https://raw.githubusercontent.com/libretro/RetroArch/refs/heads/master/libretro-common/include/libretro.h -o libretro.hpp