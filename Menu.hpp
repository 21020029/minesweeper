bool checkInside(const int &x, const int &y, const SDL_Rect &rect) {
    int u = rect.x;
    int v = rect.y;
    int l = rect.w;
    int h = rect.h;
    return (x > u && x < u + l && y > v && y < v + h);
}


int makeMenu() {
    SCREEN_WIDTH = 500;
    SCREEN_HEIGHT = 500;
    SDL_SetWindowSize(gWindow, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetWindowPosition(gWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    LTexture textMenu[MENU_ITEM];
    bool selectedMenu[MENU_ITEM] = {0, 0};
    std::string labels[MENU_ITEM] = {"NEW GAME", "EXIT"};
    
    for (int i = 0; i < MENU_ITEM; ++i) 
        textMenu[i].loadFromRenderedText(labels[i], {0, 0, 0});
    
    int x = 0, y = 0;

    SDL_Event e;
    for (;;) {
        frameStart = SDL_GetTicks();
        SDL_RenderClear(gRenderer);
        for (int i = 0; i < MENU_ITEM; ++i) {
            textMenu[i].render((SCREEN_WIDTH - textMenu[i].getWidth()) / 2, (SCREEN_HEIGHT - textMenu[i].getHeight()) * 1 / 3 + i * 60);
        }
        while(SDL_PollEvent(&e) != 0) {
            switch(e.type) {
                case SDL_QUIT:
                    return EXIT;
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE) 
                        return EXIT;
                    break;
                case SDL_MOUSEMOTION: {
                    x = e.motion.x;
                    y = e.motion.y;
                    for (int i = 0; i < MENU_ITEM; ++i) {
                        if(checkInside(x, y, textMenu[i].getRect())) {
                            if(!selectedMenu[i]) {
                                selectedMenu[i] = 1;
                                textMenu[i].loadFromRenderedText(labels[i], {255, 0, 0});
                            }
                        } else {
                            if(selectedMenu[i]) {
                                selectedMenu[i] = 0;
                                textMenu[i].loadFromRenderedText(labels[i], {0, 0, 0});
                            }
                        }
                    }
                }
                break;
                case SDL_MOUSEBUTTONDOWN: {
                    x = e.motion.x;
                    y = e.motion.y;
                    for (int i = 0; i < MENU_ITEM; ++i) {
                        if(checkInside(x, y, textMenu[i].getRect())) {
                            for (int j = 0; j < MENU_ITEM; ++j) {
                                textMenu[i].free();
                                Mix_PlayChannel(-1, click, 0);
                                return i;
                            }
                        }
                    }
                }
                break;
            }
        }
        SDL_RenderPresent(gRenderer);
        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

int showGameMode() {
    static const int numGameMode = 2;
    LTexture textMenu[numGameMode];
    bool selectedMenu[numGameMode] = {0, 0};
    std::string labels[numGameMode] = {"Easy (9 x 9)"
                                , "Hard (11 x 11)"};

    for (int i = 0; i < numGameMode; ++i) {
        textMenu[i].loadFromRenderedText(labels[i], {0, 0, 0});
    }

    int x = 0, y = 0;

    SDL_Event e;
    for (;;) {
        frameStart = SDL_GetTicks();
        SDL_RenderClear(gRenderer);
        for (int i = 0; i < numGameMode; ++i) {
            textMenu[i].render((SCREEN_WIDTH - textMenu[i].getWidth()) / 2, (SCREEN_HEIGHT - textMenu[i].getHeight()) * 1 / 3 + i * 60);
        }
        while(SDL_PollEvent(&e) != 0) {
            switch(e.type) {
                case SDL_QUIT:
                    return QUIT;
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE) {
                        return BACK;
                    }
                    break;
                case SDL_MOUSEMOTION: {
                    x = e.motion.x;
                    y = e.motion.y;
                    for (int i = 0; i < numGameMode; ++i) {
                        if(checkInside(x, y, textMenu[i].getRect())) {
                            if(!selectedMenu[i]) {
                                selectedMenu[i] = true;
                                textMenu[i].loadFromRenderedText(labels[i], {255, 0, 0});
                            }
                        } else {
                            if(selectedMenu[i]) {
                                selectedMenu[i] = false;
                                textMenu[i].loadFromRenderedText(labels[i], {0, 0, 0}); 
                            }
                        }
                    }
                }
                break;
                case SDL_MOUSEBUTTONDOWN: {
                    x = e.motion.x;
                    y = e.motion.y;
                    for (int i = 0; i < numGameMode; ++i) {
                        if(checkInside(x, y, textMenu[i].getRect())) {
                            for (int j = 0; j < numGameMode; ++j) {
                                textMenu[i].free();
                            }
                            Mix_PlayChannel(-1, click, 0);
                            return i;
                        }
                    }
                }
                break;
            }
            SDL_RenderPresent(gRenderer);
            frameTime = SDL_GetTicks() - frameStart;
            if(frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }
    }
    return 0;
}