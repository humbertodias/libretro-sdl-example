#include "game.hpp"

Game::Game(unsigned int screen_width, unsigned int screen_height) {
    this->screen_width = screen_width;
    this->screen_height = screen_height;

    if (SDL_Init(SDL_INIT_VIDEO)) {
        throw "SDL Initialization failed";
    }

    window = SDL_CreateWindow("Hello World", screen_width, screen_height, SDL_WINDOW_RESIZABLE);
    if (!window) {
        throw "Failed to create window";
    }

    if (USE_HARDWARE) {
        renderer = SDL_CreateRenderer(window, nullptr);
        if (!renderer) {
            throw "Failed to create renderer";
        }

        // Ativar VSync
        SDL_SetRenderVSync(renderer, 1);
    } else {
        renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    }

    if (!renderer) {
        throw "Failed to create renderer";
    }

    SDL_Surface* pipe = SDL_LoadBMP("image.bmp");
    if (!pipe) {
        throw "Didn't load image";
    }

    this->pipe = SDL_CreateTextureFromSurface(renderer, pipe);
    SDL_DestroySurface(pipe);

}

void Game::GameLoop(double delta_time) {
}

uint32_t* Game::GetFrameBuffer() {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderTexture(renderer, pipe, nullptr, nullptr);

    SDL_RenderPresent(renderer);

    SDL_Surface* surface = SDL_CreateSurface(screen_width, screen_height, SDL_PIXELFORMAT_ARGB8888);
    if (!surface) {
        throw "Failed to create surface";
    }

    SDL_SaveBMP(surface, "screenshot.bmp");
    uint32_t* pixels = static_cast<uint32_t*>(surface->pixels);
    SDL_DestroySurface(surface);

    return pixels;
}
