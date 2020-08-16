#include "SPChessGameWin.h"
#include <assert.h>
#include <stdio.h>


int isClickOnBoard(int x, int y) {
	if ((x >= 220 && x <= 780) && (y >= 25 && y <= 585)) {
		return 1;
	}
	return 0;
}

int isClickOnRestart(int x, int y) {
	if ((x >= 20 && x <= 200) && (y >= 30 && y <= 70)) {
		return 1;
	}
	return 0;
}

int isClickOnUndo(int x, int y) {
	if ((x >= 20 && x <= 200) && (y >= 180 && y <= 220)) {
		return 1;
	}
	return 0;
}

int isClickOnSave(int x, int y) {
	if ((x >= 20 && x <= 200) && (y >= 80 && y <= 120)) {
		return 1;
	}
	return 0;
}

int isClickOnLoadGame(int x, int y) {
	if ((x >= 20 && x <= 200) && (y >= 130 && y <= 170)) {
		return 1;
	}
	return 0;
}

int isClickOnMainMenu(int x, int y) {
	if ((x >= 20 && x <= 200) && (y >= 490 && y <= 530)) {
		return 1;
	}
	return 0;
}

int isClickOnExitGame(int x, int y) {
	if ((x >= 20 && x <= 200) && (y >= 540 && y <= 580)) {
		return 1;
	}
	return 0;
}

void loadStatusSlot2(){
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

	fclose(slotFile);
	
}

void saveStatusSlot(){

	FILE *fp;
	errno_t err;

	FILE * slotFile = NULL;
	
	///
	/// EX.3.1: Load the list of users and store the first element at users_firstUser
	///
	if(n_slot == 5){
		full_slot = 1;
		n_slot = 1;
	}else
		n_slot++;
		
    fopen_s(&slotFile, "slot.txt" ,"w");
    
    if (slotFile == NULL)
    {
        printf("Error: File doesn’t exist or cannot be opened\n");
    }
    else
    {
		fprintf(slotFile, "%d %d", n_slot, full_slot);	    
    }
	
	fclose ( slotFile );
}

SPGameWin* spGameWindowCreate() {
	SPGameWin* res = (SPGameWin*) calloc(sizeof(SPGameWin), sizeof(char));
	SDL_Surface* loadingSurface = NULL; //Used as temp surface
	if (res == NULL ) {
		printf("Couldn't create SPGameWin struct\n");
		return NULL ;
	}
	res->piece = '_';
	res->x = -1;
	res->y = -1;
	res->game = spChessCreate();
	if (res->game == NULL ) {
		printf("Couldn't create game\n");
		spGameWindowDestroy(res);
		return NULL ;
	}
	loadStatusSlot2();
	
	// Create an application window with the following settings:
	res->window = SDL_CreateWindow("Chess Game", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			800,                               // width, in pixels
			600,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->window == NULL ) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->renderer == NULL ) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}

	//Create a background texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/cleanBoard.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->bgTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->bgTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	
	//Create a board texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/board2.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->boardTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->boardTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	
	//Create a current player texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/currentPlayer.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->currentPlayerTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->currentPlayerTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	
	//Create a texture for the white color active
	loadingSurface = SDL_LoadBMP("./graphics/images/white.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format,   0,   0, 255 ));
	res->whiteTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->whiteTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for two players active
	loadingSurface = SDL_LoadBMP("./graphics/images/black.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255,   0, 255 ));
	res->blackTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->blackTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a restart texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/restart.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->restartTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->restartTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	
	//Create a save texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/save.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->saveTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->saveTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	
	//Create a save inactive texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/save_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->saveITexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->saveITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	
	//Create a load texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/load.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->loadTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->loadTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it

	//Create a undo texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/undo_acti.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->undoTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->undoTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	
	//Create a undo texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/undo_inac.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->undoITexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->undoITexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	
		//Create a board texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/mainMenu.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->mainMenuTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->mainMenuTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	
	//Create a board texture:
	loadingSurface = SDL_LoadBMP("./graphics/images/exit.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->exitTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->exitTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it
	
	//Create a texture for the black pawn 
	loadingSurface = SDL_LoadBMP("./graphics/images/blackPawn.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->blackPawnTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->blackPawnTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the white pawn
	loadingSurface = SDL_LoadBMP("./graphics/images/whitePawn.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->whitePawnTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->whitePawnTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for the black bishop
	loadingSurface = SDL_LoadBMP("./graphics/images/blackBishop.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->blackBishopTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->blackBishopTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the white pawn
	loadingSurface = SDL_LoadBMP("./graphics/images/whiteBishop.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->whiteBishopTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->whiteBishopTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for the black rook 
	loadingSurface = SDL_LoadBMP("./graphics/images/blackRook.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->blackRookTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->blackRookTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the white rook
	loadingSurface = SDL_LoadBMP("./graphics/images/whiteRook.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->whiteRookTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->whiteRookTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for the black knight
	loadingSurface = SDL_LoadBMP("./graphics/images/blackKnight.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->blackKnightTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->blackKnightTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the white knight
	loadingSurface = SDL_LoadBMP("./graphics/images/whiteKnight.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->whiteKnightTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->whiteKnightTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for the black queen
	loadingSurface = SDL_LoadBMP("./graphics/images/blackQueen.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->blackQueenTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->blackQueenTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the white queen
	loadingSurface = SDL_LoadBMP("./graphics/images/whiteQueen.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->whiteQueenTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->whiteQueenTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	
	//Create a texture for the black king
	loadingSurface = SDL_LoadBMP("./graphics/images/blackKing.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->blackKingTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->blackKingTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Create a texture for the white king
	loadingSurface = SDL_LoadBMP("./graphics/images/whiteKing.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	//We use SetColorKey to make texture background transparent
	//This function will make the magenta background transparent
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->whiteKingTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->whiteKingTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	return res;
}

void spGameWindowDestroy(SPGameWin* src) {
	if (!src) {
		return;
	}
	spChessDestroy(src->game);
	if (src->blackPawnTexture != NULL ) {
		SDL_DestroyTexture(src->blackPawnTexture);
	}
	if (src->whitePawnTexture != NULL ) {
		SDL_DestroyTexture(src->whitePawnTexture);
	}
	if (src->blackBishopTexture != NULL ) {
		SDL_DestroyTexture(src->blackBishopTexture);
	}
	if (src->whiteBishopTexture != NULL ) {
		SDL_DestroyTexture(src->whiteBishopTexture);
	}
	if (src->blackRookTexture != NULL ) {
		SDL_DestroyTexture(src->blackRookTexture);
	}
	if (src->whiteRookTexture != NULL ) {
		SDL_DestroyTexture(src->whiteRookTexture);
	}
	if (src->blackKnightTexture != NULL ) {
		SDL_DestroyTexture(src->blackKnightTexture);
	}
	if (src->whiteKnightTexture != NULL ) {
		SDL_DestroyTexture(src->whiteKnightTexture);
	}
	if (src->blackQueenTexture != NULL ) {
		SDL_DestroyTexture(src->blackQueenTexture);
	}
	if (src->whiteQueenTexture != NULL ) {
		SDL_DestroyTexture(src->whiteQueenTexture);
	}
	if (src->blackKingTexture != NULL ) {
		SDL_DestroyTexture(src->blackKingTexture);
	}
	if (src->whiteKingTexture != NULL ) {
		SDL_DestroyTexture(src->whiteKingTexture);
	}
	if (src->restartTexture != NULL ) {
		SDL_DestroyTexture(src->restartTexture);
	}
	if (src->saveTexture != NULL ) {
		SDL_DestroyTexture(src->saveTexture);
	}
	if (src->saveITexture != NULL ) {
		SDL_DestroyTexture(src->saveTexture);
	}
	if (src->loadTexture != NULL ) {
		SDL_DestroyTexture(src->loadTexture);
	}
	if (src->undoTexture != NULL ) {
		SDL_DestroyTexture(src->undoTexture);
	}
	if (src->undoITexture != NULL ) {
		SDL_DestroyTexture(src->undoITexture);
	}
	if (src->mainMenuTexture != NULL ) {
		SDL_DestroyTexture(src->mainMenuTexture);
	}
	if (src->exitTexture != NULL ) {
		SDL_DestroyTexture(src->exitTexture);
	}
	if (src->whiteTexture != NULL ) {
		SDL_DestroyTexture(src->whiteTexture);
	}
	if (src->blackTexture != NULL ) {
		SDL_DestroyTexture(src->blackTexture);
	}
	if (src->currentPlayerTexture != NULL ) {
		SDL_DestroyTexture(src->currentPlayerTexture);
	}
	if (src->boardTexture != NULL ) {
		SDL_DestroyTexture(src->boardTexture);
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

void spGameWindowDraw(SPGameWin* src) {
	if(src == NULL){
		return;
	}
	SDL_Rect rec = 			{ .x = 0, .y = 0, .w = 800, .h = 600 };
	SDL_Rect boardR = 		{ .x = 220, .y = 25, .w = 560, .h = 560 };
	SDL_Rect currentPlayerR = { .x = 30, .y = 250, .h = 40, .w = 150 };
	SDL_Rect whiteR = 		{ .x = 70, .y = 300, .w = 70, .h = 80 };
	SDL_Rect blackR = 		{ .x = 70, .y = 300, .w = 70, .h = 80 };
	SDL_Rect restartR = 	{ .x = 20, .y = 30, .h = 40, .w = 180 };
	SDL_Rect saveR = 		{ .x = 20, .y = 80, .h = 40, .w = 180 };
	SDL_Rect loadR = 		{ .x = 20, .y = 130, .h = 40, .w = 180 };
	SDL_Rect undoR = 		{ .x = 20, .y = 180, .h = 40, .w = 180 };
	SDL_Rect mainMenuR = 	{ .x = 20, .y = 490, .h = 40, .w = 180 };
	SDL_Rect exitR = 		{ .x = 20, .y = 540, .h = 40, .w = 180 };
	SDL_Rect areYouR = 		{ .x = src->x-35, .y = src->y-35, .w = 70, .h = 70 };
	
	SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
	SDL_RenderClear(src->renderer);
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &rec);
	SDL_RenderCopy(src->renderer, src->boardTexture, NULL, &boardR);
	SDL_RenderCopy(src->renderer, src->currentPlayerTexture, NULL, &currentPlayerR);
	SDL_RenderCopy(src->renderer, src->restartTexture, NULL, &restartR);
	SDL_RenderCopy(src->renderer, src->loadTexture, NULL, &loadR);
	
	if(src->game->currentPlayer == SP_WHITE)
		SDL_RenderCopy(src->renderer, src->whiteTexture, NULL, &whiteR);
	else
		SDL_RenderCopy(src->renderer, src->blackTexture, NULL, &blackR);
	
	if(spChessChange(src->game))
		SDL_RenderCopy(src->renderer, src->saveTexture, NULL, &saveR);
	else
		SDL_RenderCopy(src->renderer, src->saveITexture, NULL, &saveR);
	
	if(src->game->gameMode == '1'){
		if(!isEmptyHistory())
			SDL_RenderCopy(src->renderer, src->undoTexture, NULL, &undoR);
		else
			SDL_RenderCopy(src->renderer, src->undoITexture, NULL, &undoR);
	}
	SDL_RenderCopy(src->renderer, src->mainMenuTexture, NULL, &mainMenuR);
	SDL_RenderCopy(src->renderer, src->exitTexture, NULL, &exitR);

	int i = 0, j = 0;
	for (i = 0; i < SP_N_ROWS; i++) {
		for (j = 0; j < SP_N_COLUMNS; j++) {
			rec.x = (j * 70) + 220;
			rec.y = (i * 70) + 25;
			rec.h = 70;
			rec.w = 70;
			if (src->game->board[i][j] == SP_BLACK_PAWN_SYMBOL) {
				if(src->piece != SP_BLACK_PAWN_SYMBOL || i != src->game->row_o || j != src->game->col_o)
					SDL_RenderCopy(src->renderer, src->blackPawnTexture, NULL, &rec);
				else
					SDL_RenderCopy(src->renderer, src->blackPawnTexture, NULL, &areYouR);
			} else if (src->game->board[i][j] == SP_WHITE_PAWN_SYMBOL) {
				if(src->piece != SP_WHITE_PAWN_SYMBOL || i != src->game->row_o || j != src->game->col_o)
					SDL_RenderCopy(src->renderer, src->whitePawnTexture, NULL, &rec);
				else
					SDL_RenderCopy(src->renderer, src->whitePawnTexture, NULL, &areYouR);
			} else if (src->game->board[i][j] == SP_BLACK_BISHOP_SYMBOL) {
				if(src->piece != SP_BLACK_BISHOP_SYMBOL || i != src->game->row_o || j != src->game->col_o)
					SDL_RenderCopy(src->renderer, src->blackBishopTexture, NULL, &rec);
				else
					SDL_RenderCopy(src->renderer, src->blackBishopTexture, NULL, &areYouR);
			} else if (src->game->board[i][j] == SP_WHITE_BISHOP_SYMBOL) {
				if(src->piece != SP_WHITE_BISHOP_SYMBOL || i != src->game->row_o || j != src->game->col_o)
					SDL_RenderCopy(src->renderer, src->whiteBishopTexture, NULL, &rec);
				else
					SDL_RenderCopy(src->renderer, src->whiteBishopTexture, NULL, &areYouR);
			} else if (src->game->board[i][j] == SP_BLACK_ROOK_SYMBOL) {
				if(src->piece != SP_BLACK_ROOK_SYMBOL || i != src->game->row_o || j != src->game->col_o)
					SDL_RenderCopy(src->renderer, src->blackRookTexture, NULL, &rec);
				else
					SDL_RenderCopy(src->renderer, src->blackRookTexture, NULL, &areYouR);
			} else if (src->game->board[i][j] == SP_WHITE_ROOK_SYMBOL) {
				if(src->piece != SP_WHITE_ROOK_SYMBOL || i != src->game->row_o || j != src->game->col_o)
					SDL_RenderCopy(src->renderer, src->whiteRookTexture, NULL, &rec);
				else
					SDL_RenderCopy(src->renderer, src->whiteRookTexture, NULL, &areYouR);
			} else if (src->game->board[i][j] == SP_BLACK_KNIGHT_SYMBOL) {
				if(src->piece != SP_BLACK_KNIGHT_SYMBOL || i != src->game->row_o || j != src->game->col_o)
					SDL_RenderCopy(src->renderer, src->blackKnightTexture, NULL, &rec);
				else
					SDL_RenderCopy(src->renderer, src->blackKnightTexture, NULL, &areYouR);
			} else if (src->game->board[i][j] == SP_WHITE_KNIGHT_SYMBOL) {
				if(src->piece != SP_WHITE_KNIGHT_SYMBOL || i != src->game->row_o || j != src->game->col_o)
					SDL_RenderCopy(src->renderer, src->whiteKnightTexture, NULL, &rec);
				else
					SDL_RenderCopy(src->renderer, src->whiteKnightTexture, NULL, &areYouR);
			}else if (src->game->board[i][j] == SP_BLACK_QUEEN_SYMBOL) {
				if(src->piece != SP_BLACK_QUEEN_SYMBOL || i != src->game->row_o || j != src->game->col_o)
					SDL_RenderCopy(src->renderer, src->blackQueenTexture, NULL, &rec);
				else
					SDL_RenderCopy(src->renderer, src->blackQueenTexture, NULL, &areYouR);
			} else if (src->game->board[i][j] == SP_WHITE_QUEEN_SYMBOL) {
				if(src->piece != SP_WHITE_QUEEN_SYMBOL || i != src->game->row_o || j != src->game->col_o)
					SDL_RenderCopy(src->renderer, src->whiteQueenTexture, NULL, &rec);
				else
					SDL_RenderCopy(src->renderer, src->whiteQueenTexture, NULL, &areYouR);
			}else if (src->game->board[i][j] == SP_BLACK_KING_SYMBOL) {
				if(src->piece != SP_BLACK_KING_SYMBOL || i != src->game->row_o || j != src->game->col_o)
					SDL_RenderCopy(src->renderer, src->blackKingTexture, NULL, &rec);
				else
					SDL_RenderCopy(src->renderer, src->blackKingTexture, NULL, &areYouR);
			} else if (src->game->board[i][j] == SP_WHITE_KING_SYMBOL) {
				if(src->piece != SP_WHITE_KING_SYMBOL || i != src->game->row_o || j != src->game->col_o)
					SDL_RenderCopy(src->renderer, src->whiteKingTexture, NULL, &rec);
				else
					SDL_RenderCopy(src->renderer, src->whiteKingTexture, NULL, &areYouR);
			}
		}
	}
	SDL_RenderPresent(src->renderer);
}

SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SDL_Event* event) {
	char slot[200];
	const SDL_MessageBoxButtonData buttons[] = {
		{ /* .flags, .buttonid, .text */        0, 0, "no" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
	   { /* .colors (.r, .g, .b) */
			/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 255,   0,   0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
			{   0, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
			{ 255, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
			{   0,   0, 255 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
			{ 255,   0, 255 }
		}
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		NULL, /* .window */
		"Save Game", /* .title */
		"Do you want to save the changes?", /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};
	int buttonid;
	
	if (event == NULL || src == NULL ) {
		return SP_GAME_EVENT_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEMOTION:
		src->x = event->button.x;
		src->y = event->button.y;
		break;
	case SDL_MOUSEBUTTONDOWN:
		src->x = event->button.x;
		src->y = event->button.y;

		if(event->button.button == SDL_BUTTON_LEFT){
			if(isClickOnBoard(event->button.x, event->button.y)){
				spChessSetPosOrigin(src->game, (event->button.y - 25) / 70, (event->button.x - 220) / 70);
				src->piece = spChessGetPiece(src->game, src->game->row_o, src->game->col_o);
			}
		}/*else if(event->button.button == SDL_BUTTON_RIGHT){
			if(isClickOnBoard(event->button.x, event->button.y)){
				spChessSetPosOrigin(src->game, (event->button.y - 25) / 70, (event->button.x - 220) / 70);
				src->piece = spChessGetPiece(src->game, src->game->row_o, src->game->col_o);
				
			}
		}*/
		break;
	case SDL_MOUSEBUTTONUP:
		if(event->button.button == SDL_BUTTON_LEFT && isClickOnBoard(src->x, src->y) && isClickOnBoard(event->button.x, event->button.y)){
			spChessSetPosDestiny(src->game, (event->button.y - 25) / 70, (event->button.x - 220) / 70);
			spChessSetMove(src->game);
			src->x = -1;
			src->y = -1;
			if(spChessError(src->game) == CHESS_NOT_CONTAIN_YOUR_PIECE){
				return SP_GAME_EVENT_NOT_CONTAIN_YOUR_PIECE;
			}else if(spChessError(src->game) == CHESS_ILLEGAL_MOVE){
				return SP_GAME_EVENT_ILLEGAL_MOVE;
			}else if(src->game->check == CHESS_CHECK_WHITE){
				return SP_GAME_EVENT_CHECK_WHITE;
			}else if(src->game->check == CHESS_CHECK_BLACK){
				return SP_GAME_EVENT_CHECK_BLACK;
			}else if(src->game->checkMate == CHESS_CHECKMATE_BLACK){
				return SP_GAME_EVENT_CHECKMATE_BLACK;
			}else if(src->game->checkMate == CHESS_CHECKMATE_WHITE){
				return SP_GAME_EVENT_CHECKMATE_WHITE;
			}
		}else if(isClickOnRestart(event->button.x, event->button.y)){
			spChessRestart(src->game);
		}else if(isClickOnUndo(event->button.x, event->button.y) && src->game->gameMode == '1'){
			spChessUndo(src->game);
		}else if(isClickOnSave(event->button.x, event->button.y) && spChessChange(src->game)){
			saveStatusSlot();
			sprintf_s(slot,200, "slot%d.XML", n_slot);
			spChessSetSlot(src->game, slot);
			spChessSave(src->game);
		}else if(isClickOnLoadGame(event->button.x, event->button.y)){
			return SP_GAME_EVENT_LOAD;
		}else if(isClickOnMainMenu(event->button.x, event->button.y)){
			if(spChessChange(src->game)){
				if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
					SDL_Log("error displaying message box");
					return 1;
				}
			
				if (buttonid == -1) {
					SDL_Log("no selection");
				} else if (buttonid == 0) {
					return SP_GAME_EVENT_MAIN_MENU;
				}if (buttonid == 1){
					saveStatusSlot();
					sprintf_s(slot,200,"slot%d.XML", n_slot);
					spChessSetSlot(src->game, slot);
					spChessSave(src->game);
				}else{
					return SP_GAME_EVENT_NONE;
				}
			}
			return SP_GAME_EVENT_MAIN_MENU;
		}else if(isClickOnExitGame(event->button.x, event->button.y)){
			if(spChessChange(src->game)){
				if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
					SDL_Log("error displaying message box");
					return 1;
				}
			
				if (buttonid == -1) {
					SDL_Log("no selection");
				} else if (buttonid == 0) {
					return SP_GAME_EVENT_EXIT;
				}if (buttonid == 1){
					saveStatusSlot();
					sprintf_s(slot, 200, "slot%d.XML", n_slot);
					spChessSetSlot(src->game, slot);
					spChessSave(src->game);
				}else{
					return SP_GAME_EVENT_NONE;
				}
			}
			return SP_GAME_EVENT_EXIT;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_GAME_EVENT_QUIT;
		}
		break;
	default:
		return SP_GAME_EVENT_NONE;
	}
	return SP_GAME_EVENT_NONE;
}
