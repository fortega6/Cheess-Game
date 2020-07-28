#include <stdio.h>
#include <termios.h>    //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO
#include <sys/types.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "ConsoleMode.h"

void clearScreen_C(){
	
    printf("\x1B[2J");
    
}

void gotoxyP2_C(int rowCurScreen, int colCurScreen){
	
   printf("\x1B[%d;%dH",rowCurScreen,colCurScreen);
   
}

void printchP2_C(char c){
	
   printf("%c",c);
   
}

int getRowCol(char c) {
	if(c == 'A' || c == '8')
		return 0;
	else if(c == 'B' || c == '7')
		return 1;
	else if(c == 'C' || c == '6')
		return 2;
	else if(c == 'D' || c == '5')
		return 3;
	else if(c == 'E' || c == '4')
		return 4;
	else if(c == 'F' || c == '3')
		return 5;
	else if(c == 'G' || c == '2')
		return 6;
	else
		return 7;
}

char getchP2_C(){

   int c;   

   static struct termios oldt, newt;

   /*tcgetattr get the parameters of the terminal*/
   tcgetattr( STDIN_FILENO, &oldt);
   /*the parameters are copied*/
   newt = oldt;

   newt.c_lflag &= ~(ICANON | ECHO);          

   tcsetattr( STDIN_FILENO, TCSANOW, &newt);

   /*Read a character*/
   c=getchar();                 
    
   /*restore original parameters*/
   tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

   /*Return the read character*/
   return (char)c;
   
}


void printBoardP2_C(SPChess* game){

   clearScreen_C();
   gotoxyP2_C(1,1);
   printf("8| _ _ _ _ _ _ _ _ |\n");	//01
   printf("                    \n");
   printf("7| _ _ _ _ _ _ _ _ |\n");	//02
   printf("                    \n");
   printf("6| _ _ _ _ _ _ _ _ |\n");	//03
   printf("                    \n");
   printf("5| _ _ _ _ _ _ _ _ |\n");	//04
   printf("                    \n");
   printf("4| _ _ _ _ _ _ _ _ |\n");	//05
   printf("                    \n");
   printf("3| _ _ _ _ _ _ _ _ |\n");	//06
   printf("                    \n");
   printf("2| _ _ _ _ _ _ _ _ |\n");	//07
   printf("                    \n");
   printf("1| _ _ _ _ _ _ _ _ |\n");	//08
   printf("                    \n");
   printf("  -----------------\n");
   printf("                    \n");
   printf("   A B C D E F G H\n");
   printf("                    \n");
   if(game->currentPlayer == SP_WHITE)
	printf("White player - enter your move:\n");
   else
	printf("Black player - enter your move:\n");
   gotoxyP2_C(22,1);
}

 int readCommand(char * command, char * REGEX) {
	
	int rv;
	regex_t exp; //Our compiled expression
	//1. Compile our expression.
	//Our regex is "-?[0-9]+(\\.[0-9]+)?". I will explain this later.
	//REG_EXTENDED is so that we can use Extended regular expressions
	rv = regcomp(&exp, REGEX, REG_EXTENDED);
	if (rv != 0) {
		printf("regcomp failed with %d\n", rv);
	}
	
	regmatch_t matches[MAX_MATCHES]; //A list of the matches in the string (a list of 1)
	//Compare the string to the expression
	//regexec() returns 0 on match, otherwise REG_NOMATCH
	return regexec(&exp, command, MAX_MATCHES, matches, 0) == 0;
	
}

void match(regex_t *pexp, char *sz, tMoving *mov) {
	int i, offset;
	regmatch_t matches[MAX_MATCHES]; //A list of the matches in the string (a list of 1)
	//Compare the string to the expression
	//regexec() returns 0 on match, otherwise REG_NOMATCH
	for(i = 0; i < 2; i++){
		
		
	}
	if (regexec(pexp, sz, MAX_MATCHES, matches, 0) == 0) {
		mov->o.x = sz[matches[0].rm_so+1];
		mov->o.y = sz[matches[0].rm_so+3];
		
		offset = matches[0].rm_eo;
		sz += offset;
	} else {
		printf("\"%s\" does not match\n", sz);
	}
	
	if (regexec(pexp, sz, MAX_MATCHES, matches, 0) == 0) {
		mov->d.x = sz[matches[0].rm_so+1];
		mov->d.y = sz[matches[0].rm_so+3];
	} else {
		printf("\"%s\" does not match\n", sz);
	}
}

void updateBoardP2_C(SPChess* game){

   int rowScreen, colScreen;
   int i,j;
   
   rowScreen = 1;
   for (i=0;i<DIM_MATRIX;i++){
	  colScreen = 4;
      for (j=0;j<DIM_MATRIX;j++){
         gotoxyP2_C(rowScreen,colScreen);
         printchP2_C(game->board[i][j]);
         colScreen = colScreen + 2;
      }
      rowScreen = rowScreen + 2;
   }
   
}


char readSetting(char * command){
	

	if(readCommand(command, GAME_MODE_X)){
		if(readCommand(command, GAME_MODE_12)){
			wrongGame = FALSE;
		}else{
			wrongGame = TRUE;
		}
		return '1';
	}
	
	if(readCommand(command, DIFFICULTY_X)){
		if(readCommand(command, DIFFICULTY_1_5)){
			wrongDifficulty = FALSE;
		}else{
			wrongDifficulty = TRUE;
		}
		return '2';
	}
	
	if(readCommand(command, USER_COLOR_X)){
		return '3';
	}
	
	if(readCommand(command, LOAD_X)){
		return '4';
	}
	
	if(readCommand(command, DEFAULT)){
		return '5';
	}
	
	if(readCommand(command, PRINT_SETTING)){
		return '6';
	}
	
	if(readCommand(command, QUIT)){
		return '7';
	}
	
	if(readCommand(command, START)){
		return '8';
	}
	
	return '0';
}

char readCommandGame(char * command){
	
	if(readCommand(command, MOVE)){
		return '1';
	}
	
	if(readCommand(command, GET_MOVES)){
		return '2';
	}
	
	if(readCommand(command, SAVE_X)){
		return '3';
	}
	
	if(readCommand(command, UNDO)){
		return '4';
	}
	
	if(readCommand(command, RESET)){
		return '5';
	}
	
	if(readCommand(command, QUIT)){
		return '6';
	}
	
	return '0';
}


void save(SPChess* game, char * command){
		
	///
	/// EX.4.3: Save the trips list information into OPS_TRIPS_FILE file.
	///
	
	if(readCommand(command+5, "(/.)+")){
		sprintf(game->slot,"%s", command+5);
	}else{
		sprintf(game->slot,"./%s", command+5);
	}
	
	spChessSave(game);
}

void load(SPChess* game, char * command){
	
	if(readCommand(command+5, "(/.)+")){
		sprintf(game->slot,"%s", command+5);
	}else{
		sprintf(game->slot,"./%s", command+5);
	}
	
	spChessLoad(game);
}

int start(SPChess* game){
/**
 * definition of local variables.
 */
	
	tMoving mov;
	
	//char aux_path[100];
	char * command = malloc(100 * sizeof(char));
	boolean OK = TRUE;

	int rv, rv1;
	  

	int op = 1;
	
	regex_t exp, exp1; //Our compiled expression
	//1. Compile our expression.
	//Our regex is "-?[0-9]+(\\.[0-9]+)?". I will explain this later.
	//REG_EXTENDED is so that we can use Extended regular expressions
	
	rv = regcomp(&exp, "<[1-8],[A-H]>", REG_EXTENDED);
	if (rv != 0) {
		printf("regcomp failed with %d\n", rv);
	}
	
	rv1 = regcomp(&exp1, PATH_X, REG_EXTENDED);
	if (rv1 != 0) {
		printf("regcomp failed with %d\n", rv);
	}
		 
	while (op != '6' && game->checkMate != CHESS_CHECKMATE_WHITE && game->checkMate != CHESS_CHECKMATE_BLACK) {  //bucle principal.  
		
	
		printBoardP2_C(game);
		updateBoardP2_C(game);
		gotoxyP2_C(22,1);
			
		scanf("%[^\n]", command);
		getchar();                   //to destroy the last charecter '\n'
		
		op = readCommandGame(command);
		switch (op)
		{
			case '1': // Move
				match(&exp, command, &mov);
				
				game->row_o = getRowCol(mov.o.x);
				game->col_o = getRowCol(mov.o.y);
	
				game->piece_o = game->board[game->row_o][game->col_o];
	
				game->row_d = getRowCol(mov.d.x);
				game->col_d = getRowCol(mov.d.y);
				game->piece_d = game->board[game->row_d][game->col_d];
				
				if(game->gameMode == '1'){
					clearScreen_C();
					gotoxyP2_C(1,1);
				}
				
				spChessSetMove(game);
				
				if(game->check == CHESS_CHECK_WHITE){
					printf("Check: White King is threatened!\n");
				}else if(game->check == CHESS_CHECK_BLACK){
					printf("Check: Black King is threatened!\n");
				}else if(game->checkMate == CHESS_CHECKMATE_WHITE){
					printf("Checkmate! Black player wins the game\n");
				}else if(game->checkMate == CHESS_CHECKMATE_BLACK){
					printf("Checkmate! White player wins the game\n");
				}
				
				printf("Press enter to continue...");
				getchar();

				break; 
			case '2': // Get moves
				
				break;
			case '3': // Save
				save(game, command);
				printf("Press enter to continue...");
				getchar();
				break;
			case '4': // Undo
				if(game->gameMode == '1')
					spChessUndo(game);
				else
					printf("Undo command not available in 2 players mode\n");
				printf("Press enter to continue...");
				getchar();
				break;
			case '5': // Reset
				spChessRestart(game);
				printf("Restarting...\n");
				getchar();
				break;
			case '6': // quit
				printf("Exiting...\n");
				break;
			default:
				printf("Illegal command!!\n");
				printf("Press enter to continue...");
				getchar();
				
		}
		
		
	}
     free(command);
   return 1;
}

int consoleModeMain() {
	
	int rv;
	int op = 1;
	SPChess* game;
	char * command = malloc(100 * sizeof(char));
	 
	regex_t exp; //Our compiled expression
	//1. Compile our expression.
	//Our regex is "-?[0-9]+(\\.[0-9]+)?". I will explain this later.
	//REG_EXTENDED is so that we can use Extended regular expressions
	
	rv = regcomp(&exp, PATH_X, REG_EXTENDED);
	if (rv != 0) {
		printf("regcomp failed with %d\n", rv);
	}

	game  = spChessCreate();
	game->mode = 'c';
	while( op != '7'){
		clearScreen_C();
		gotoxyP2_C(1,1);
		printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
		scanf("%[^\n]", command);
		getchar();                   //to destroy the last charecter '\n'
		
		op = readSetting(command);
		
		switch (op)
		{
			case '1': // Game mode
				if(!wrongGame){
					if(command[10] == '1'){
						printf("Game mode is set to 1 player\n");
						game->gameMode = '1';
						spChessDefaultSettins(game);
					}else{
						printf("Game mode is set to 2 player\n");
						game->gameMode = '2';
					}
				}else{
					printf("Wrong game mode\n");
				}
				break; 
			case '2': // difficulty
				if(game->gameMode == '1')
					if(!wrongDifficulty)
						//if(command[11] != '5')
							game->diff = command[11];
						//else
							//printf("Expert level not supported, please choose a value between 1 to 4:\n");
					else
						printf("Wrong difficulty level. The value should be between 1 to 5\n\n");
				else 
					printf("This command is only legal when the game is set to 1 player mode\n");
				break;
			case '3': // user color
				if(game->gameMode == '1'){
					game->currentPlayer = (int) (command[11] - 48);
				}else{ 
					printf("Illegal command!!\n");
				}
				break;
			case '4': // load
				load(game, command);
				break;
			case '5': // default
				spChessDefaultSettins(game);
				break;
			case '6': // print setting
				
				spChessPrintSettins(game);
				break;
			case '7': // quit
				printf("Exiting...\n");
				break;
			case '8': // start
				start(game);
				spChessRestart(game);
				break;
				
		}
		printf("\nPress enter to continue...");

		getchar();
	}
	free(command);
	return 0;
}
