#include "SPChessGUIManager.h"
#include <stdio.h>
#include <stdlib.h>

SPGuiManager* spManagerCreate() {
	SPGuiManager* res = (SPGuiManager*) malloc(sizeof(SPGuiManager));
	if (res == NULL ) {
		return NULL ;
	}
	res->mainWin = spMainWindowCreate();
	if (res->mainWin == NULL ) {
		free(res);
		return NULL ;
	}
	res->slotWin = NULL;
	res->gameModeWin = NULL;
	res->diffWin = NULL;
	res->colorWin = NULL;
	res->gameWin = NULL;
	res->activeWin = SP_MAIN_WINDOW_ACTIVE;
	return res;
}
void spManagerDestroy(SPGuiManager* src) {
	if (!src) {
		return;
	}
	if (src->activeWin == SP_GAME_WINDOW_ACTIVE) {
		spGameWindowDestroy(src->gameWin);
	}
	spMainWindowDestroy(src->mainWin);
	free(src);
}
void spManagerDraw(SPGuiManager* src) {
	if (!src) {
		return;
	}
	if (src->activeWin == SP_MAIN_WINDOW_ACTIVE) {
		spMainWindowDraw(src->mainWin);
	} else if (src->activeWin == SP_GAME_WINDOW_ACTIVE){
		spGameWindowDraw(src->gameWin);
	} else if (src->activeWin == SP_SLOT_WINDOW_ACTIVE){
		spSlotWindowDraw(src->slotWin);
	}else if (src->activeWin == SP_GAME_MODE_WINDOW_ACTIVE){
		spGameModeWindowDraw(src->gameModeWin);
	}else if (src->activeWin == SP_DIFF_WINDOW_ACTIVE){
		spDiffWindowDraw(src->diffWin);
	}else{
		spColorWindowDraw(src->colorWin);
	}
}
SP_MANAGER_EVENET handleManagerDueToMainEvent(SPGuiManager* src,
		SP_MAIN_EVENT event) {
	if (src == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (event == SP_MAIN_NEW_GAME) {
		spMainWindowHide(src->mainWin);
		src->gameModeWin = spGameModeWindowCreate();
		if (src->gameModeWin == NULL ) {
			printf("Couldn't create game window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_GAME_MODE_WINDOW_ACTIVE;
	}else if(event == SP_MAIN_LOAD){
		spMainWindowHide(src->mainWin);
		src->slotWin = spSlotWindowCreate();
		if (src->slotWin == NULL ) {
			printf("Couldn't create load window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_SLOT_WINDOW_ACTIVE;
	}
	if (event == SP_MAIN_EXIT) {
		return SP_MANAGER_QUTT;
	}
	return SP_MANAGER_NONE;
}

SP_MANAGER_EVENET handleManagerDueToGameEvent(SPGuiManager* src,
		SP_GAME_EVENT event) {
	if (event == SP_GAME_EVENT_NONE || src == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (event ==  SP_GAME_EVENT_NOT_CONTAIN_YOUR_PIECE) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "The specified position does not contain your piece",
				NULL );
		return SP_MANAGER_NONE;
	} else if (event == SP_GAME_EVENT_ILLEGAL_MOVE) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Illegal move",
				NULL );
		return SP_MANAGER_NONE;
	}else if (event == SP_GAME_EVENT_CHECK_WHITE) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Check", "Check: White King is threatened!\n",
				NULL );
		return SP_MANAGER_NONE;
	}else if (event == SP_GAME_EVENT_CHECK_BLACK) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Check", "Check: Black King is threatened!\n",
				NULL );
		return SP_MANAGER_NONE;
	}else if (event == SP_GAME_EVENT_CHECKMATE_WHITE) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Checkmate", "Checkmate! Black player wins the game\n",
				NULL );
		spChessRestart(src->gameWin->game);
		return SP_MANAGER_NONE;
	}else if (event == SP_GAME_EVENT_CHECKMATE_BLACK) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Checkmate", "Checkmate! White player wins the game\n",
				NULL );
		spChessRestart(src->gameWin->game);
		return SP_MANAGER_NONE;
	}else if (event == SP_GAME_EVENT_TIE) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over",
				"it's a tie", NULL );
	}else if(event  == SP_GAME_EVENT_LOAD){
		spGameWindowDestroy(src->gameWin);
		src->gameWin = NULL;
		spGameModeWindowDestroy(src->gameModeWin);
		src->gameModeWin = NULL;
		spDiffWindowDestroy(src->diffWin);
		src->diffWin = NULL;
		spColorWindowDestroy(src->colorWin);
		src->colorWin = NULL;
		src->slotWin = spSlotWindowCreate();
		if (src->slotWin == NULL ) {
			printf("Couldn't create load window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_SLOT_WINDOW_ACTIVE;
		return SP_MANAGER_NONE;
	}else if (event == SP_GAME_EVENT_EXIT) {
		spGameWindowDestroy(src->gameWin);
		src->gameWin = NULL;
		spGameModeWindowDestroy(src->gameModeWin);
		src->gameModeWin = NULL;
		spDiffWindowDestroy(src->diffWin);
		src->diffWin = NULL;
		spColorWindowDestroy(src->colorWin);
		src->colorWin = NULL;
		src->activeWin = SP_MAIN_WINDOW_ACTIVE;
		spMainWindowShow(src->mainWin);
		return SP_MANAGER_QUTT;
	}
	
	spSlotWindowDestroy(src->slotWin);
	src->slotWin = NULL;
	spGameWindowDestroy(src->gameWin);
	src->gameWin = NULL;
	spGameModeWindowDestroy(src->gameModeWin);
	src->gameModeWin = NULL;
	spDiffWindowDestroy(src->diffWin);
	src->diffWin = NULL;
	spColorWindowDestroy(src->colorWin);
	src->colorWin = NULL;
	src->activeWin = SP_MAIN_WINDOW_ACTIVE;
	spMainWindowShow(src->mainWin);
	return SP_MANAGER_NONE;
}

SP_MANAGER_EVENET handleManagerDueToSlotEvent(SPGuiManager* src,
		SP_SLOT_EVENT event) {
	char slot[200];
	if (event == SP_SLOT_EVENT_NONE || src == NULL 
									|| event == SP_SLOT_EVENT_SLOT1 
									|| event == SP_SLOT_EVENT_SLOT2
									|| event == SP_SLOT_EVENT_SLOT3
									|| event == SP_SLOT_EVENT_SLOT4
									|| event == SP_SLOT_EVENT_SLOT5) {
		return SP_MANAGER_NONE;
	}
	
	if(event == SP_SLOT_EVENT_LOAD){
		src->gameWin = spGameWindowCreate();
		if(src->slotWin->slot <= n_slot)
			sprintf_s(slot, 200, "slot%d.XML", (n_slot - src->slotWin->slot)+1);
		else
			sprintf_s(slot, 200,"slot%d.XML", (5 - src->slotWin->slot)+n_slot+1);
		spChessSetSlot(src->gameWin->game, slot);
		spChessLoad(src->gameWin->game);
		if (src->gameWin == NULL ) {
			printf("Couldn't create game window\n");
			return SP_MANAGER_QUTT;
		}
		spSlotWindowDestroy(src->slotWin);
		src->slotWin = NULL;
		src->activeWin = SP_GAME_WINDOW_ACTIVE;
		
	}else{
		spSlotWindowDestroy(src->slotWin);
		src->slotWin = NULL;
		src->activeWin = SP_MAIN_WINDOW_ACTIVE;
		spMainWindowShow(src->mainWin);
	}
	/*if (event == SP_GAME_EVENT_X_WON) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "X won",
				NULL );
	} else if (event == SP_GAME_EVENT_O_WON) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "O won",
				NULL );
	} else if (event == SP_GAME_EVENT_TIE) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over",
				"it's a tie", NULL );
	}*/
	return SP_MANAGER_NONE;
}

SP_MANAGER_EVENET handleManagerDueToGameModeEvent(SPGuiManager* src,
		SP_GAME_MODE_EVENT event) {
	if (event == SP_GAME_MODE_EVENT_NONE || event == SP_GAME_MODE_EVENT_ONE_PLAYER
										 || event == SP_GAME_MODE_EVENT_TWO_PLAYERS
										 || src == NULL) {
		return SP_MANAGER_NONE;
	}
	
	if (event == SP_GAME_MODE_EVENT_NEXT) {
		spGameModeWindowHide(src->gameModeWin);
		src->diffWin = spDiffWindowCreate();
		if (src->diffWin == NULL ) {
			printf("Couldn't create diff window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_DIFF_WINDOW_ACTIVE;
	}else if (event == SP_GAME_MODE_EVENT_START){
		spGameModeWindowHide(src->gameModeWin);
		src->gameWin = spGameWindowCreate();
		spChessSetGameMode(src->gameWin->game, src->gameModeWin->gameMode);
		if (src->gameWin == NULL ) {
			printf("Couldn't create game window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_GAME_WINDOW_ACTIVE;
	}else{
		spGameModeWindowDestroy(src->gameModeWin);
		src->gameModeWin = NULL;
		src->activeWin = SP_MAIN_WINDOW_ACTIVE;
		spMainWindowShow(src->mainWin);
	}
	
	return SP_MANAGER_NONE;
}

SP_MANAGER_EVENET handleManagerDueToDiffEvent(SPGuiManager* src,
		SP_DIFF_EVENT event) {
	if (event == SP_DIFF_EVENT_NONE || event == SP_DIFF_EVENT_NOOB
										 || event == SP_DIFF_EVENT_EASY
										 || event == SP_DIFF_EVENT_MODERATE
										 || event == SP_DIFF_EVENT_HARD
										 || event == SP_DIFF_EVENT_EXPERT
										 || src == NULL) {
		return SP_MANAGER_NONE;
	}
	
	if (event == SP_DIFF_EVENT_NEXT) {
		spDiffWindowHide(src->diffWin);
		src->colorWin = spColorWindowCreate();
		if (src->colorWin == NULL ) {
			printf("Couldn't create color window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_COLOR_WINDOW_ACTIVE;
	}else if(event == SP_DIFF_EVENT_BACK){
		spDiffWindowDestroy(src->diffWin);
		src->diffWin = NULL;
		spGameModeWindowShow(src->gameModeWin);
		src->activeWin = SP_GAME_MODE_WINDOW_ACTIVE;
	}else{
		spGameModeWindowDestroy(src->gameModeWin);
		src->gameModeWin = NULL;
		spDiffWindowDestroy(src->diffWin);
		src->diffWin = NULL;
		src->activeWin = SP_MAIN_WINDOW_ACTIVE;
		spMainWindowShow(src->mainWin);
	}
	
	return SP_MANAGER_NONE;
}

SP_MANAGER_EVENET handleManagerDueToColorEvent(SPGuiManager* src,
		SP_COLOR_EVENT event) {
	if (event == SP_COLOR_EVENT_NONE || event == SP_COLOR_EVENT_WHITE
									 || event == SP_COLOR_EVENT_BLACK
									 || src == NULL) {
		return SP_MANAGER_NONE;
	}
	
	if (event == SP_COLOR_EVENT_START) {
		spColorWindowHide(src->colorWin);
		src->gameWin = spGameWindowCreate();
		spChessSetGameMode(src->gameWin->game, src->gameModeWin->gameMode);
		spChessSetCurrentPlayer(src->gameWin->game, src->colorWin->color);
		spChessSetDiff(src->gameWin->game, src->diffWin->diff);
		if (src->gameWin == NULL ) {
			printf("Couldn't create game window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_GAME_WINDOW_ACTIVE;
	}else if(event == SP_COLOR_EVENT_BACK){
		spColorWindowDestroy(src->colorWin);
		src->colorWin = NULL;
		src->activeWin = SP_DIFF_WINDOW_ACTIVE;
		spDiffWindowShow(src->diffWin);
	}else{
		spGameModeWindowDestroy(src->gameModeWin);
		src->gameModeWin = NULL;
		spDiffWindowDestroy(src->diffWin);
		src->diffWin = NULL;
		spColorWindowDestroy(src->colorWin);
		src->colorWin = NULL;
		src->activeWin = SP_MAIN_WINDOW_ACTIVE;
		spMainWindowShow(src->mainWin);
	}
	
	return SP_MANAGER_NONE;
}

SP_MANAGER_EVENET spManagerHandleEvent(SPGuiManager* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (src->activeWin == SP_MAIN_WINDOW_ACTIVE) {
		SP_MAIN_EVENT mainEvent = spMainWindowHandleEvent(src->mainWin, event);
		return handleManagerDueToMainEvent(src, mainEvent);
	} else if (src->activeWin == SP_GAME_WINDOW_ACTIVE) {
		SP_GAME_EVENT gameEvent = spGameWindowHandleEvent(src->gameWin, event);
		spManagerDraw(src);
		return handleManagerDueToGameEvent(src, gameEvent);
	} else if (src->activeWin == SP_SLOT_WINDOW_ACTIVE) {
		SP_SLOT_EVENT slotEvent = spSlotWindowHandleEvent(src->slotWin, event);
		spManagerDraw(src);
		return handleManagerDueToSlotEvent(src, slotEvent);
	}else if (src->activeWin == SP_GAME_MODE_WINDOW_ACTIVE){
		SP_GAME_MODE_EVENT gameModeEvent = spGameModeWindowHandleEvent(src->gameModeWin, event);
		spManagerDraw(src);
		return handleManagerDueToGameModeEvent(src, gameModeEvent);
	}else if (src->activeWin == SP_DIFF_WINDOW_ACTIVE){
		SP_DIFF_EVENT diffEvent = spDiffWindowHandleEvent(src->diffWin, event);
		spManagerDraw(src);
		return handleManagerDueToDiffEvent(src, diffEvent);
	}else{
		SP_COLOR_EVENT colorEvent = spColorWindowHandleEvent(src->colorWin, event);
		spManagerDraw(src);
		return handleManagerDueToColorEvent(src, colorEvent);
	}
	return SP_MANAGER_NONE;
}
