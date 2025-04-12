#include "game.hpp"
#include <SDL3/SDL.h>
#include "libretro.hpp"

Game::Game(unsigned int screen_width, unsigned int screen_height) {
    this->screen_width = screen_width;
    this->screen_height = screen_height;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Hello World", screen_width, screen_height, SDL_WINDOW_RESIZABLE);
    if (!window) {
        throw "Failed to create window";
    }

    surface = SDL_GetWindowSurface(window);
    if (!surface) {
        throw "Failed to get window surface";
    }

    SDL_Surface *pipeSurface = SDL_LoadBMP("image.bmp");
    if (pipeSurface == nullptr) {
        throw "Didn't load image";
    }

    SDL_BlitSurface(pipeSurface, nullptr, surface, nullptr);
    SDL_DestroySurface(pipeSurface);

    SDL_UpdateWindowSurface(window);
}


void Game::GameLoop(double delta_time) {
    // TODO: Implement game loop
}

uint32_t* Game::GetFrameBuffer() {
    if (USE_HARDWARE) {
        SDL_UpdateWindowSurface(window);
    }

    SDL_SaveBMP(surface, "screenshot.bmp");

    return static_cast<uint32_t*>(surface->pixels);
}
