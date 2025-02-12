#include "game.hpp"


Game::Game(unsigned int screen_width, unsigned int screen_height) {
    this->screen_width = screen_width;
    this->screen_height = screen_height;

    SDL_Init(SDL_INIT_EVERYTHING);
    surface = SDL_CreateRGBSurface(0, screen_width, screen_height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    if (USE_HARDWARE) {
        // Hardware
        window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_OPENGL);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    } else {
        //Software
        renderer = SDL_CreateSoftwareRenderer(surface);
    }

    SDL_Surface *pipe = SDL_LoadBMP("image.bmp");
    if (pipe == nullptr)
        throw "Didn't load image";
    this->pipe = SDL_CreateTextureFromSurface(renderer, pipe);
    SDL_FreeSurface(pipe);
}

void Game::GameLoop(double delta_time) {

}

uint32_t* Game::GetFrameBuffer() {
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderClear( renderer );
    SDL_RenderCopy(renderer, pipe, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    if (USE_HARDWARE)
        SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
    SDL_SaveBMP(surface, "screenshot.bmp");  // For demo's sake
    return (uint32_t*)surface->pixels;
}