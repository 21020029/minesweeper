#ifndef TEXTURE__H_
#define TEXTURE__H_

#include <bits/stdc++.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Constances.hpp"
#include "Variables.hpp"

class LTexture {
public:
    LTexture();
    ~LTexture();
    bool loadFromFile(std::string path);
    bool loadFromRenderedText(std::string myText, SDL_Color textColor);
    void free();
    void render(int x, int y, SDL_Rect* clip = NULL);
    int getWidth();
    int getHeight();
private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};

#endif TEXTURE__H_