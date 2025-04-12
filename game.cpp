#include "game.hpp"
#include <SDL3/SDL.h>

Game::Game(unsigned int screen_width, unsigned int screen_height) {
    this->screen_width = screen_width;
    this->screen_height = screen_height;

    SDL_Init(SDL_INIT_VIDEO);

    surface = SDL_CreateSurface(screen_width, screen_height, SDL_PIXELFORMAT_ARGB8888);
    if (!surface) {
        throw "Failed to create surface";
    }

    if (USE_HARDWARE) {
        // Hardware
        window = SDL_CreateWindow("Hello World", screen_width, screen_height, SDL_WINDOW_RESIZABLE);
        renderer = SDL_CreateRenderer(window, nullptr);
    } else {
        // Software
        renderer = SDL_CreateSoftwareRenderer(surface);
    }

    SDL_Surface *pipeSurface = SDL_LoadBMP("image.bmp");
    if (!pipeSurface) {
        throw "Didn't load image";
    }

    pipe = SDL_CreateTextureFromSurface(renderer, pipeSurface);
    SDL_DestroySurface(pipeSurface);
}

void Game::GameLoop(double delta_time) {
    // TODO: Implement game loop
}

SDL_Rect SurfaceToRect(SDL_Surface* surface) {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = surface->w;
    rect.h = surface->h;
    return rect;
}

uint32_t* Game::GetFrameBuffer() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderTexture(renderer, pipe, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    if (USE_HARDWARE) {
        // SDL2
        // SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
        SDL_Rect rect = SurfaceToRect(surface);
        SDL_RenderReadPixels(renderer, &rect);
    }

    SDL_SaveBMP(surface, "screenshot.bmp");  // For demo's sake

    return static_cast<uint32_t*>(surface->pixels);
}
