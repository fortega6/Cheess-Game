#ifndef SPCHESSSLOTWIN_H_
#define SPCHESSSLOTWIN_H_
#include <SDL.h>
#include <SDL_video.h>
//#include "SPTicTacToeWindow.h"
//#include "SPTicTacToe.h"

int n_slot;
int full_slot;

typedef enum {
	SP_SLOT_EVENT_SLOT1,
	SP_SLOT_EVENT_SLOT2,
	SP_SLOT_EVENT_SLOT3,
	SP_SLOT_EVENT_SLOT4,
	SP_SLOT_EVENT_SLOT5,
	SP_SLOT_EVENT_BACK,
	SP_SLOT_EVENT_LOAD,
	SP_SLOT_EVENT_QUIT,
	SP_SLOT_EVENT_INVALID_ARGUMENT,
	SP_SLOT_EVENT_NONE
} SP_SLOT_EVENT;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* slot1Texture;
	SDL_Texture* slot2Texture;
	SDL_Texture* slot3Texture;
	SDL_Texture* slot4Texture;
	SDL_Texture* slot5Texture;
	
	SDL_Texture* slot1ITexture;
	SDL_Texture* slot2ITexture;
	SDL_Texture* slot3ITexture;
	SDL_Texture* slot4ITexture;
	SDL_Texture* slot5ITexture;
	
	SDL_Texture* backTexture;
	SDL_Texture* loadTexture;
	SDL_Texture* loadITexture;
	int slot;
	//SPTicTacToe* game;
}SPSlotWin;

SPSlotWin* spSlotWindowCreate();
void spSlotWindowDraw(SPSlotWin*);
void spSlotWindowDestroy(SPSlotWin*);
SP_SLOT_EVENT spSlotWindowHandleEvent(SPSlotWin* src, SDL_Event* event);
void spSlotWindowHide(SPSlotWin* src);
void spSlotWindowShow(SPSlotWin* src);

#endif
