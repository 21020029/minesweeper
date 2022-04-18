
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
    gamePlayAgain = TTF_OpenFont("font/myfont.ttf", 40);
    if(gamePlayAgain == NULL) {
        std::cout << "Failed" << std::endl;
        okay = false;
    } else {
        SDL_Color textColor = {30, 140, 140};
        if(!gPlayAgain.loadFromRenderedText("PRESS ENTER TO PLAY AGAIN", textColor, gamePlayAgain)) {
            std::cout << "Failed" << std::endl;
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
    }

    winner = Mix_LoadMUS("sound/winner.wav");
    loser = Mix_LoadWAV("sound/loser.wav");
    click = Mix_LoadWAV("sound/click.wav");

    return okay;
}