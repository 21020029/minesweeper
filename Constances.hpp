const int TILE_SIZE = 32;
const int BUTTON_SPRITE_TOTAL = 12;
const int MENU_ITEM = 2;

const int SCREEN_WITDH = 500;
const int SCREEN_HEIGHT = 500;

const int NUM_DIRECTION = 8;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

TTF_Font* gameOver = NULL;
TTF_Font* gamePlayAgain = NULL;

Mix_Music *winner = NULL;
Mix_Chunk *loser = NULL;
Mix_Chunk *click = NULL;

int mineCount;
int ROW_SIZE;
int COL_SIZE;
int DISTANCE_BETWEEN;
int countLeft;
int countTileLeft;
bool loseGame= 0;
bool isWinning = 0;

Uint32 frameStart;
unsigned int frameTime;
const int FPS = 30;
const int frameDelay = 1000 / FPS;

std::vector<std::vector<int>> gBoard, gTable;

const int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
const int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

enum title {
    BLANK, 
    MINE = 9,
    COVER, 
    FLAG
};

enum gameModeSelect {
    Easy,
    Medium, 
    Hard
};

enum MenuSelection {
    NEWGAME,
    EXIT,
    BACK,
    QUIT
};
