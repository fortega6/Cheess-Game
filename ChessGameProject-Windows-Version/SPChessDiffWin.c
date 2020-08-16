#include "SPChessDiffWin.h"
#include <assert.h>
#include <stdio.h>

int isClickOnNoob(int x, int y) {
	if ((x >= 130 && x <= 270) && (y >= 50 && y <= 80)) {
		return 1;
	}
	return 0;
}

int isClickOnEasy(int x, int y) {
	if ((x >= 130 && x <= 270) && (y >= 90 && y <= 120)) {
		return 1;
	}
	return 0;
}

int isClickOnModerate(int x, int y) {
	if ((x >= 130 && x <= 270) && (y >= 130 && y <= 160)) {
		return 1;
	}
	return 0;
}

int isClickOnHard(int x, int y) {
	if ((x >= 130 && x <= 270) && (y >= 170 && y <= 200)) {
		return 1;
	}
	return 0;
}

int isClickOnExpert(int x, int y) {
	if ((x >= 130 && x <= 270) && (y >= 210 && y <= 240)) {
		return 1;
	}
	return 0;
}

int isClickOnBackDiff(int x, int y) {
	if ((x >= 205 && x <= 295) && (y >= 300 && y <= 330)) {
		return 1;
	}
	return 0;
}

int isClickOnNextDiff(int x, int y) {
	if ((x >= 110 && x <= 200) && (y >= 300 && y <= 330)) {
		return 1;
	}
	return 0;
}

SPDiffWin* spDiffWindowCreate() {
	SPDiffWin* res = (SPDiffWin*) calloc(sizeof(SPDiffWin), sizeof(char));
	SDL_Surface* loadingSurface = NULL; //Used as temp surface
	if (res == NULL ) {
		printf("Couldn't create SPGameWin struct\n");
		return NULL ;
	}
	/*res->game = spTicTacToeCreate();
	if (res->game == NULL ) {
		printf("Couldn't create game\n");
		spDiffWindowDestroy(res);
		return NULL ;
	}*/
	res->diff = '2';
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
		spDiffWindowDestroy(res);
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->renderer == NULL ) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}

	//Create a background texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/menu2.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	res->bgTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->bgTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	
	//Create a difficulty texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/difficulty.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	res->difficultyTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->difficultyTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it

	//Create a texture for noob active
	loadingSurface = SDL_LoadBMP("./graphics/images/noob_acti.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}

	res->noobTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->noobTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the slot 1 inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/noob_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}

	res->noobITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->noobITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for the slot 2 active
	loadingSurface = SDL_LoadBMP("./graphics/images/easy_acti.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}

	res->easyTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->easyTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the slot 2 inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/easy_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}

	res->easyITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->easyITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for the slot 3 active
	loadingSurface = SDL_LoadBMP("./graphics/images/moderate_acti.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}

	res->moderateTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->moderateTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the slot 3 inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/moderate_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}

	res->moderateITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->moderateITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for the slot 4 active
	loadingSurface = SDL_LoadBMP("./graphics/images/hard_acti.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}

	res->hardTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->easyTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the slot 4 inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/hard_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}

	res->hardITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->hardITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for the slot 5 active
	loadingSurface = SDL_LoadBMP("./graphics/images/expert_acti.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}

	res->expertTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->expertTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the slot 5 inactive
	loadingSurface = SDL_LoadBMP("./graphics/images/expert_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}

	res->expertITexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->expertITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for back
	loadingSurface = SDL_LoadBMP("./graphics/images/back.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}

	res->backTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->backTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for next
	loadingSurface = SDL_LoadBMP("./graphics/images/next.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}

	res->nextTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->nextTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spDiffWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	return res;
}

void spDiffWindowDestroy(SPDiffWin* src) {
	if (!src) {
		return;
	}
	//spTicTacToeDestroy(src->game);
	if (src->noobTexture != NULL ) {
		SDL_DestroyTexture(src->noobTexture);
	}
	if (src->noobITexture != NULL ) {
		SDL_DestroyTexture(src->noobITexture);
	}
	if (src->easyTexture != NULL ) {
		SDL_DestroyTexture(src->easyTexture);
	}
	if (src->easyITexture != NULL ) {
		SDL_DestroyTexture(src->easyITexture);
	}
	if (src->moderateTexture != NULL ) {
		SDL_DestroyTexture(src->moderateTexture);
	}
	if (src->moderateITexture != NULL ) {
		SDL_DestroyTexture(src->moderateITexture);
	}
	if (src->hardTexture != NULL ) {
		SDL_DestroyTexture(src->hardTexture);
	}
	if (src->hardITexture != NULL ) {
		SDL_DestroyTexture(src->hardITexture);
	}
	if (src->expertTexture != NULL ) {
		SDL_DestroyTexture(src->expertTexture);
	}
	if (src->expertITexture != NULL ) {
		SDL_DestroyTexture(src->expertITexture);
	}
	if (src->difficultyTexture != NULL ) {
		SDL_DestroyTexture(src->difficultyTexture);
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

void spDiffWindowDraw(SPDiffWin* src) {
	if(src == NULL){
		return;
	}

	SDL_Rect bgR = { .x = 0, .y = 0, .h = 400, .w = 400 };
	SDL_Rect difficultyR = { .x = 130, .y = 15, .h = 30, .w = 140 };
	SDL_Rect noobR = { .x = 130, .y = 50, .h = 30, .w = 140 };
	SDL_Rect easyR = { .x = 130, .y = 90, .h = 30, .w = 140 };
	SDL_Rect moderateR = { .x = 130, .y = 130, .h = 30, .w = 140 };
	SDL_Rect hardR = { .x = 130, .y = 170, .h = 30, .w = 140 };
	SDL_Rect expertR = { .x = 130, .y = 210, .h = 30, .w = 140 };
	SDL_Rect backR = { .x = 205, .y = 300, .h = 30, .w = 90 };
	SDL_Rect nextR = { .x = 110, .y = 300, .h = 30, .w = 90};
	
	SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
	SDL_RenderClear(src->renderer);
	
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &bgR);
	SDL_RenderCopy(src->renderer, src->difficultyTexture, NULL, &difficultyR);
	if(src->diff == '1')
		SDL_RenderCopy(src->renderer, src->noobTexture, NULL, &noobR);
	else
		SDL_RenderCopy(src->renderer, src->noobITexture, NULL, &noobR);
	if(src->diff == '2')
		SDL_RenderCopy(src->renderer, src->easyTexture, NULL, &easyR);
	else
		SDL_RenderCopy(src->renderer, src->easyITexture, NULL, &easyR);
	if(src->diff == '3')
		SDL_RenderCopy(src->renderer, src->moderateTexture, NULL, &moderateR);
	else
		SDL_RenderCopy(src->renderer, src->moderateITexture, NULL, &moderateR);
	if(src->diff == '4')
		SDL_RenderCopy(src->renderer, src->hardTexture, NULL, &hardR);
	else
		SDL_RenderCopy(src->renderer, src->hardITexture, NULL, &hardR);
	if(src->diff == '5')
		SDL_RenderCopy(src->renderer, src->expertTexture, NULL, &expertR);
	else
		SDL_RenderCopy(src->renderer, src->expertITexture, NULL, &expertR);
	SDL_RenderCopy(src->renderer, src->backTexture, NULL, &backR);
	SDL_RenderCopy(src->renderer, src->nextTexture, NULL, &nextR);
	
	SDL_RenderPresent(src->renderer);
}

SP_DIFF_EVENT spDiffWindowHandleEvent(SPDiffWin* src, SDL_Event* event) {
	if (event == NULL || src == NULL ) {
		return SP_DIFF_EVENT_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnNoob(event->button.x, event->button.y)) {
			src->diff = '1';
			return SP_DIFF_EVENT_NOOB;
		} else if (isClickOnEasy(event->button.x, event->button.y)) {
			src->diff = '2';
			return SP_DIFF_EVENT_EASY;
		} else if (isClickOnModerate(event->button.x, event->button.y)) {
			src->diff = '3';
			return SP_DIFF_EVENT_MODERATE;
		} else if (isClickOnHard(event->button.x, event->button.y)) {
			src->diff = '4';
			return SP_DIFF_EVENT_HARD;
		} else if (isClickOnExpert(event->button.x, event->button.y)) {
			src->diff = '5';
			return SP_DIFF_EVENT_EXPERT;
		}else if (isClickOnBackDiff(event->button.x, event->button.y)) {
			return SP_DIFF_EVENT_BACK;
		}else if (isClickOnNextDiff(event->button.x, event->button.y)) {
			return SP_DIFF_EVENT_NEXT;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_DIFF_EVENT_QUIT;
		}
		break;
	default:
		return SP_DIFF_EVENT_NONE;
	}
	return SP_DIFF_EVENT_NONE;
}

void spDiffWindowHide(SPDiffWin* src) {
	SDL_HideWindow(src->window);
}

void spDiffWindowShow(SPDiffWin* src) {
	SDL_ShowWindow(src->window);
}
