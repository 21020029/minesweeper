#include <bits/stdc++.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Constances.hpp"
#include "Texture.hpp"
#include "Button.hpp"

#include "InitWindows.hpp"
#include "loadMedia.hpp"
#include "Menu.hpp"
#include "Game.hpp"

int main(int argc, char *argv[]) {
    initProgram();
    if(!loadMedia()) {
        std::cout << "Failed to load media\n";
    } else {
        bool quit = false;
        SDL_Event e;
    }
}