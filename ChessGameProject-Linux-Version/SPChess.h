#ifndef SPTICTACTOE_H_
#define SPTICTACTOE_H_
#include <stdbool.h>

#define SP_N_ROWS 8
#define SP_N_COLUMNS 8
#define DIM_MATRIX 8
#define SP_PLAYER_1_SYMBOL 'X'
#define SP_PLAYER_2_SYMBOL 'O'
#define SP_BLACK_PAWN_SYMBOL	 'P'
#define SP_BLACK_BISHOP_SYMBOL	 'B'
#define SP_BLACK_ROOK_SYMBOL	 'R'
#define SP_BLACK_KNIGHT_SYMBOL	 'N'
#define SP_BLACK_QUEEN_SYMBOL	 'Q'
#define SP_BLACK_KING_SYMBOL	 'K'
#define SP_WHITE_PAWN_SYMBOL	 'p'
#define SP_WHITE_BISHOP_SYMBOL	 'b'
#define SP_WHITE_ROOK_SYMBOL	 'r'
#define SP_WHITE_KNIGHT_SYMBOL	 'n'
#define SP_WHITE_QUEEN_SYMBOL	 'q'
#define SP_WHITE_KING_SYMBOL	 'k'
#define SP_EMPTY_ENTRY '_'

#define SCORE_PAWN		1
#define SCORE_KNIGHT	3
#define SCORE_BISHOP	3
#define SCORE_ROOK		5
#define SCORE_QUEEN		9
#define SCORE_KING		100

typedef enum {
	SP_BLACK,
	SP_WHITE
} SP_COLOR;

typedef enum {FALSE, TRUE} boolean;

typedef enum
{
	CHESS_NOERR,
	CHESS_NOT_CONTAIN_YOUR_PIECE,
	CHESS_ILLEGAL_MOVE,
	CHESS_CORRECTLY_MOVE
} SP_CHESS_ERROR;

typedef enum
{
	CHESS_CHECK_WHITE,
	CHESS_CHECK_BLACK,
	CHESS_CHECKMATE_WHITE,
	CHESS_CHECKMATE_BLACK,
	CHESS_NOCHECK,
	CHESS_NOCHECKMATE
} SP_CHESS_CHECK;

typedef struct {
		int row;
		int col;
}SPChessPos;

typedef struct{
	char piece_o;
	char piece_d;
	int row_o;
	int col_o;
	int row_d;
	int col_d;
}tMove;

typedef struct{
	int n;
	tMove data[3];
}tMoves;

tMoves playerHistory;

tMoves IAHistory;

typedef struct{
	char board[SP_N_ROWS][SP_N_COLUMNS];
	char highlightboard[SP_N_ROWS][SP_N_COLUMNS];
	SP_COLOR currentPlayer;
	int row_o;
	int col_o;
	int row_d;
	int col_d;
	char piece_o;
	char piece_d;
	char gameMode;
	char diff;
	char slot[200];
	SP_CHESS_ERROR error;
	boolean change;
	SP_CHESS_CHECK check;
	SP_CHESS_CHECK checkMate;
	SPChessPos posWhiteKing;
	SPChessPos posBlackKing;
	char mode;
} SPChess;

SPChess* spChessCreate();
void spChessDefaultSettins(SPChess* src);
void spChessPrintSettins(SPChess* src);
void spChessRestart(SPChess* res);
void spChessResetHighLightBoard(SPChess* src);
void spChessDestroy(SPChess* src);
void spChessSetPosOrigin(SPChess* src, int row, int col);
void spChessSetPosDestiny(SPChess* src, int row, int col);
void spChessSetMove(SPChess* src);
void spChessSetMoveIA(SPChess* src);
bool spChessIsGameOver(SPChess* src);
char spChessCheckWinner(SPChess* src);
char spChessGetPiece(SPChess* src, int row, int col);
SP_CHESS_ERROR spChessCheckMove(SPChess* src);
void spChessSetCurrentPlayer(SPChess* src, SP_COLOR currentPlayer);
void spChessSetDiff(SPChess* src, char diff);
void spChessSetGameMode(SPChess* src, char gameMode);
void spChessUndo(SPChess* src);
boolean isEmptyHistory ();
void spChessLoad(SPChess* src);
void spChessSave(SPChess* src);
void spChessSetSlot(SPChess* src, char* slot);
SP_CHESS_ERROR spChessError(SPChess* src);
boolean spChessChange(SPChess* src);
#endif
