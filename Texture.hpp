// #ifndef TEXTURE_H
// #define TEXTURE_H

class LTexture {
public:
    LTexture();
    ~LTexture();
    bool loadFromFile(std::string path);
    bool loadFromRenderedText(std::string myText, SDL_Color myColor);
    void free();
    void render(int x, int y, SDL_Rect* clip = NULL);
    int getWidth();
    int getHeight();
    SDL_Rect getRect();
private:
    SDL_Texture* mTexture;
    SDL_Rect rect;
    int mWidth;
    int mHeight;
};

LTexture::LTexture() {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture() {
    free();
}

bool LTexture::loadFromRenderedText(std::string myText, SDL_Color myColor) {
    free();
    SDL_Surface* textSurface  = TTF_RenderText_Solid(gFont, myText.c_str(), myColor);
    if(textSurface == NULL) {
        std::cout << "Unable to render text surface! SDL_ttf error: " << TTF_GetError() << '\n';
        std::cout << myText << '\n';
    } else {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if(mTexture == NULL) {
            std::cout << "Unable to create texture from rendered text! SDL_Error: " << SDL_GetError() << std::endl;
        } else {
            mWidth = textSurface -> w;
            mHeight = textSurface -> h;
        }
        SDL_FreeSurface(textSurface);
    }
    return mTexture != NULL;
}


bool LTexture::loadFromFile(std::string path) {
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface  == NULL) {
        std::cout << "Unable to load image" << std::endl;
    } else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL) {
            std::cout << "Unable to create texture" << std::endl;
        } else {
            mWidth = loadedSurface -> w;
            mHeight = loadedSurface -> h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free() {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

void LTexture::render(int x, int y, SDL_Rect* clip) {
    rect = {x, y, mWidth, mHeight};
    if(clip != NULL) {
        rect.w = clip -> w;
        rect.w = clip -> h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &rect);
}

int LTexture::getHeight() {
    return mHeight;
}

int LTexture::getWidth() {
    return mWidth;
}

SDL_Rect LTexture::getRect() {
    return rect;
}

LTexture gTextTexture;
LTexture gPlayAgain;
LTexture gWinTexture;
LTexture gButtonSprite;
LTexture gMineLeft;

SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
// #endif 