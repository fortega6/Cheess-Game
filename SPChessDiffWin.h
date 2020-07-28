#ifndef SPCHESSDIFFWIN_H_
#define SPCHESSDIFFWIN_H_
#include <SDL.h>
#include <SDL_video.h>
//#include "SPTicTacToeWindow.h"
//#include "SPTicTacToe.h"

typedef enum {
	SP_DIFF_EVENT_NOOB,
	SP_DIFF_EVENT_EASY,
	SP_DIFF_EVENT_MODERATE,
	SP_DIFF_EVENT_HARD,
	SP_DIFF_EVENT_EXPERT,
	SP_DIFF_EVENT_QUIT,
	SP_DIFF_EVENT_BACK,
	SP_DIFF_EVENT_NEXT,
	SP_DIFF_EVENT_INVALID_ARGUMENT,
	SP_DIFF_EVENT_NONE
} SP_DIFF_EVENT;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* difficultyTexture;
	SDL_Texture* noobTexture;
	SDL_Texture* easyTexture;
	SDL_Texture* moderateTexture;
	SDL_Texture* hardTexture;
	SDL_Texture* expertTexture;
	
	SDL_Texture* noobITexture;
	SDL_Texture* easyITexture;
	SDL_Texture* slotITexture;
	SDL_Texture* moderateITexture;
	SDL_Texture* hardITexture;
	SDL_Texture* expertITexture;
	
	SDL_Texture* backTexture;
	SDL_Texture* nextTexture;
	
	char diff;
	//SPTicTacToe* game;
}SPDiffWin;

SPDiffWin* spDiffWindowCreate();
void spDiffWindowDraw(SPDiffWin*);
void spDiffWindowDestroy(SPDiffWin*);
SP_DIFF_EVENT spDiffWindowHandleEvent(SPDiffWin* src, SDL_Event* event);
void spDiffWindowHide(SPDiffWin* src);
void spDiffWindowShow(SPDiffWin* src);

#endif
