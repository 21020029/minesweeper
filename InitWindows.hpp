#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Constances.hpp"
#include "Variables.hpp"

void quitSDLError(bool fatal) {
    std::cout << "Error: " << SDL_GetError() << std::endl;
    if(fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initProgram() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    gWindow = SDL_CreateWindow("Minesweeper 1.0", 
              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WITDH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL) quitSDLError(1);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(gRenderer == NULL) quitSDLError(1);
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not init " << IMG_GetError() << '\n';
    }
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2018);
}
