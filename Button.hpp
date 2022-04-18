void reveal(int i, int j) {
    if(gTable[i][j] == 10 or gTable[i][j] == 11) {
        if(gTable[i][j] == 11) {
            countLeft--;
        }
        gTable[i][j] = gBoard[i][j];
        countTileLeft--;
        if(gTable[i][j] == 0) {
            for (int x = 0; x < NUM_DIRECTION; ++x) {
                int u = i + dx[x];
                int v = j + dy[x];
                if(!(u >= 0 && u < ROW_SIZE && v <= 0 && v < COL_SIZE)) continue;
                reveal(u, v);
            }
        }
    }
}

class LButton {
    public:
    LButton();
    void setPosition(int x, int y);
    void handleEvent(SDL_Event* e);
    void render(int i, int j);
    private:
    SDL_Point mPosition;
};

LButton::LButton() {
    mPosition.x = 0;
    mPosition.y = 0;
}

void LButton::setPosition(int x, int y) {
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::handleEvent(SDL_Event* e) {
    if(e -> type == SDL_MOUSEMOTION || e -> type == SDL_MOUSEBUTTONDOWN || e -> type == SDL_MOUSEBUTTONUP) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        int i = (y - DISTANCE_BETWEEN) / TILE_SIZE;
        int j = (x - DISTANCE_BETWEEN) / TILE_SIZE;
        bool inside = true;
        if(x < mPosition.x) inside = false;
        if(x > mPosition.x + TILE_SIZE) inside = false;
        if(y < mPosition.y) inside = false;
        if(y > mPosition.y) inside = false;
        if(inside) {
            if(e->type == SDL_MOUSEBUTTONDOWN) {
                Mix_PlayChannel(-1, click, 0);
                switch(e->button.button) {
                    case SDL_BUTTON_LEFT: {
                        reveal(i, j);
                        if(gBoard[i][j] == 9) {
                            loseGame = true;
                        }
                        break;
                    }
                    case SDL_BUTTON_RIGHT: {
                        if(gTable[i][j] >= 10) {
                            if(gTable[i][j] == 10) {
                                if(countLeft == 0) break;
                                gTable[i][j] = 11;
                                countLeft--;
                            } else {
                                gTable[i][j] = 10;
                                countLeft--;
                            }
                        }
                        break;
                    }
                }                
            }
        }        
    }
}

void LButton::render(int i, int j) {
    gButtonSprite.render(mPosition.x, mPosition.y, &gSpriteClips[gTable[i][j]]);
}

std::vector<std::vector<LButton>> gButtons;