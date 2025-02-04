#ifndef SUPERPONG_GAME_H
#define SUPERPONG_GAME_H

#include <SDL.h>


class Game {
public:
    Game(unsigned int screen_width, unsigned int screen_height);
    void GameLoop(double delta_time);
    uint32_t* GetFrameBuffer();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    unsigned int screen_width;
    unsigned int screen_height;
    SDL_Texture* pipe;
};

#endif //SUPERPONG_GAME_H
