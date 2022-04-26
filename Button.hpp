void reveal(int i, int j) {
    if(gTable[i][j] == COVER or gTable[i][j] == FLAG) {
        if(gTable[i][j] == FLAG) {
            countLeft++;
        }
        gTable[i][j] = gBoard[i][j];
        if(gBoard[i][j] == MINE) {
            loseGame = true;
        }
        if(gTable[i][j] == BLANK) {
            for (int x = 0; x < NUM_DIRECTION; ++x) {
                int u = i + dx[x];
                int v = j + dy[x];
                if(!(u > 0 && u <= ROW_SIZE && v > 0 && v <= COL_SIZE)) continue;
                if(gBoard[i][j] == MINE) continue;
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
    bool correctFlag(int i, int j);
    void dfs(int i, int j);
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

bool LButton::correctFlag(int i, int j) {
    int flags = 0;
    for (int k = i - 1; k <= i + 1; ++k) {
        for (int l = j - 1; l <= j + 1; ++l) {
            if(gTable[k][l] == FLAG) {
                flags++;
            }
        }
    }
    return flags == gBoard[i][j];
}

void LButton::dfs(int i, int j) {
    for (int k = i - 1; k <= i + 1; ++k) {
        for (int l = j - 1; l <= j + 1; ++l) {
            if(gBoard[k][l] != FLAG) {
                reveal(k, l);
            }
        }
    }
}

void LButton::handleEvent(SDL_Event* e) {
    if(e -> type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        int i = (y - DISTANCE_BETWEEN) / TILE_SIZE;
        int j = (x - DISTANCE_BETWEEN) / TILE_SIZE;
        bool inside = true;
        if(x < mPosition.x) inside = false;
        if(x > mPosition.x + TILE_SIZE) inside = false;
        if(y < mPosition.y) inside = false;
        if(y > mPosition.y + TILE_SIZE) inside = false;
        if(inside) {
            if(e->type == SDL_MOUSEBUTTONDOWN) {
                switch(e->button.button) {
                    Mix_PlayChannel(-1, click, 0);
                    case SDL_BUTTON_LEFT: {
                        if(gTable[i][j] == COVER) {
                            reveal(i, j);
                            if(gBoard[i][j] != MINE) {
                                Mix_PlayChannel(-1, click, 0);
                            }
                        }
                        break;
                    }
                    case SDL_BUTTON_RIGHT: {
                        if(gTable[i][j] == COVER) {
                            if(countLeft == 0) break;
                            gTable[i][j] = FLAG;
                            Mix_PlayChannel(-1, flag, 0);
                            countLeft--;
                        } else if(gTable[i][j] == FLAG) {
                            Mix_PlayChannel(-1, flag, 0);
                            gTable[i][j] = COVER;
                            countLeft++;
                        }
                        break;
                    }
                    case SDL_BUTTON_MIDDLE: {
                        if(gTable[i][j] < MINE && correctFlag(i, j)) {
                            dfs(i, j);
                            Mix_PlayChannel(-1, click, 0);
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