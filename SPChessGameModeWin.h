#ifndef SPCHESSGAMEMODEWIN_H_
#define SPCHESSGAMEMODEWIN_H_
#include <SDL.h>
#include <SDL_video.h>
//#include "SPTicTacToeWindow.h"
//#include "SPTicTacToe.h"

typedef enum {
	SP_GAME_MODE_EVENT_ONE_PLAYER,
	SP_GAME_MODE_EVENT_TWO_PLAYERS,
	SP_GAME_MODE_EVENT_NEXT,
	SP_GAME_MODE_EVENT_START,
	SP_GAME_MODE_EVENT_BACK,
	SP_GAME_MODE_EVENT_QUIT,
	SP_GAME_MODE_EVENT_INVALID_ARGUMENT,
	SP_GAME_MODE_EVENT_NONE
} SP_GAME_MODE_EVENT;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* gameModeTexture;
	SDL_Texture* onePlayerTexture;
	SDL_Texture* twoPlayersTexture;
	SDL_Texture* onePlayerITexture;
	SDL_Texture* twoPlayersITexture;
	SDL_Texture* startTexture;
	SDL_Texture* nextTexture;
	SDL_Texture* backTexture;
	char gameMode;
}SPGameModeWin;

SPGameModeWin* spGameModeWindowCreate();
void spGameModeWindowDraw(SPGameModeWin*);
void spGameModeWindowDestroy(SPGameModeWin*);
SP_GAME_MODE_EVENT spGameModeWindowHandleEvent(SPGameModeWin* src, SDL_Event* event);
void spGameModeWindowHide(SPGameModeWin* src);
void spGameModeWindowShow(SPGameModeWin* src);

#endif
