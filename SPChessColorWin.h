#ifndef SPCHESSCOLORWIN_H_
#define SPCHESSCOLORWIN_H_
#include <SDL.h>
#include <SDL_video.h>
//#include "SPTicTacToeWindow.h"
#include "SPChess.h"

typedef enum {
	SP_COLOR_EVENT_WHITE,
	SP_COLOR_EVENT_BLACK,
	SP_COLOR_EVENT_START,
	SP_COLOR_EVENT_BACK,
	SP_COLOR_EVENT_QUIT,
	SP_COLOR_EVENT_INVALID_ARGUMENT,
	SP_COLOR_EVENT_NONE
} SP_COLOR_EVENT;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* colorTexture;
	SDL_Texture* whiteTexture;
	SDL_Texture* blackTexture;
	SDL_Texture* whiteITexture;
	SDL_Texture* blackITexture;
	SDL_Texture* startTexture;
	SDL_Texture* backTexture;
	SP_COLOR color;
}SPColorWin;

SPColorWin* spColorWindowCreate();
void spColorWindowDraw(SPColorWin*);
void spColorWindowDestroy(SPColorWin*);
SP_COLOR_EVENT spColorWindowHandleEvent(SPColorWin* src, SDL_Event* event);
void spColorWindowHide(SPColorWin* src);
void spColorWindowShow(SPColorWin* src);

#endif
