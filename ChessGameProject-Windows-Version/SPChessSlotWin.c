#include "SPChessSlotWin.h"
#include <assert.h>
#include <stdio.h>

int isClickOnSlot1(int x, int y) {
	if ((x >= 130 && x <= 270) && (y >= 50 && y <= 80)) {
		return 1;
	}
	return 0;
}

int isClickOnSlot2(int x, int y) {
	if ((x >= 130 && x <= 270) && (y >= 90 && y <= 120)) {
		return 1;
	}
	return 0;
}

int isClickOnSlot3(int x, int y) {
	if ((x >= 130 && x <= 270) && (y >= 130 && y <= 160)) {
		return 1;
	}
	return 0;
}

int isClickOnSlot4(int x, int y) {
	if ((x >= 130 && x <= 270) && (y >= 170 && y <= 200)) {
		return 1;
	}
	return 0;
}

int isClickOnSlot5(int x, int y) {
	if ((x >= 130 && x <= 270) && (y >= 210 && y <= 240)) {
		return 1;
	}
	return 0;
}

int isClickOnBack(int x, int y) {
	if ((x >= 110 && x <= 200) && (y >= 300 && y <= 330)) {
		return 1;
	}
	return 0;
}

int isClickOnLoadSlot(int x, int y) {
	if ((x >= 205 && x <= 295) && (y >= 300 && y <= 330)) {
		return 1;
	}
	return 0;
}

void loadStatusSlot(){
	FILE * slotFile = NULL;
	
	///
	/// EX.3.1: Load the list of users and store the first element at users_firstUser
	///
    fopen_s(&slotFile, "slot.txt" ,"r");
    
    if (slotFile == NULL)
    {
        printf("Error: File doesn’t exist or cannot be opened\n");
    }
    else
    {
		fscanf_s(slotFile, "%d %d", &n_slot, &full_slot);	    
    }
	
}

SPSlotWin* spSlotWindowCreate() {
	SPSlotWin* res = (SPSlotWin*) calloc(sizeof(SPSlotWin), sizeof(char));
	SDL_Surface* loadingSurface = NULL; //Used as temp surface
	if (res == NULL ) {
		printf("Couldn't create SPGameWin struct\n");
		return NULL ;
	}
	res->slot = 0;
	/*res->game = spTicTacToeCreate();
	if (res->game == NULL ) {
		printf("Couldn't create game\n");
		spSlotWindowDestroy(res);
		return NULL ;
	}*/
	// Create an application window with the following settings:
	res->window = SDL_CreateWindow("Chess_Game", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			400,                               // width, in pixels
			400,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	loadStatusSlot();
	// Check that the window was successfully created
	if (res->window == NULL ) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->renderer == NULL ) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}

	//Create a background texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/menu2.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	res->bgTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->bgTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it

	//Create a texture for the slot 1 active
	loadingSurface = SDL_LoadBMP("./graphics/images/slot1_acti.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}

	res->slot1Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->slot1Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the slot 1 inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/slot1_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}

	res->slot1ITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->slot1ITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for the slot 2 active
	loadingSurface = SDL_LoadBMP("./graphics/images/slot2_acti.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}

	res->slot2Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->slot2Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the slot 2 inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/slot2_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}

	res->slot2ITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->slot2ITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for the slot 3 active
	loadingSurface = SDL_LoadBMP("./graphics/images/slot3_acti.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}

	res->slot3Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->slot3Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the slot 3 inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/slot3_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}

	res->slot3ITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->slot3ITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for the slot 4 active
	loadingSurface = SDL_LoadBMP("./graphics/images/slot4_acti.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}

	res->slot4Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->slot2Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the slot 4 inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/slot4_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}

	res->slot4ITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->slot4ITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for the slot 5 active
	loadingSurface = SDL_LoadBMP("./graphics/images/slot5_acti.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}

	res->slot5Texture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->slot5Texture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the slot 5 inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/slot5_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}

	res->slot5ITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->slot5ITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for back
	loadingSurface = SDL_LoadBMP("./graphics/images/back.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}

	res->backTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->backTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for load
	loadingSurface = SDL_LoadBMP("./graphics/images/load.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}

	res->loadTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->loadTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for load
	loadingSurface = SDL_LoadBMP("./graphics/images/load_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}

	res->loadITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->loadITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spSlotWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	return res;
}

void spSlotWindowDestroy(SPSlotWin* src) {
	if (!src) {
		return;
	}
	//spTicTacToeDestroy(src->game);
	if (src->slot1Texture != NULL ) {
		SDL_DestroyTexture(src->slot1Texture);
	}
	if (src->slot1ITexture != NULL ) {
		SDL_DestroyTexture(src->slot1ITexture);
	}
	if (src->slot2Texture != NULL ) {
		SDL_DestroyTexture(src->slot2Texture);
	}
	if (src->slot2ITexture != NULL ) {
		SDL_DestroyTexture(src->slot2ITexture);
	}
	if (src->slot3Texture != NULL ) {
		SDL_DestroyTexture(src->slot3Texture);
	}
	if (src->slot3ITexture != NULL ) {
		SDL_DestroyTexture(src->slot3ITexture);
	}
	if (src->slot4Texture != NULL ) {
		SDL_DestroyTexture(src->slot4Texture);
	}
	if (src->slot4ITexture != NULL ) {
		SDL_DestroyTexture(src->slot4ITexture);
	}
	if (src->slot5Texture != NULL ) {
		SDL_DestroyTexture(src->slot5Texture);
	}
	if (src->slot5ITexture != NULL ) {
		SDL_DestroyTexture(src->slot5ITexture);
	}
	if (src->backTexture != NULL ) {
		SDL_DestroyTexture(src->backTexture);
	}
	if (src->loadTexture != NULL ) {
		SDL_DestroyTexture(src->loadTexture);
	}
	if (src->loadITexture != NULL ) {
		SDL_DestroyTexture(src->loadITexture);
	}
	if (src->renderer != NULL ) {
		SDL_DestroyRenderer(src->renderer);
	}
	if (src->window != NULL ) {
		SDL_DestroyWindow(src->window);
	}
	free(src);
}

void spSlotWindowDraw(SPSlotWin* src) {
	int i;
	if(src == NULL){
		return;
	}
	SDL_Rect bgR = { .x = 0, .y = 0, .h = 400, .w = 400 };
	SDL_Rect slot1R = { .x = 130, .y = 50, .h = 30, .w = 140 };
	SDL_Rect slot2R = { .x = 130, .y = 90, .h = 30, .w = 140 };
	SDL_Rect slot3R = { .x = 130, .y = 130, .h = 30, .w = 140 };
	SDL_Rect slot4R = { .x = 130, .y = 170, .h = 30, .w = 140 };
	SDL_Rect slot5R = { .x = 130, .y = 210, .h = 30, .w = 140 };
	SDL_Rect backR = { .x = 110, .y = 300, .h = 30, .w = 90 };
	SDL_Rect loadR = { .x = 205, .y = 300, .h = 30, .w = 90 };

	SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
	SDL_RenderClear(src->renderer);
	
	
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &bgR);
	for (i = 1; i <= n_slot; i++)
	{
		if(i == 1 || full_slot){
			if(src->slot == 1)
				SDL_RenderCopy(src->renderer, src->slot1Texture, NULL, &slot1R);
			else
				SDL_RenderCopy(src->renderer, src->slot1ITexture, NULL, &slot1R);
		}
		if(i == 2 || full_slot){
			if(src->slot == 2)
				SDL_RenderCopy(src->renderer, src->slot2Texture, NULL, &slot2R);
			else
				SDL_RenderCopy(src->renderer, src->slot2ITexture, NULL, &slot2R);
		}
		if(i == 3 || full_slot){
			if(src->slot == 3)
				SDL_RenderCopy(src->renderer, src->slot3Texture, NULL, &slot3R);
			else
				SDL_RenderCopy(src->renderer, src->slot3ITexture, NULL, &slot3R);
		}
		if(i == 4 || full_slot){
			if(src->slot == 4)
				SDL_RenderCopy(src->renderer, src->slot4Texture, NULL, &slot4R);
			else
				SDL_RenderCopy(src->renderer, src->slot4ITexture, NULL, &slot4R);
		}
		if(i == 5 || full_slot){
			if(src->slot == 5)
				SDL_RenderCopy(src->renderer, src->slot5Texture, NULL, &slot5R);
			else
				SDL_RenderCopy(src->renderer, src->slot5ITexture, NULL, &slot5R);
		}
	}
	
	SDL_RenderCopy(src->renderer, src->backTexture, NULL, &backR);
	if(src->slot != 0)		
		SDL_RenderCopy(src->renderer, src->loadTexture, NULL, &loadR);
	else
		SDL_RenderCopy(src->renderer, src->loadITexture, NULL, &loadR);

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

SP_SLOT_EVENT spSlotWindowHandleEvent(SPSlotWin* src, SDL_Event* event) {
	if (event == NULL || src == NULL ) {
		return SP_SLOT_EVENT_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnSlot1(event->button.x, event->button.y)) {
			src->slot = 1;
			return SP_SLOT_EVENT_SLOT1;
		} else if (isClickOnSlot2(event->button.x, event->button.y)) {
			src->slot = 2;
			return SP_SLOT_EVENT_SLOT2;
		} else if (isClickOnSlot3(event->button.x, event->button.y)) {
			src->slot = 3;
			return SP_SLOT_EVENT_SLOT3;
		} else if (isClickOnSlot4(event->button.x, event->button.y)) {
			src->slot = 4;
			return SP_SLOT_EVENT_SLOT4;
		} else if (isClickOnSlot5(event->button.x, event->button.y)) {
			src->slot = 5;
			return SP_SLOT_EVENT_SLOT5;
		} else if (isClickOnBack(event->button.x, event->button.y)) {
			return SP_SLOT_EVENT_BACK;
		} else if (isClickOnLoadSlot(event->button.x, event->button.y) && src->slot != 0) {
			return SP_SLOT_EVENT_LOAD;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_SLOT_EVENT_QUIT;
		}
		break;
	default:
		return SP_SLOT_EVENT_NONE;
	}
	return SP_SLOT_EVENT_NONE;
}

void spSlotWindowHide(SPSlotWin* src) {
	SDL_HideWindow(src->window);
}

void spSlotWindowShow(SPSlotWin* src) {
	SDL_ShowWindow(src->window);
}
