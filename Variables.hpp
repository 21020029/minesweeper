LTexture gTextTexture;
LTexture gPlayWin;
LTexture gPlayLose;
LTexture gWinTexture;
LTexture gBackground;
LTexture gButtonSprite;

SDL_Rect gSpriteClips[BUTTON_SPRITE_TOTAL];
extern int gBoard[ROW_SIZE][COL_SIZE];
extern int gTable[ROW_SIZE][COL_SIZE];

int countLeft = MINE_COUNT;
int countTileLeft = ROW_SIZE * COL_SIZE;
bool loseGame= 0;
bool isWinning = 0;

stringstream mineLeft;