#ifndef SUPERPONG_GAME_H
#define SUPERPONG_GAME_H

#include <SDL3/SDL.h>

class Game {
public:
    Game(unsigned int screen_width, unsigned int screen_height);
    void GameLoop(double delta_time);
    uint32_t* GetFrameBuffer();

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_Texture* pipe = nullptr;
    unsigned int screen_width = 0;
    unsigned int screen_height = 0;
};

#endif // SUPERPONG_GAME_H
