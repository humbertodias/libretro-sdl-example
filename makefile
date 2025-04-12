RETROARCH=$(shell which retroarch)
ifeq ($(shell uname),Darwin)
    RETROARCH=/Applications/RetroArch.app/Contents/MacOS/RetroArch
endif

.PHONY: build

CMAKE=$(shell which cmake)
build:
	$(CMAKE) -Bbuild
	$(CMAKE) --build build

videodriver:
	@echo $(XDG_SESSION_TYPE)

run/core: build
	SDL_VIDEODRIVER=x11 $(RETROARCH) -L build/sdl2_libretro_test.so

run: build
	build/sdl2_libretro_test_exe

clean:
	rm -rf build

libretroh:
	curl -L https://raw.githubusercontent.com/libretro/RetroArch/refs/heads/master/libretro-common/include/libretro.h -o libretro.hpp