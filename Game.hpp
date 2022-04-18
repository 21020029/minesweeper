void initTable(int rowSize, int colSize) {
    ROW_SIZE = rowSize;
    COL_SIZE = colSize;
    gTable.resize(ROW_SIZE + 2, std::vector<int>(COL_SIZE + 2, COVER));
    gBoard.resize(ROW_SIZE + 2, std::vector<int>(COL_SIZE + 2, BLANK));
    gButtons.resize(ROW_SIZE + 2, std::vector<LButton>(COL_SIZE + 2));
    countLeft = mineCount;
    DISTANCE_BETWEEN = (SCREEN_WITDH  - (ROW_SIZE + 2) * COL_SIZE) / 2;
    for (int i = 1; i <= ROW_SIZE; ++i) {
        for (int j = 1; j <= COL_SIZE; ++j) {
            gButtons[i][j].setPosition(j * TILE_SIZE + DISTANCE_BETWEEN, i * TILE_SIZE + DISTANCE_BETWEEN);
        }
    }
}

void createGame() {
    // random function. ref: https://codeforces.com/blog/entry/61587
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

    auto rnd = [&](int l, int r) {
        return l + rng() % (r - l + 1);
    };

    int numBomb = 0;
    for (int i = 0; i < ROW_SIZE; ++i) {
        for (int j = 0; j < COL_SIZE; ++j) {
            gTable[i][j] = 10;
            gBoard[i][j] = 0;
        }
    }

    while(numBomb < mineCount) {
        int i = rnd(0, ROW_SIZE - 1);
        int j = rnd(0, COL_SIZE - 1);
        if(gBoard[i][j] == 9) continue;
        gBoard[i][j] = 9;
        numBomb++;
        for (int di = 0; di < 8; ++di) {
            int ni = i + dx[di];
            int nj = j + dy[di];
            if(!(ni >= 0 && nj >= 0 && ni < ROW_SIZE && nj < COL_SIZE)) continue;
            if(gBoard[ni][nj] == 9) continue;
            gBoard[ni][nj]++;
        }
    }
}

bool checkWinGame() {
    for (int i = 1; i <= COL_SIZE; ++i) {
        for (int j = 1; j <= ROW_SIZE; ++j) {
            if(gBoard[i][j] == MINE) {
                if(gTable[i][j] != FLAG) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool mineManager() {
    if(!loseGame && !isWinning) {
        SDL_Color textColor = {140, 140, 140, 255};
        std::stringstream ss;
        ss << "Mine left: " << countLeft;
        if(!gMineLeft.loadFromRenderedText(ss.str().c_str(), textColor)) {
            std::cout << "Unable to render mine left texture\n";
        }
        gMineLeft.render((SCREEN_WITDH - gMineLeft.getWidth()) / 2, 30);
    }
}

void flagManager() {
    if(isWinning) {
        for (int i = 1; i <= ROW_SIZE; ++i) {
            for (int j = 1; j <= COL_SIZE; ++j) {
                gTable[i][j] = gBoard[i][j];
            }
        }
        for (int i = 1; i <= ROW_SIZE; ++i) {
            for (int j = 1; j <= COL_SIZE; ++j) {
                gButtons[i][j].render(i, j);
            }
        }
        gWinTexture.render((SCREEN_WITDH - gWinTexture.getWidth()) / 2, 30);
        gPlayAgain.render((SCREEN_WITDH - gPlayAgain.getWidth()) / 2, SCREEN_HEIGHT - gPlayAgain.getHeight());
        Mix_PlayMusic(winner, 0);
    }
    if(loseGame) {
        for (int i = 1; i <= ROW_SIZE; ++i) {
            for (int j = 1; j <= COL_SIZE; ++j) {
                gTable[i][j] = gBoard[i][j];
            }
        }
        for (int i = 1; i <= ROW_SIZE; ++i) {
            for (int j = 1; j <= COL_SIZE; ++j) {
                gButtons[i][j].render(i, j);
            }
        }
        gWinTexture.render((SCREEN_WITDH - gWinTexture.getWidth()) / 2, 30);
        gPlayAgain.render((SCREEN_WITDH - gPlayAgain.getWidth()) / 2, SCREEN_HEIGHT - gPlayAgain.getHeight());
        Mix_PlayChannel(-1, loser, 0);
    }
}

bool playAgain(bool &quitGame, bool &quit) {
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {
        switch(e.type) {
            case SDL_QUIT: { 
                quitGame = true;
                quit = true;
                break;
            } 
            case SDL_KEYDOWN: {
                if(e.key.keysym.sym == SDLK_RETURN) {
                    /**
                     * play again
                     */
                    Mix_HaltMusic();
                    countLeft = mineCount;
                    loseGame = false;
                    isWinning = false;
                    for (int i = 0; i < ROW_SIZE + 2; ++i) 
                        fill(begin(gBoard[i]), end(gBoard[i]), BLANK),
                        fill(begin(gTable[i]), end(gTable[i]), COVER);
                    createGame();
                } else if(e.key.keysym.sym == SDLK_ESCAPE) {
                    /**
                     * return to main menu
                     */
                    Mix_HaltMusic();
                    quitGame = true;
                    loseGame = false;
                    isWinning = false;
                    for (int i = 0; i < ROW_SIZE + 2; ++i) 
                        fill(begin(gBoard[i]), end(gBoard[i]), BLANK),
                        fill(begin(gTable[i]), end(gTable[i]), COVER);
                }
            }
        }
    }
}

void closeGame() {
    gButtonSprite.free();
    gMineLeft.free();
    gPlayAgain.free();
    gWinTexture.free();
    gTextTexture.free();

    TTF_CloseFont(gameOver);
    TTF_CloseFont(gamePlayAgain);

    Mix_FreeChunk(click);
    Mix_FreeMusic(winner);
    Mix_FreeChunk(loser);

    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    gWindow = NULL;
    gRenderer = NULL;

    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}