#ifndef SPCHESSMAINWIN_H_
#define SPCHESSMAINWIN_H_
#include <SDL.h>

typedef enum {
	SP_MAIN_EXIT, SP_MAIN_LOAD, SP_MAIN_NEW_GAME, SP_MAIN_INVALID_ARGUMENT, SP_MAIN_NONE
} SP_MAIN_EVENT;

typedef struct {
	//SDL_Window* window;
	SDL_Window* mainWindow;
	SDL_Renderer* mainRenderer;
	SDL_Texture* menuTexture;
	SDL_Texture* newGameTexture;
	SDL_Texture* startTexture;
	SDL_Texture* loadTexture;
	SDL_Texture* exitTexture;
} SPMainWin;

SPMainWin* spMainWindowCreate();
void spMainWindowDraw(SPMainWin* src);
void spMainWindowDestroy(SPMainWin* src);
void spMainWindowHide(SPMainWin* src);
void spMainWindowShow(SPMainWin* src);
SP_MAIN_EVENT spMainWindowHandleEvent(SPMainWin* src, SDL_Event* event);

#endif
