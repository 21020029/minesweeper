#include <bits/stdc++.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Constances.hpp"
#include "Texture.hpp"
#include "Button.hpp"

#include "Windows.hpp"
#include "loadMedia.hpp"
#include "Menu.hpp"
#include "Game.hpp"
#include "Time.hpp"

int main(int argc, char *argv[]) {
    initProgram();
    if(!loadMedia()) {
        std::cout << "Failed to load media\n";
    } else {
        bool quit = false;
        bool quitGame = false;
        while(not quit) {
            int menuOptions = makeMenu();
            switch(menuOptions) {
                case NEWGAME: {
                    int Mode = showGameMode();
                    switch (Mode) {
                        case Easy: {
                            quitGame = false;
                            mineCount = 10;
                            ROW_SIZE = 9;
                            COL_SIZE = 9;
                            initTable(ROW_SIZE, COL_SIZE);
                            break;
                        }   
                        case Hard: {
                            quitGame = false;
                            mineCount = 25;
                            ROW_SIZE = 11;
                            COL_SIZE = 11;
                            SCREEN_HEIGHT = 800;
                            SCREEN_WIDTH = 800;
                            initTable(ROW_SIZE, COL_SIZE);
                            break;
                        }
                        case QUIT: {
                            quitGame = true;
                            quit = true;
                            break;
                        }
                        default: {
                            quitGame = true;
                            break;
                        }
                    }
                    SDL_Event e;
                    createGame();
                    while(!quitGame) {
                        Time timer;
                        while(!loseGame && !quitGame && !isWinning) {
                            frameStart = SDL_GetTicks();
                            SDL_RenderClear(gRenderer);
                            while(SDL_PollEvent(&e)) {
                                if(e.type == SDL_QUIT) {
                                    quitGame = true;
                                    quit = true;
                                } else if(e.type == SDL_KEYDOWN and e.key.keysym.sym == SDLK_ESCAPE) {
                                    quitGame = true;
                                    for (int i = 0; i < ROW_SIZE + 2; ++i) 
                                        fill(begin(gBoard[i]), end(gBoard[i]), BLANK);
                                    for (int i = 0; i < ROW_SIZE + 2; ++i) 
                                        fill(begin(gTable[i]), end(gTable[i]), COVER);
                                }
                                for (int i = 1; i <= ROW_SIZE; ++i) {
                                    for (int j = 1; j <= COL_SIZE; ++j) {
                                        gButtons[i][j].handleEvent(&e);
                                    }
                                }
                                isWinning = checkWinGame();
                            }
                            for (int i = 1; i <= ROW_SIZE; ++i) {
                                for (int j = 1; j <= COL_SIZE; ++j) {
                                    gButtons[i][j].render(i, j);
                                }
                            }
                            timer.printTime();
                            mineManager();
                            flagManager();
                            SDL_RenderPresent(gRenderer);
                            frameTime = SDL_GetTicks() - frameStart;
						    if (frameDelay > frameTime)
							    SDL_Delay(frameDelay - frameTime);
                        }
                        playAgain(quitGame, quit);
                    }
                    break;
                }
                case EXIT: {
                    quit = true;
                    break;
                }
            }
        }
    }
    exitGame();
    return 0;
}