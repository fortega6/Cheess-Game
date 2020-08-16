#include "SPChessGameModeWin.h"
#include <assert.h>
#include <stdio.h>

int isClickOnOnePlayer(int x, int y) {
	if ((x >= 110 && x <= 200) && (y >= 90 && y <= 180)) {
		return 1;
	}
	return 0;
}

int isClickOnTwoPlayers(int x, int y) {
	if ((x >= 205 && x <= 295) && (y >= 90 && y <= 180)) {
		return 1;
	}
	return 0;
}

int isClickOnBackGameMode(int x, int y) {
	if ((x >= 205 && x <= 295) && (y >= 300 && y <= 330)) {
		return 1;
	}
	return 0;
}

int isClickOnNextGameMode(int x, int y, char gameMode) {
	if ((x >= 110 && x <= 200) && (y >= 300 && y <= 330) && (gameMode == '1')) {
		return 1;
	}
	return 0;
}

int isClickOnStartGameMode(int x, int y, char gameMode) {
	if ((x >= 110 && x <= 200) && (y >= 300 && y <= 330) && (gameMode == '2')) {
		return 1;
	}
	return 0;
}

SPGameModeWin* spGameModeWindowCreate() {
	SPGameModeWin* res = (SPGameModeWin*) calloc(sizeof(SPGameModeWin), sizeof(char));
	SDL_Surface* loadingSurface = NULL; //Used as temp surface
	if (res == NULL ) {
		printf("Couldn't create SPGameWin struct\n");
		return NULL ;
	}
	/*res->game = spTicTacToeCreate();
	if (res->game == NULL ) {
		printf("Couldn't create game\n");
		spGameModeWindowDestroy(res);
		return NULL ;
	}*/
	res->gameMode = '1';
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
		spGameModeWindowDestroy(res);
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->renderer == NULL ) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}

	//Create a background texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/menu2.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}
	res->bgTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->bgTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	
	//Create a game mode texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/gameMode.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}
	res->gameModeTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->gameModeTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it

	//Create a texture for one player active
	loadingSurface = SDL_LoadBMP("./graphics/images/one_player_acti.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}

	res->onePlayerTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->onePlayerTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for one player inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/one_player_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}

	res->onePlayerITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->onePlayerITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for two players active
	loadingSurface = SDL_LoadBMP("./graphics/images/two_players_acti.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}

	res->twoPlayersTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->twoPlayersTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for two players inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/two_players_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}

	res->twoPlayersITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->twoPlayersITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for back
	loadingSurface = SDL_LoadBMP("./graphics/images/back.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}

	res->backTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->backTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for start
	loadingSurface = SDL_LoadBMP("./graphics/images/start.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}

	res->startTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->startTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for next
	loadingSurface = SDL_LoadBMP("./graphics/images/next.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}

	res->nextTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->nextTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameModeWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	return res;
}

void spGameModeWindowDestroy(SPGameModeWin* src) {
	if (!src) {
		return;
	}
	//spTicTacToeDestroy(src->game);
	if (src->onePlayerTexture != NULL ) {
		SDL_DestroyTexture(src->onePlayerTexture);
	}
	if (src->onePlayerITexture != NULL ) {
		SDL_DestroyTexture(src->onePlayerITexture);
	}
	if (src->twoPlayersTexture != NULL ) {
		SDL_DestroyTexture(src->twoPlayersTexture);
	}
	if (src->twoPlayersITexture != NULL ) {
		SDL_DestroyTexture(src->twoPlayersITexture);
	}
	if (src->backTexture != NULL ) {
		SDL_DestroyTexture(src->backTexture);
	}
	if (src->startTexture != NULL ) {
		SDL_DestroyTexture(src->startTexture);
	}
	if (src->nextTexture != NULL ) {
		SDL_DestroyTexture(src->nextTexture);
	}
	if (src->gameModeTexture != NULL ) {
		SDL_DestroyTexture(src->gameModeTexture);
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

void spGameModeWindowDraw(SPGameModeWin* src) {
	if(src == NULL){
		return;
	}
	SDL_Rect bgR = { .x = 0, .y = 0, .h = 400, .w = 400 };
	SDL_Rect gameModeR = { .x = 110, .y = 30, .h = 30, .w = 190 };
	SDL_Rect onePlayerR = { .x = 110, .y = 90, .h = 30, .w = 90 };
	SDL_Rect twoPlayersR = { .x = 205, .y = 90, .h = 30, .w = 90 };
	SDL_Rect backR = { .x = 205, .y = 300, .h = 30, .w = 90 };
	SDL_Rect startOrNextR = { .x = 110, .y = 300, .h = 30, .w = 90 };

	SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
	SDL_RenderClear(src->renderer);
	
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &bgR);
	SDL_RenderCopy(src->renderer, src->gameModeTexture, NULL, &gameModeR);
	if(src->gameMode == '1'){
		SDL_RenderCopy(src->renderer, src->onePlayerTexture, NULL, &onePlayerR);
		SDL_RenderCopy(src->renderer, src->twoPlayersITexture, NULL, &twoPlayersR);
		SDL_RenderCopy(src->renderer, src->nextTexture, NULL, &startOrNextR);
		SDL_RenderCopy(src->renderer, src->backTexture, NULL, &backR);
	}else{
		SDL_RenderCopy(src->renderer, src->onePlayerITexture, NULL, &onePlayerR);
		SDL_RenderCopy(src->renderer, src->twoPlayersTexture, NULL, &twoPlayersR);
		SDL_RenderCopy(src->renderer, src->startTexture, NULL, &startOrNextR);
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

SP_GAME_MODE_EVENT spGameModeWindowHandleEvent(SPGameModeWin* src, SDL_Event* event) {
	if (event == NULL || src == NULL ) {
		return SP_GAME_MODE_EVENT_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnOnePlayer(event->button.x, event->button.y)) {
			src->gameMode = '1';
			return SP_GAME_MODE_EVENT_ONE_PLAYER;
		} else if (isClickOnTwoPlayers(event->button.x, event->button.y)) {
			src->gameMode = '2';
			return SP_GAME_MODE_EVENT_TWO_PLAYERS;
		} else if (isClickOnBackGameMode(event->button.x, event->button.y)) {
			return SP_GAME_MODE_EVENT_BACK;
		}else if (isClickOnNextGameMode(event->button.x, event->button.y, src->gameMode)) {
			return SP_GAME_MODE_EVENT_NEXT;
		}else if (isClickOnStartGameMode(event->button.x, event->button.y, src->gameMode)) {
			return SP_GAME_MODE_EVENT_START;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_GAME_MODE_EVENT_QUIT;
		}
		break;
	default:
		return SP_GAME_MODE_EVENT_NONE;
	}
	return SP_GAME_MODE_EVENT_NONE;
}

void spGameModeWindowHide(SPGameModeWin* src) {
	SDL_HideWindow(src->window);
}

void spGameModeWindowShow(SPGameModeWin* src) {
	SDL_ShowWindow(src->window);
}
