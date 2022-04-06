const int TILE_SIZE = 32;
const int BUTTON_SPRITE_TOTAL = 12;

const int MINE_COUNT = 12;
const int ROW_SIZE  = 10;
const int COL_SIZE = 10;

const int SCREEN_WITDH = 500;
const int SCREEN_HEIGHT = 500;
const int DISTANCE_BETWEEN = (SCREEN_HEIGHT  - ROW_SIZE + TILE_SIZE) / 2;

const int NUM_DIRECTION = 8;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

TTF_Font* gameOver = NULL;
TTF_Font* gameWin = NULL;
TTF_Font* gameLose = NULL;

const int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
const int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};