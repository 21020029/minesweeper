bool checkInside(int x, int y, SDL_Rect &rect) {
    int u = rect.x;
    int v = rect.y;
    int l = rect.w;
    return (x >= u && x <= u + l && y >= v && y <= v + l);
}


int makeMenu() {
    LTexture textMenu[MENU_ITEM];
    bool selectedMenu[MENU_ITEM] = {0, 0};
    std::string labels[MENU_ITEM] = {"NEW GAME", "EXIT"};
    
    for (int i = 0; i < MENU_ITEM; ++i) 
        textMenu[i].loadFromRenderedText(labels[i], {0, 0, 0});
    
    SDL_Event e;
    for (;;) {
        frameStart = SDL_GetTicks();
        SDL_RenderClear(gRenderer);
        for (int i = 0; i < MENU_ITEM; ++i) {
            textMenu[i].render((SCREEN_WIDTH ))
        }
    }
}