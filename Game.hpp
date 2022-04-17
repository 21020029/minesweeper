void initTable() {
    
}

void createGame() {
    // random function. ref: https://codeforces.com/blog/entry/61587
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

    while(numBomb < MINE_COUNT) {
        int i = rnd(0, ROW_SIZE - 1);
        int j = rnd(0, COL_SIZE - 1);
        if(gBoard[i][j] == 9) continue;
        gBoard[i][j] = 9;
        numBomb++;
        for (int di = 0; di < 8; ++di) {
            int ni = i + dx[di];
            int nj = j + dy[di];
            if(!(ni >= 0 && nj >= 0 && ni < ROW_SIZE && nj < COL_SIZE)) continue;
            if(g[ni][nj] == 9) continue;
            g[ni][nj]++;
        }
    }
}

bool checkWinGame() {
    return countTileLeft == MINE_COUNT;
}

bool mineManager() {
    if(!loseGame && !isWinning) {
        SDL_Color textColor = {140, 140, 140, 255};
        stringstream ss;
        ss << "Mine left: " << countLeft;
        if(!gMineLeft.loadFromRenderedFile(mineLeft.str().c_str(), textColor)) {
            std::cout << "Unable to render mine left texture\n";
        }
        gMineLeft.render((SCREEN_WIDTH - gMineLeftTexture.getWidth()) / 2, 0);
    }
}

void flagManager() {
    if(isWinning && !loseGame) {
        SDL_RenderPresent(gRenderer);
        SDL_Delay(500);
        Mix_PlayMusic(winner, 0);
        gWinTexture.render(0, 0);
        gPlayWin.render((SCREEN_WIDTH - gPlayWin.getWidth()) / 2, SCREEN_HEIGHT - gPlayWin.getHeight());
    }
    if(loseGame) {
        gTextTeture.render((SCREEN_WIDTH - gTextTexture.getWidth()) / 2, 0);
        Mix_PlayMusic(loser, 0);
        for (int i = 0; i < ROW_SIZE; ++i) {
            for (int j = 0; j < COL_SIZE; ++j) {
                
            }
        }
    }
}