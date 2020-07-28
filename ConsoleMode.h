#ifndef CONSOLEMODE_H_
#define CONSOLEMODE_H_

#include "SPChess.h"

#define MAX_MATCHES 1 //The maximum number of matches allowed in a single string
#define GAME_MODE_X		"^game_mode [0-9]+$"
#define GAME_MODE_12	"^game_mode (1|2)$"
#define DIFFICULTY_X	"^difficulty [0-9]+$"
#define DIFFICULTY_1_5	"^difficulty [1-5]$"
#define USER_COLOR_X	"^user_color (0|1)$"
#define LOAD_X			"^load .+$"
#define DEFAULT			"^default$"
#define PRINT_SETTING	"^print_setting$"
#define QUIT			"^quit$"
#define START			"^start$"

#define MOVE 			"^move <[1-8],[A-H]> to <[1-8],[A-H]>$"
#define GET_MOVES		"^get_moves <[1-8],[A-H]>$"
#define SAVE_X			"^save .+$"
#define UNDO			"^undo$"
#define RESET			"^reset$"
#define PATH_X			"[a-z]+(\x2E)[a-z]+"

#define LEVEL_1			'1'
#define LEVEL_2			'2'
#define LEVEL_3			'3'
#define LEVEL_4			'4'
#define LEVEL_5			'5'

typedef enum {BLACK, WHITE} userColor;


typedef struct
{
	char x;
	char y;
	char * piece;
} tLocation;                             

typedef struct
{
	tLocation o;	// The current position of the piece <x,y>
	tLocation d;	// The destination position of the piece <i,j>
} tMoving;

boolean wrongGame, wrongDifficulty;

int consoleModeMain();

#endif
