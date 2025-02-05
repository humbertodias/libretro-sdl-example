#include "game.hpp"

Game::Game(unsigned int screen_width, unsigned int screen_height) {
    this->screen_width = screen_width;
    this->screen_height = screen_height;

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        throw "SDL Initialization failed";
    }

    surface = SDL_CreateSurface(screen_width, screen_height, SDL_PIXELFORMAT_RGBA32);

    if (USE_HARDWARE) {
        window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOW_RESIZABLE);
        renderer = SDL_CreateRenderer(window, nullptr);
        SDL_SetRenderVSync(renderer, 1);
    } else {
        renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
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
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderClear( renderer );
    SDL_RenderTexture(renderer, pipe, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    if (USE_HARDWARE) {
        SDL_RenderReadPixels(renderer, nullptr);
    }
    SDL_SaveBMP(surface, "screenshot.bmp");  // For demo's sake
    return (uint32_t*)surface->pixels;
}
