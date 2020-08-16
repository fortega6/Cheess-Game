#ifndef SPSHESSEGAMEWIN_H_
#define SPSHESSEGAMEWIN_H_
#include <SDL.h>
#include <SDL_video.h>
#include "SPChess.h"

int n_slot;
int full_slot;

typedef enum {
	SP_GAME_EVENT_X_WON,
	SP_GAME_EVENT_O_WON,
	SP_GAME_EVENT_TIE,
	SP_GAME_EVENT_BLACK_PAWN,
	SP_GAME_EVENT_WHITE_PAWN,
	SP_GAME_EVENT_BLACK_BISHOP,
	SP_GAME_EVENT_WHITE_BISHOP,
	SP_GAME_EVENT_BLACK_ROOK,
	SP_GAME_EVENT_WHITE_ROOK,
	SP_GAME_EVENT_BLACK_KNIGHT,
	SP_GAME_EVENT_WHITE_KNIGHT,
	SP_GAME_EVENT_BLACK_QUEEN,
	SP_GAME_EVENT_WHITE_QUEEN,
	SP_GAME_EVENT_BLACK_KING,
	SP_GAME_EVENT_WHITE_KING,
	SP_GAME_EVENT_QUIT,
	SP_GAME_EVENT_EXIT,
	SP_GAME_EVENT_LOAD,
	SP_GAME_EVENT_INVALID_ARGUMENT,
	SP_GAME_EVENT_MAIN_MENU,
	SP_GAME_EVENT_NONE,
	SP_GAME_EVENT_NOT_CONTAIN_YOUR_PIECE,
	SP_GAME_EVENT_ILLEGAL_MOVE,
	SP_GAME_EVENT_CHECK_WHITE,
	SP_GAME_EVENT_CHECK_BLACK,
	SP_GAME_EVENT_CHECKMATE_WHITE,
	SP_GAME_EVENT_CHECKMATE_BLACK
} SP_GAME_EVENT;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* currentPlayerTexture;
	SDL_Texture* whiteTexture;
	SDL_Texture* blackTexture;
	SDL_Texture* boardTexture;
	SDL_Texture* restartTexture;
	SDL_Texture* saveTexture;
	SDL_Texture* saveITexture;
	SDL_Texture* loadTexture;
	SDL_Texture* undoTexture;
	SDL_Texture* undoITexture;
	SDL_Texture* mainMenuTexture;
	SDL_Texture* exitTexture;
	SDL_Texture* blackPawnTexture;
	SDL_Texture* whitePawnTexture;
	SDL_Texture* blackBishopTexture;
	SDL_Texture* whiteBishopTexture;
	SDL_Texture* blackRookTexture;
	SDL_Texture* whiteRookTexture;	
	SDL_Texture* blackKnightTexture;
	SDL_Texture* whiteKnightTexture;
	SDL_Texture* blackQueenTexture;
	SDL_Texture* whiteQueenTexture;
	SDL_Texture* blackKingTexture;
	SDL_Texture* whiteKingTexture;
	int x;
	int y;
	char piece;
	SPChess* game;
}SPGameWin;

SPGameWin* spGameWindowCreate();
void spGameWindowDraw(SPGameWin*);
void spGameWindowDestroy(SPGameWin*);
SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SDL_Event* event);


#endif
