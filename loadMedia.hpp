bool loadMedia() {
    bool okay = true;
    gameOver = TTF_OpenFont("font/myfont.ttf");
    if(gameOver == NULL) {
        std::cout << "Failed" << std::endl;
        okay = false;
    } else {
        SDL_Color textColor = {140, 140, 140};
        if(!gTextTexture.loadFromRenderedText("GAME OVER", textColor)) {
            std::cout << "Failed" << std::endl;
            okay = false;
        }
    }
    
}