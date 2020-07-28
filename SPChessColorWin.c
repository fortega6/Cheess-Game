#include "SPChessColorWin.h"
#include <assert.h>
#include <stdio.h>

int isClickOnWhite(int x, int y) {
	if ((x >= 110 && x <= 200) && (y >= 90 && y <= 180)) {
		return 1;
	}
	return 0;
}

int isClickOnBlack(int x, int y) {
	if ((x >= 205 && x <= 295) && (y >= 90 && y <= 180)) {
		return 1;
	}
	return 0;
}

int isClickOnBackColor(int x, int y) {
	if ((x >= 205 && x <= 295) && (y >= 300 && y <= 330)) {
		return 1;
	}
	return 0;
}


int isClickOnStartColor(int x, int y) {
	if ((x >= 110 && x <= 200) && (y >= 300 && y <= 330)) {
		return 1;
	}
	return 0;
}

SPColorWin* spColorWindowCreate() {
	SPColorWin* res = (SPColorWin*) calloc(sizeof(SPColorWin), sizeof(char));
	SDL_Surface* loadingSurface = NULL; //Used as temp surface
	if (res == NULL ) {
		printf("Couldn't create SPGameWin struct\n");
		return NULL ;
	}
	/*res->game = spTicTacToeCreate();
	if (res->game == NULL ) {
		printf("Couldn't create game\n");
		spColorWindowDestroy(res);
		return NULL ;
	}*/
	res->color = SP_WHITE;
	// Create an application window with the following settings:
	res->window = SDL_CreateWindow("Chess Game", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			400,                               // width, in pixels
			400,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->window == NULL ) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->renderer == NULL ) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}

	//Create a background texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/menu2.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}
	res->bgTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->bgTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	
	//Create a background texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/selectYourColor.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}
	res->colorTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->colorTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it

	//Create a texture for the white color active
	loadingSurface = SDL_LoadBMP("./graphics/images/white.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format,   0,   0, 255 ));
	res->whiteTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->whiteTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for  inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/white_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}

	res->whiteITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->whiteITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for two players active
	loadingSurface = SDL_LoadBMP("./graphics/images/black.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255,   0, 255 ));
	res->blackTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->blackTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for two players inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/black_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}

	res->blackITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->blackITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for back
	loadingSurface = SDL_LoadBMP("./graphics/images/back.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}

	res->backTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->backTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for start
	loadingSurface = SDL_LoadBMP("./graphics/images/start.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}

	res->startTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->startTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spColorWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	return res;
}

void spColorWindowDestroy(SPColorWin* src) {
	if (!src) {
		return;
	}
	//spTicTacToeDestroy(src->game);
	if (src->whiteTexture != NULL ) {
		SDL_DestroyTexture(src->whiteTexture);
	}
	if (src->whiteITexture != NULL ) {
		SDL_DestroyTexture(src->whiteITexture);
	}
	if (src->blackTexture != NULL ) {
		SDL_DestroyTexture(src->blackTexture);
	}
	if (src->blackITexture != NULL ) {
		SDL_DestroyTexture(src->blackITexture);
	}
	if (src->backTexture != NULL ) {
		SDL_DestroyTexture(src->backTexture);
	}
	if (src->startTexture != NULL ) {
		SDL_DestroyTexture(src->startTexture);
	}
	if (src->colorTexture != NULL ) {
		SDL_DestroyTexture(src->colorTexture);
	}
	if (src->bgTexture != NULL ) {
		SDL_DestroyTexture(src->bgTexture);
	}
	if (src->renderer != NULL ) {
		SDL_DestroyRenderer(src->renderer);
	}
	if (src->window != NULL ) {
		SDL_DestroyWindow(src->window);
	}
	free(src);
}

void spColorWindowDraw(SPColorWin* src) {
	if(src == NULL){
		return;
	}
	SDL_Rect bgR = { .x = 0, .y = 0, .h = 400, .w = 400 };
	SDL_Rect colorR = { .x = 110, .y = 20, .h = 30, .w = 190 };
	SDL_Rect whiteR = { .x = 205, .y = 90, .h = 60, .w = 60 };
	SDL_Rect blackR = { .x = 110, .y = 90, .h = 60, .w = 60 };
	SDL_Rect backR = { .x = 205, .y = 300, .h = 30, .w = 90 };
	SDL_Rect startR = { .x = 110, .y = 300, .h = 30, .w = 90 };

	SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
	SDL_RenderClear(src->renderer);
	
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &bgR);
	SDL_RenderCopy(src->renderer, src->colorTexture, NULL, &colorR);
	if(src->color == SP_WHITE){
		SDL_RenderCopy(src->renderer, src->whiteTexture, NULL, &whiteR);
		SDL_RenderCopy(src->renderer, src->blackITexture, NULL, &blackR);
		SDL_RenderCopy(src->renderer, src->startTexture, NULL, &startR);
		SDL_RenderCopy(src->renderer, src->backTexture, NULL, &backR);
	}else{
		SDL_RenderCopy(src->renderer, src->whiteITexture, NULL, &whiteR);
		SDL_RenderCopy(src->renderer, src->blackTexture, NULL, &blackR);
		SDL_RenderCopy(src->renderer, src->startTexture, NULL, &startR);
		SDL_RenderCopy(src->renderer, src->backTexture, NULL, &backR);
	}

	/*int i = 0, j = 0;
	for (i = 0; i < SP_N_ROWS; i++) {
		for (j = 0; j < SP_N_COLUMNS; j++) {
			rec.x = j * 200;
			rec.y = i * 200;
			rec.h = 200;
			rec.w = 200;
			if (src->game->board[i][j] == SP_PLAYER_1_SYMBOL) {
				SDL_RenderCopy(src->renderer, src->xTexture, NULL, &rec);
			} else if (src->game->board[i][j] == SP_PLAYER_2_SYMBOL) {
				SDL_RenderCopy(src->renderer, src->oTexture, NULL, &rec);
			}
		}
	}*/
	SDL_RenderPresent(src->renderer);
}

SP_COLOR_EVENT spColorWindowHandleEvent(SPColorWin* src, SDL_Event* event) {
	if (event == NULL || src == NULL ) {
		return SP_COLOR_EVENT_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnWhite(event->button.x, event->button.y)) {
			src->color = SP_BLACK;
			return SP_COLOR_EVENT_WHITE;
		} else if (isClickOnBlack(event->button.x, event->button.y)) {
			src->color = SP_WHITE;
			return SP_COLOR_EVENT_BLACK;
		} else if (isClickOnBackColor(event->button.x, event->button.y)) {
			return SP_COLOR_EVENT_BACK;
		}else if (isClickOnStartColor(event->button.x, event->button.y)) {
			return SP_COLOR_EVENT_START;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_COLOR_EVENT_QUIT;
		}
		break;
	default:
		return SP_COLOR_EVENT_NONE;
	}
	return SP_COLOR_EVENT_NONE;
}

void spColorWindowHide(SPColorWin* src) {
	SDL_HideWindow(src->window);
}

void spColorWindowShow(SPColorWin* src) {
	SDL_ShowWindow(src->window);
}
