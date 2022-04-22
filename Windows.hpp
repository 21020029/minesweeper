
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
              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL) quitSDLError(1);
    gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
    if(gRenderer == NULL) quitSDLError(1);
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "SDL_image could not init " << IMG_GetError() << '\n';
    }
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048);
}

void exitGame() {
    gTextTexture.free();
    gPlayAgain.free();
    gWinTexture.free();
    gButtonSprite.free();
    gMineLeft.free();

    TTF_CloseFont(gFont);

    Mix_FreeChunk(click);
    Mix_FreeChunk(loser);
    Mix_FreeChunk(winner);
    Mix_FreeChunk(flag);

    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    gWindow = NULL;
    gRenderer = NULL;

    Mix_CloseAudio();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}