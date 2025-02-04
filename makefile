RETROARCH=retroarch
ifeq ($(shell uname),Darwin)
    RETROARCH=/Applications/RetroArch.app/Contents/MacOS/RetroArch
endif

.PHONY: build
build:
	cmake -Bbuild
	cmake --build build

run/core: build
	$(RETROARCH) -L build/libretro.so

run: build
	build/sdl2_libretro_test_exe

clean:
	rm -rf build

libretroh:
	curl -L https://raw.githubusercontent.com/libretro/RetroArch/refs/heads/master/libretro-common/include/libretro.h -o libretro.hpp