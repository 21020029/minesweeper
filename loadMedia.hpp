
bool loadMedia() {
    bool okay = true;
    gameOver = TTF_OpenFont("font/myfont.ttf", 40);
    if(gameOver == NULL) {
        std::cout << "Failed" << std::endl;
        okay = false;
    } else {
        SDL_Color textColor = {140, 140, 140};
        if(!gTextTexture.loadFromRenderedText("GAME OVER", textColor, gameOver)) {
            std::cout << "Failed" << std::endl;
            okay = false;
        }
    }
    gameWin = TTF_OpenFont("font/myfont.ttf", 40);
    if(gameWin == NULL) {
        std::cout << "Failed" << std::endl;
        okay = false;
    } else {
        SDL_Color textColor = {30, 100, 100};
        if(!gPlayWin.loadFromRenderedText("Press s to play again", textColor, gameWin)) {
            std::cout << "Failed to render text texture\n";
            okay = false;
        }
    }
    gameLose = TTF_OpenFont("font/myfont.ttf", 40);
    if(gameLose == NULL) {
        std::cout << "Failed" << std::endl;
        okay = false;
    } else {
        SDL_Color textColor = {140, 140, 140};
        if(!gPlayLose.loadFromRenderedText("Press s to play again", textColor, gameLose)) {
            std::cout << "Failed to render text texture\n";
            okay = false;
        }
    }
    if(!gWinTexture.loadFromFile("assets/Winner.png")) {
        std::cout << "Failed" << std::endl;
        okay = false;
    }
    if(!gBackground.loadFromFile("assets/Background.png")) {
        std::cout << "Failed" << std::endl;
        okay = false;
    }
    if(!gButtonSprite.loadFromFile("assets/Tiles.png")) {
        std::cout << "Failed" << std::endl;
        okay = false;
    } else {
        for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
            gSpriteClips[i].x = i * 32;
            gSpriteClips[i].y = 0;
            gSpriteClips[i].w = TILE_SIZE;
            gSpriteClips[i].h = TILE_SIZE;
        }
        for (int i = 0; i < ROW_SIZE; ++i) {
            for (int j = 0; j < COL_SIZE; ++j) {
                gButtons[i][j].setPosition(j * TILE_SIZE + DISTANCE_BETWEEN, i * TILE_SIZE + DISTANCE_BETWEEN);
            }
        }
    }

    winner = Mix_LoadMUS("sound/winner.wav");
    loser = Mix_LoadMUS("sound/loser.wav");
    click = Mix_LoadMUS("sound/click.wav");

    return okay;
}