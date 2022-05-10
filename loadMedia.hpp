bool loadMedia() {
    bool okay = true;
    SDL_SetRenderDrawColor(gRenderer, 204, 204, 204, 255);
    gFont = TTF_OpenFont("font/myfont.ttf", 40);
    SDL_Color textColor = {140, 140, 140};
    if(!gTextTexture.loadFromRenderedText("GAME OVER", textColor)) {
        std::cout << "Failed" << std::endl;
        okay = false;
    }
    textColor = {30, 140, 140};
    if(!gPlayAgain.loadFromRenderedText("PRESS ESC TO PLAY AGAIN", textColor)) {
        std::cout << "Failed" << std::endl;
        okay = false;
    }
    if(!gWinTexture.loadFromRenderedText("YOU WIN", textColor)) {
        std::cout << "Failed" << std::endl;
        okay = false;
    }
    if(!gButtonSprite.loadFromFile("assets/Tiles.png")) {
        std::cout << "Failed" << std::endl;
        okay = false;
    } else {
        for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
            gSpriteClips[i].x = i * TILE_SIZE;
            gSpriteClips[i].y = 0;
            gSpriteClips[i].w = TILE_SIZE;
            gSpriteClips[i].h = TILE_SIZE;
        }
    }

    winner = Mix_LoadWAV("sound/winner.wav");
    boom_sound = Mix_LoadWAV("sound/loser.wav");
    click = Mix_LoadWAV("sound/click.wav");
    flag = Mix_LoadWAV("sound/flag.wav");

    return okay;
}
