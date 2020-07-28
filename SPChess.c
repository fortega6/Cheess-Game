#include "SPChess.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

char getRow(int r) {
	if(r == 0)
		return '8';	 
	else if(r == 1)
		return '7';
	else if(r == 2)
		return '6';
	else if(r == 3)
		return '5';
	else if(r == 4)
		return '4';
	else if(r == 5)
		return '3';
	else if(r == 6)
		return '2';
	else
		return '1';
}

char getCol(int c) {
	if(c == 0)
		return 'A';	 
	else if(c == 1)
		return 'B';
	else if(c == 2)
		return 'C';
	else if(c == 3)
		return 'D';
	else if(c == 4)
		return 'E';
	else if(c == 5)
		return 'F';
	else if(c == 6)
		return 'G';
	else
		return 'H';
}

boolean isColor(SP_COLOR color, char piece){
	boolean val = FALSE;

	if(color == SP_WHITE){
		if(piece >= 97 && piece <= 122){
			val = TRUE;
		}
	}else if(piece >= 65 && piece <= 90){
		val = TRUE;
	}
	return val;
}

SP_COLOR nextPlayer(SP_COLOR currentPlayer) {
	if (currentPlayer == SP_WHITE) {
		return SP_BLACK;
	}
	return SP_WHITE;
}

boolean isEmptyHistory (){
	return playerHistory.n == 0;
}

int f(SPChess* src) {
	int i, j, score_white, score_black;
	
	score_white = score_black = 0;
	for(i = 0; i < DIM_MATRIX; i++){
		for(j = 0; j < DIM_MATRIX; j++){
			if(src->board[i][j] != '_'){
				if(isColor(SP_WHITE, src->board[i][j])){
					if(src->board[i][j] == 'p'){
						score_white += SCORE_PAWN;
					}else if(src->board[i][j] == 'n'){
						score_white += SCORE_KNIGHT;
					}else if(src->board[i][j] == 'b'){
						score_white += SCORE_BISHOP;
					}else if(src->board[i][j] == 'r'){
						score_white += SCORE_ROOK;
					}else if(src->board[i][j] == 'q'){
						score_white += SCORE_QUEEN;
					}else if(src->board[i][j] == 'k'){
						score_white += SCORE_KING;
					}
				}else{
					if(src->board[i][j] == 'P'){
						score_black += SCORE_PAWN;
					}else if(src->board[i][j] == 'N'){
						score_black += SCORE_KNIGHT;
					}else if(src->board[i][j] == 'B'){
						score_black += SCORE_BISHOP;
					}else if(src->board[i][j] == 'R'){
						score_black += SCORE_ROOK;
					}else if(src->board[i][j] == 'Q'){
						score_black += SCORE_QUEEN;
					}else if(src->board[i][j] == 'K'){
						score_black += SCORE_KING;
					}
				}
			}
		}
	}

	if(src->currentPlayer == SP_WHITE){
		//~ printf(" MiniMax: %d\n", score_white - score_black);
		//~ printf("===================\n");
		return score_white - score_black;
	}else{
		//~ printf(" MiniMax: %d\n", score_black - score_white);
		//~ printf("===================\n");
		return score_black - score_white;
	}
}
void print(SPChess* src){
	int i, j;
	
	for (i = 0; i < DIM_MATRIX; i++)
	{
		for (j = 0; j < DIM_MATRIX; j++)
		{
			printf("%c ", src->board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*
 * Find destiny position on the board 
 * */
boolean findPosition(SPChess* src){
	int i, max = 8;
	boolean finded = FALSE;
	boolean locked_1, locked_2, locked_3, locked_4, locked_5, locked_6, locked_7, locked_8;
	
	locked_1 = locked_2 = locked_3 = locked_4 = locked_5 = locked_6 = locked_7 = locked_8 = FALSE;
	
	i = 1;
		
	if( (src->piece_o == 'P' || src->piece_o == 'p') && (src->row_o == 1 || src->row_o == 6) ){
		max = 2;
		if(src->piece_d == '_'){
			locked_3 = locked_4 = locked_5 = locked_6 = locked_7 = locked_8 = TRUE;
		}
	}else if(src->piece_o == 'P' || src->piece_o == 'p'){
		max = 1;
		if(src->piece_d == '_'){
			locked_3 = locked_4 = locked_5 = locked_6 = locked_7 = locked_8 = TRUE;
		}
	}
	
	if(src->piece_o == 'K' || src->piece_o == 'k'){
		max = 1;
	}
	
	if(src->piece_o != 'N' && src->piece_o != 'n'){
		while(i <= max && !finded){
			
			/* Vertically */
			
			if( !locked_1 ){
				if(src->piece_o == 'R' || src->piece_o == 'r' 
									   || src->piece_o == 'Q' 
									   || src->piece_o == 'q' 
									   || src->piece_o == 'K' 
									   || src->piece_o == 'k'){
					if( src->row_o+i == src->row_d && src->col_o == src->col_d ){
						finded = TRUE;
					}else if( src->board[src->row_o+i][src->col_o] != '_' ){
						locked_1 = TRUE;
					}
				}
				
				if(src->piece_o == 'P'){
					if( src->row_o+i == src->row_d && src->col_o == src->col_d && src->board[src->row_o+1][src->col_o] == '_' ){
						finded = TRUE;
					}else if( src->board[src->row_o+i][src->col_o] != '_' ){
						locked_1 = TRUE;
					}
				}
			}
			
			if( !locked_2 ){	
				if(src->piece_o == 'R' || src->piece_o == 'r' 
									 || src->piece_o == 'Q' 
									 || src->piece_o == 'q' 
									 || src->piece_o == 'K' 
									 || src->piece_o == 'k'){
					if( src->row_o-i == src->row_d && src->col_o == src->col_d ){
						 finded = TRUE;
					}else if( src->board[src->row_o-i][src->col_o] != '_' ){
						locked_2 = TRUE;
					}
				}
				
				if(src->piece_o == 'p'){
					if( src->row_o-i == src->row_d && src->col_o == src->col_d && src->board[src->row_o-i][src->col_o] == '_'){
						 finded = TRUE;
					}else if( src->board[src->row_o-i][src->col_o] != '_' ){
						locked_2 = TRUE;
					}
				}
			}
				
			/* Horizontally */
			
			if( !locked_3 ){	
				if(src->piece_o == 'R' || src->piece_o == 'r' 
									   || src->piece_o == 'Q' 
									   || src->piece_o == 'q' 
									   || src->piece_o == 'K' 
									   || src->piece_o == 'k'){
					if( src->row_o == src->row_d && src->col_o+i == src->col_d ){
						finded = TRUE;
					}else if( src->board[src->row_o][src->col_o+i] != '_' ){
						locked_3 = TRUE;
					}
				}
			}
			
			if( !locked_4 ){
				if(src->piece_o == 'R' || src->piece_o == 'r' 
									   || src->piece_o == 'Q' 
									   || src->piece_o == 'q' 
									   || src->piece_o == 'K' 
									   || src->piece_o == 'k'){
					if( src->row_o == src->row_d && src->col_o-i == src->col_d ){
						finded = TRUE;
					}else if( src->board[src->row_o][src->col_o-i] != '_' ){
						locked_4 = TRUE;
					}
				}
			}
				
			/* Diagonally */
			
			if( !locked_5 ){
				if(src->piece_o == 'B' || src->piece_o == 'b' 
				                       || src->piece_o == 'Q' 
				                       || src->piece_o == 'q' 
				                       || src->piece_o == 'K' 
				                       || src->piece_o == 'k'){
					if( src->row_o+i == src->row_d && src->col_o+i == src->col_d ){
						finded = TRUE;
					}else if( src->board[src->row_o+i][src->col_o+i] != '_' ){
						locked_5 = TRUE;
					}
				}
				
				if(src->piece_o == 'P'){
					locked_5 = TRUE;
					if( src->row_o+i == src->row_d && src->col_o+i == src->col_d ){
						finded = TRUE;
					}
				}
			}
			
			if( !locked_6 ){
				if(src->piece_o == 'B' || src->piece_o == 'b' 
									   || src->piece_o == 'Q' 
									   || src->piece_o == 'q' 
									   || src->piece_o == 'K' 
									   || src->piece_o == 'k'){
					if( src->row_o-i == src->row_d && src->col_o+i == src->col_d ){
						finded = TRUE;
					}else if( src->board[src->row_o-i][src->col_o+i] != '_' ){
						locked_6 = TRUE;
					}
				}
				
				if(src->piece_o == 'p'){
					locked_6 = TRUE;
					if( src->row_o-i == src->row_d && src->col_o+i == src->col_d ){
						finded = TRUE;
					}
				}
			}
				
			if( !locked_7 ){
				if(src->piece_o == 'B' || src->piece_o == 'b' || src->piece_o == 'Q' || src->piece_o == 'q' || src->piece_o == 'K' || src->piece_o == 'k'){
					if( src->row_o+i == src->row_d && src->col_o-i == src->col_d ){
						finded = TRUE;
					}else if( src->board[src->row_o+i][src->col_o-i] != '_' ){
						locked_7 = TRUE;
					}
				}
				
				if(src->piece_o == 'P'){
					locked_7 = TRUE;
					if( src->row_o+i == src->row_d && src->col_o-i == src->col_d ){
						finded = TRUE;
					}
				}
			}
			
			if( !locked_8 ){
				if(src->piece_o == 'B' || src->piece_o == 'b' 
									   || src->piece_o == 'Q' 
									   || src->piece_o == 'q' 
									   || src->piece_o == 'K' 
									   || src->piece_o == 'k'){
					if( src->row_o-i == src->row_d && src->col_o-i == src->col_d ){
						finded = TRUE;
					}else if( src->board[src->row_o-i][src->col_o-i] != '_' ){
						locked_8 = TRUE;
					}
				}
				
				if(src->piece_o == 'p'){
					locked_8 = TRUE;
					if( src->row_o-i == src->row_d && src->col_o-i == src->col_d ){
						finded = TRUE;
					}
				}
			}
			i++;
		}
	}
	if(src->piece_o == 'N' || src->piece_o == 'n'){
		if( src->row_o-2 == src->row_d && src->col_o+1 == src->col_d ){
			finded = TRUE;
		}else if( src->row_o-1 == src->row_d && src->col_o+2 == src->col_d ){
			finded = TRUE;
		}else if( src->row_o+1 == src->row_d && src->col_o+2 == src->col_d ){
			finded = TRUE;
		}else if( src->row_o+1 == src->row_d && src->col_o+2 == src->col_d ){
			finded = TRUE;
		}else if( src->row_o+2 == src->row_d && src->col_o+1 == src->col_d ){
			finded = TRUE;
		}else if( src->row_o+2 == src->row_d && src->col_o-1 == src->col_d ){
			finded = TRUE;
		}else if( src->row_o+1 == src->row_d && src->col_o-2 == src->col_d ){
			finded = TRUE;
		}else if( src->row_o-1 == src->row_d && src->col_o-2 == src->col_d ){
			finded = TRUE;
		}else if( src->row_o-2 == src->row_d && src->col_o-1 == src->col_d ){
			finded = TRUE;
		}
	}
	
	return finded;
}


/*
 * Find moves for artificial intelligence (the minimax algorithm)
 * */
int findPositionIA(SPChess* src, SP_COLOR currentPlayer, int depth, int alpha, int beta) {
	int row_o, col_o, row_d, col_d;
	int row, col, k, max, miniMax;
	char piece, aux_piece;
	boolean locked_1, locked_2, locked_3, locked_4, locked_5, locked_6, locked_7, locked_8;
	
	if(depth == 0){
		return f(src);
	}else {
		for(row = 0; row < SP_N_ROWS; row++){
			for(col = 0; col < SP_N_COLUMNS; col++){
				piece = src->board[row][col];
				src->board[row][col] = '_';
				max = 7;
				locked_1 = locked_2 = locked_3 = locked_4 = locked_5 = locked_6 = locked_7 = locked_8 = FALSE;

				if(piece == 'K' || piece == 'k'){
					max = 1;
				}
				
				if( (piece == 'P' || piece == 'p') && (row == 1 || row == 6) ){
					max = 2;
				}else if(piece == 'P' || piece == 'p'){
					max = 1;
				}
				
				k=1;
				if(isColor(currentPlayer, piece)){
					if(piece != 'N' && piece != 'n' && piece != '_'){
						while(k <= max){
							
							/* Vertically */
							if( !locked_1 && row+k < DIM_MATRIX){
								if(piece == 'R' || piece == 'r' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'K'){
									if( !isColor(currentPlayer, src->board[row+k][col]) ){
										aux_piece = src->board[row+k][col];
										src->board[row+k][col] = piece;
										//~ print(src);
										miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
										src->board[row+k][col] = aux_piece;
										if(currentPlayer == src->currentPlayer){
											if(miniMax > alpha){
												row_o = row; col_o = col; row_d = row+k; col_d = col; 
												alpha = miniMax;
											}
										}else if(miniMax < beta){
											row_o = row; col_o = col; row_d = row+k; col_d = col;
											beta = miniMax;		
										}
										if(aux_piece != '_'){
											locked_1 = TRUE;
										}
									}else{
										locked_1 = TRUE;
									}
								}
								
								if(piece == 'P'){
									if(src->board[row+k][col] == '_'){
										aux_piece = src->board[row+k][col];
										src->board[row+k][col] = piece;
										miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
										src->board[row+k][col] = aux_piece;
										
										if(currentPlayer == src->currentPlayer){
											if(miniMax > alpha){
												row_o = row; col_o = col; row_d = row+k; col_d = col; 
												alpha = miniMax;
											}
										}else if(miniMax < beta){
											row_o = row; col_o = col; row_d = row+k; col_d = col;
											beta = miniMax;		
										}
										if(aux_piece != '_'){
											locked_1 = TRUE;
										}
									}else{
										locked_1 = TRUE;
									}
								}
							}
							
							if( !locked_2 &&  row-k >= 0){	
								if(piece == 'R' || piece == 'r' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'K'){
									if( !isColor(currentPlayer, src->board[row-k][col]) ){
										aux_piece = src->board[row-k][col];
										src->board[row-k][col] = piece;
										//~ print(src);
										miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
										src->board[row-k][col] = aux_piece;
										if(currentPlayer == src->currentPlayer){
											if(miniMax > alpha){
												row_o = row; col_o = col; row_d = row-k; col_d = col;
												alpha = miniMax;
											}
										}else if(miniMax < beta){
											row_o = row; col_o = col; row_d = row-k; col_d = col;
											beta = miniMax;	
										}
										
										if(aux_piece != '_'){
											locked_2 = TRUE;
										}
									}else{
										locked_2 = TRUE;
									}
								}
								
								if(piece == 'p'){
									if( src->board[row-k][col] == '_' ){
										aux_piece = src->board[row-k][col];
										src->board[row-k][col] = piece;
										//~ print(src);
										miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
										src->board[row-k][col] = aux_piece;
										
										if(currentPlayer == src->currentPlayer){
											if(miniMax > alpha){
												row_o = row; col_o = col; row_d = row-k; col_d = col;
												alpha = miniMax;
											}
										}else if(miniMax < beta){
											row_o = row; col_o = col; row_d = row-k; col_d = col;
											beta = miniMax;		
										}
										
										if(aux_piece != '_'){
											locked_2 = TRUE;
										}
									}else{
										locked_2 = TRUE;
									}
								}
							}
								
							/* Horizontally */
							
							if( !locked_3 && col+k < DIM_MATRIX){	
								if(piece == 'R' || piece == 'r' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'K'){
									if( !isColor(currentPlayer, src->board[row][col+k]) ){
										aux_piece = src->board[row][col+k];
										src->board[row][col+k] = piece;
										//~ print(src);
										miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
										src->board[row][col+k] = aux_piece;
										
										if(currentPlayer == src->currentPlayer){
											if(miniMax > alpha){
												row_o = row; col_o = col; row_d = row; col_d = col+k;
												alpha = miniMax;
											}
										}else if(miniMax < beta){
											row_o = row; col_o = col; row_d = row; col_d = col+k;
											beta = miniMax;		
										}
										
										if(aux_piece != '_'){
											locked_3 = TRUE;
										}
									}else{
										locked_3 = TRUE;
									}
								}
							}
							
							if( !locked_4 && col-k >= 0){
								if(piece == 'R' || piece == 'r' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'K'){
									if( !isColor(currentPlayer, src->board[row][col-k]) ){
										aux_piece = src->board[row][col-k];
										src->board[row][col-k] = piece;
										//~ print(src);
										miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
										src->board[row][col-k] = aux_piece;
										
										if(currentPlayer == src->currentPlayer){
											if(miniMax > alpha){
												row_o = row; col_o = col; row_d = row; col_d = col-k;
												alpha = miniMax;
											}
										}else if(miniMax < beta){
											row_o = row; col_o = col; row_d = row; col_d = col-k;
											beta = miniMax;		
										}
										
										if(aux_piece != '_'){
											locked_4 = TRUE;
										}
									}else{
										locked_4 = TRUE;
									}
								}
							}
								
							/* Diagonally */
							
							if( !locked_5 && row+k < DIM_MATRIX && col+k < DIM_MATRIX ){
								if(piece == 'B' || piece == 'b' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'K'){
									if( !isColor(currentPlayer, src->board[row+k][col+k]) ){
										aux_piece = src->board[row+k][col+k];
										src->board[row+k][col+k] = piece;
										//~ print(src);
										miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
										src->board[row+k][col+k] = aux_piece;
											
										if(currentPlayer == src->currentPlayer){
											if(miniMax > alpha){
												row_o = row; col_o = col; row_d = row+k; col_d = col+k;
												alpha = miniMax;
											}
										}else if(miniMax < beta){
											row_o = row; col_o = col; row_d = row+k; col_d = col+k;
											beta = miniMax;		
										}
										if(aux_piece != '_'){
											locked_5 = TRUE;
										}
									}else{
										locked_5 = TRUE;
									}
								}
								
								if(piece == 'P'){
									locked_5 = TRUE;
									if( !isColor(currentPlayer, src->board[row+k][col+k]) && src->board[row+k][col+k] != '_'){
										aux_piece = src->board[row+k][col+k];
										src->board[row+k][col+k] = piece;
										//~ print(src);
										miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
										src->board[row+k][col+k] = aux_piece;
										
										if(currentPlayer == src->currentPlayer){
											if(miniMax > alpha){
												row_o = row; col_o = col; row_d = row+k; col_d = col+k;
												alpha = miniMax;
											}
										}else if(miniMax < beta){
											row_o = row; col_o = col; row_d = row+k; col_d = col+k;
											beta = miniMax;		
										}
									}
								}
							}
							
							if( !locked_6 && row-k >= 0 && col+k < DIM_MATRIX){
								if(piece == 'B' || piece == 'b' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'K'){
									if( !isColor(currentPlayer, src->board[row-k][col+k]) ){
										aux_piece = src->board[row-k][col+k];
										src->board[row-k][col+k] = piece;
										//~ print(src);
										miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
										src->board[row-k][col+k] = aux_piece;
										
										if(currentPlayer == src->currentPlayer){
											if(miniMax > alpha){
												row_o = row; col_o = col; row_d = row-k; col_d = col+k;
												alpha = miniMax;
											}
										}else if(miniMax < beta){
											row_o = row; col_o = col; row_d = row-k; col_d = col+k;
											beta = miniMax;		
										}
										
										if(aux_piece != '_'){
											locked_6 = TRUE;
										}
									}else{
										locked_6 = TRUE;
									}
								}
								
								if(piece == 'p'){
									locked_6 = TRUE;
									if( !isColor(currentPlayer, src->board[row-k][col+k]) && src->board[row-k][col+k] != '_'){
										aux_piece = src->board[row-k][col+k];
										src->board[row-k][col+k] = piece;
										//~ print(src);
										miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
										src->board[row-k][col+k] = aux_piece;
										
										if(currentPlayer == src->currentPlayer){
											if(miniMax > alpha){
												row_o = row; col_o = col; row_d = row-k; col_d = col+k;
												alpha = miniMax;
											}
										}else if(miniMax < beta){
											row_o = row; col_o = col; row_d = row-k; col_d = col+k;
											beta = miniMax;		
										}
									}
								}
							}
								
							if( !locked_7 && row+k < DIM_MATRIX && col-k >= 0 ){
								if(piece == 'B' || piece == 'b' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'K'){
									if( !isColor(currentPlayer, src->board[row+k][col-k]) ){
										aux_piece = src->board[row+k][col-k];
										src->board[row+k][col-k] = piece;
										//~ print(src);
										miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
										src->board[row+k][col-k] = aux_piece;
										
										if(currentPlayer == src->currentPlayer){
											if(miniMax > alpha){
												row_o = row; col_o = col; row_d = row+k; col_d = col-k;
												alpha = miniMax;
											}
										}else if(miniMax < beta){
											row_o = row; col_o = col; row_d = row+k; col_d = col-k;
											beta = miniMax;		
										}
										
										if(aux_piece != '_'){
											locked_7 = TRUE;
										}
									}else{
										locked_7 = TRUE;
									}
								}
								
								if(piece == 'P'){
									locked_7 = TRUE;
									if( !isColor(currentPlayer, src->board[row+k][col-k]) && src->board[row+k][col-k] != '_'){
										aux_piece = src->board[row+k][col-k];
										src->board[row+k][col-k] = piece;
										//~ print(src);
										miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
										src->board[row+k][col-k] = aux_piece;
										
										if(currentPlayer == src->currentPlayer){
											if(miniMax > alpha){
												row_o = row; col_o = col; row_d = row+k; col_d = col-k;
												alpha = miniMax;
											}
										}else if(miniMax < beta){
											row_o = row; col_o = col; row_d = row+k; col_d = col-k;
											beta = miniMax;		
										}
									}
								}
							}
							
							if( !locked_8 && row-k >= 0 && col-k >= 0){
								if(piece == 'B' || piece == 'b' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'K'){
									if( !isColor(currentPlayer, src->board[row-k][col-k]) ){
										aux_piece = src->board[row-k][col-k];
										src->board[row-k][col-k] = piece;
										//~ print(src);
										miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
										src->board[row-k][col-k] = aux_piece;
										
										if(currentPlayer == src->currentPlayer){
											if(miniMax > alpha){
												row_o = row; col_o = col; row_d = row-k; col_d = col-k;
												alpha = miniMax;
											}
										}else if(miniMax < beta){
											row_o = row; col_o = col; row_d = row-k; col_d = col-k;
											beta = miniMax;		
										}
										
										if(aux_piece != '_'){
											locked_8 = TRUE;
										}
									}else{
										locked_8 = TRUE;
									}
								}
								
								if(piece == 'p'){
									locked_8 = TRUE;
									if( !isColor(currentPlayer, src->board[row-k][col-k]) && src->board[row-k][col-k] != '_' ){
										aux_piece = src->board[row-k][col-k];
										src->board[row-k][col-k] = piece;
										//~ print(src);
										miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
										src->board[row-k][col-k] = aux_piece;
										
										if(currentPlayer == src->currentPlayer){
											if(miniMax > alpha){
												row_o = row; col_o = col; row_d = row-k; col_d = col-k;
												alpha = miniMax;
											}
										}else if(miniMax < beta){
											row_o = row; col_o = col; row_d = row-k; col_d = col-k;
											beta = miniMax;		
										}
									}
								}
							}
							k++;
						}
					}
					if((piece == 'N' || piece == 'n') && (piece != '_') ){
						if(row-2 >= 0 && col+1 < DIM_MATRIX){
							if( !isColor(currentPlayer, src->board[row-2][col+1]) ){
								aux_piece = src->board[row-2][col+1];
								src->board[row-2][col+1] = piece;
								//~ print(src);
								miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
								src->board[row-2][col+1] = aux_piece;
								if(currentPlayer == src->currentPlayer){
									if(miniMax > alpha){
										row_o = row; col_o = col; row_d = row-2; col_d = col+1;
										alpha = miniMax;
									}
								}else if(miniMax < beta){
									row_o = row; col_o = col; row_d = row-2; col_d = col+1;
									beta = miniMax;		
								}
							}
						}
						
						if(row-1 >= 0 && col+2 < DIM_MATRIX){
							if( !isColor(currentPlayer, src->board[row-1][col+2]) ){
								aux_piece = src->board[row-1][col+2];
								src->board[row-1][col+2] = piece;
								//~ print(src);
								miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
								src->board[row-1][col+2] = aux_piece;
								if(currentPlayer == src->currentPlayer){
									if(miniMax > alpha){
										row_o = row; col_o = col; row_d = row-1; col_d = col+2;
										alpha = miniMax;
									}
								}else if(miniMax < beta){
									row_o = row; col_o = col; row_d = row-1; col_d = col+2;
									beta = miniMax;		
								}
							}
						}
						
						if(row+1 < DIM_MATRIX && col+2 < DIM_MATRIX){
							if( !isColor(currentPlayer, src->board[row+1][col+2]) ){
								aux_piece = src->board[row+1][col+2];
								src->board[row+1][col+2] = piece;
								//~ print(src);
								miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
								src->board[row+1][col+2] = aux_piece;
								if(currentPlayer == src->currentPlayer){
									if(miniMax > alpha){
										row_o = row; col_o = col; row_d = row+1; col_d = col+2;
										alpha = miniMax;
									}
								}else if(miniMax < beta){
									row_o = row; col_o = col; row_d = row+1; col_d = col+2;
									beta = miniMax;		
								}
							}
						}
						
						if(row+2 < DIM_MATRIX && col+1 < DIM_MATRIX){
							if( !isColor(currentPlayer, src->board[row+2][col+1]) ){
								aux_piece = src->board[row+2][col+1];
								src->board[row+2][col+1] = piece; 
								//~ print(src);
								miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
								src->board[row+2][col+1] = aux_piece;
								if(currentPlayer == src->currentPlayer){
									if(miniMax > alpha){
										row_o = row; col_o = col; row_d = row+2; col_d = col+1;
										alpha = miniMax;
									}
								}else if(miniMax < beta){
									row_o = row; col_o = col; row_d = row+2; col_d = col+1;
									beta = miniMax;		
								}
							}
						}
						
						if(row+2 < DIM_MATRIX && col-1 >= 0){
							if( !isColor(currentPlayer, src->board[row+2][col-1]) ){
								aux_piece = src->board[row+2][col-1];
								src->board[row+2][col-1] = piece;
								//~ print(src);
								miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
								src->board[row+2][col-1] = aux_piece;
								if(currentPlayer == src->currentPlayer){
									if(miniMax > alpha){
										row_o = row; col_o = col; row_d = row+2; col_d = col-1;
										alpha = miniMax;
									}
								}else if(miniMax < beta){
									row_o = row; col_o = col; row_d = row+2; col_d = col-1;
									beta = miniMax;		
								}
							}
						}
						
						if(row+1 < DIM_MATRIX && col-2 >= 0){
							if( !isColor(currentPlayer, src->board[row+1][col-2]) ){
								aux_piece = src->board[row+1][col-2];
								src->board[row+1][col-2] = piece;
								//~ print(src);
								miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
								src->board[row+1][col-2] = aux_piece;
								if(currentPlayer == src->currentPlayer){
									if(miniMax > alpha){
										row_o = row; col_o = col; row_d = row+1; col_d = col-2;
										alpha = miniMax;
									}
								}else if(miniMax < beta){
									row_o = row; col_o = col; row_d = row+1; col_d = col-2;
									beta = miniMax;		
								}
							}
						}
							
						if(row-1 >= 0 && col-2 >= 0){
							if( !isColor(currentPlayer, src->board[row-1][col-2]) ){
								aux_piece = src->board[row-1][col-2];
								src->board[row-1][col-2] = piece;
								miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
								src->board[row-1][col-2] = aux_piece;
								if(currentPlayer == src->currentPlayer){
									if(miniMax > alpha){
										row_o = row; col_o = col; row_d = row-1; col_d = col-2;
										alpha = miniMax;
									}
								}else if(miniMax < beta){
									row_o = row; col_o = col; row_d = row-1; col_d = col-2;
									beta = miniMax;		
								}
							}
						}
						
						if(row-2 >= 0 && col-1 >= 0){
							if( !isColor(currentPlayer, src->board[row-2][col-1]) ){
								aux_piece = src->board[row-2][col-1];
								src->board[row-2][col-1] = piece;
								//~ print(src);
								miniMax = findPositionIA(src, nextPlayer(currentPlayer), depth-1, alpha, beta);
								src->board[row-2][col-1] = aux_piece;
								if(currentPlayer == src->currentPlayer){
									if(miniMax > alpha){
										row_o = row; col_o = col; row_d = row-2; col_d = col-1;
										alpha = miniMax;
									}
								}else if(miniMax < beta){
									row_o = row; col_o = col; row_d = row-2; col_d = col-1;
									beta = miniMax;		
								}
							}
						}
					}
				}
				src->board[row][col] = piece;
			}
		}
		src->row_o = row_o; src->col_o = col_o; src->row_d = row_d; src->col_d = col_d;
	}
	if(currentPlayer == src->currentPlayer)   // Max
		return alpha;
	else
		return beta;	// Mini
		
}

/*
 * This function find if the king is threatened
 * */
boolean findKing(char board[SP_N_ROWS][SP_N_COLUMNS], char piece, int row, int col, char king){
	int i, max = 7;
	boolean finded = FALSE;
	boolean locked_1, locked_2, locked_3, locked_4, locked_5, locked_6, locked_7, locked_8;
	i = 1;
	
	
	if(piece == 'P' || piece == 'p' || piece == 'K' || piece == 'k'){
		max = 1;
	}

	locked_1 = locked_2 = locked_3 = locked_4 = locked_5 = locked_6 = locked_7 = locked_8 = FALSE;
	if(piece != 'N' && piece != 'n'){
		while(i <= max && !finded){
			
			/* Vertically */
			
			if( !locked_1 && row+i < DIM_MATRIX){
				if(piece == 'R' || piece == 'r' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'k'){
					if( board[row+i][col] == king ){
						finded = TRUE;
					}else if( board[row+i][col] != '_' ){
						locked_1 = TRUE;
					}
				}
			}
			
			if( !locked_2 && row-i >= 0){	
				if(piece == 'R' || piece == 'r' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'k'){
					if( board[row-i][col] == king ){
						 finded = TRUE;
					}else if( board[row-i][col] != '_' ){
						locked_2 = TRUE;
					}
				}
			}
				
				/* Horizontally */
			
			if( !locked_3 && col+i < DIM_MATRIX ){	
				if(piece == 'R' || piece == 'r' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'k'){
					if( board[row][col+i] == king ){
						finded = TRUE;
					}else if( board[row][col+i] != '_' ){
						locked_3 = TRUE;
					}
				}
			}
			
			if( !locked_4 &&  col-i >= 0){
				if(piece == 'R' || piece == 'r' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'k'){
					if( board[row][col-i] == king ){
						finded = TRUE;
					}else if( board[row][col-i] != '_' ){
						locked_4 = TRUE;
					}
				}
			}
				
			/* Diagonally */
			
			if( !locked_5 &&  row+i < DIM_MATRIX && col+i < DIM_MATRIX){
				if(piece == 'P' || piece == 'B' || piece == 'b' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'k'){
					if( board[row+i][col+i] == king ){
						finded = TRUE;
					}else if( board[row+i][col+i] != '_' ){
						locked_5 = TRUE;
					}
				}
			}
			
			if( !locked_6 && row-i >= 0 && col+i < DIM_MATRIX ){
				if(piece == 'p' || piece == 'B' || piece == 'b' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'k'){
					if( board[row-i][col+i] == king ){
						finded = TRUE;
					}else if( board[row-i][col+i] != '_' ){
						locked_6 = TRUE;
					}
				}
			}
				
			if( !locked_7 && row+i < DIM_MATRIX && col-i >= 0 ){
				if(piece == 'P' || piece == 'B' || piece == 'b' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'k'){
					if( board[row+i][col-i] == king ){
						finded = TRUE;
					}else if( board[row+i][col-i] != '_' ){
						locked_7 = TRUE;
					}
				}
			}
			
			if( !locked_8 && row-i >= 0 && col-i >= 0 ){
				if(piece == 'p' || piece == 'B' || piece == 'b' || piece == 'Q' || piece == 'q' || piece == 'K' || piece == 'k'){
					if( board[row-i][col-i] == king ){
						finded = TRUE;
					}else if( board[row-i][col-i] != '_' ){
						locked_8 = TRUE;
					}
				}
			}
			i++;
		}
	}
	if(piece == 'N' || piece == 'n'){
		if(row-2 >= 0 && col+1 < DIM_MATRIX){
			if( board[row-2][col+1] == king ){
				finded = TRUE;
			}
		}
		
		if(row-1 >= 0 && col+2 < DIM_MATRIX){
			if( board[row-1][col+2] == king ){
				finded = TRUE;
			}
		}
		
		
		if(row+1 < DIM_MATRIX && col+2 < DIM_MATRIX){
			if( board[row+1][col+2] == king ){
				finded = TRUE;
			}
		}
		
		if(row+2 < DIM_MATRIX && col+1 < DIM_MATRIX){
			if( board[row+2][col+1] == king ){
				finded = TRUE;
			}
		}
		
		if(row+2 < DIM_MATRIX && col-1 >= 0){
			if( board[row+2][col-1] == king ){
				finded = TRUE;
			}
		}
		
		if(row+1 < DIM_MATRIX && col-2 >= 0){	
			if( board[row+1][col-2] == king ){
				finded = TRUE;
			}
		}
		
		if(row-1 >= 0 && col-2 >= 0){
			if( board[row-1][col-2] == king ){
				finded = TRUE;
			}
		}
		
		if(row-2 >= 0 && col-1 >= 0){
			if( board[row-2][col-1] == king ){
				finded = TRUE;
			}
		}
	}
	
	return finded;
}

/*
 * This function find if the player is ckeck
 * */
boolean check(SPChess* src){
	int i, j;
	char king;
	boolean finded = FALSE;

	if(src->currentPlayer == SP_WHITE)
		king = 'k';
	else
		king = 'K';
		
	for(i = 0; i < SP_N_ROWS; i++){
		for(j = 0; j < SP_N_COLUMNS; j++){
			if(src->board[i][j] != '_'){
				if(!isColor(src->currentPlayer, src->board[i][j])){
					if(findKing(src->board, src->board[i][j], i, j, king)){
						finded = TRUE;
					}
				}
			}
		}
	}
	return finded;
}

/*
 * This function find if the player isn't ckeckmate
 * */
boolean outCheckMate(SPChess* src){
	int row, col, k, piece_o, piece_d, max;
	boolean finded = FALSE;
	boolean locked_1, locked_2, locked_3, locked_4, locked_5, locked_6, locked_7, locked_8;
		
	for(row = 0; row < SP_N_ROWS; row++){
		for(col = 0; col < SP_N_COLUMNS; col++){
			if(src->board[row][col] != '_'){
				if(isColor(src->currentPlayer, src->board[row][col])){
					piece_o = src->board[row][col];
					src->board[row][col] = '_';
					max = 7;
					locked_1 = locked_2 = locked_3 = locked_4 = locked_5 = locked_6 = locked_7 = locked_8 = FALSE;

					if(piece_o == 'K' || piece_o == 'k'){
						max = 1;
					}
					
					if( (piece_o == 'P' || piece_o == 'p') && (row == 1 || row == 6) ){
						max = 2;
					}else if(piece_o == 'P' || piece_o == 'p'){
						max = 1;
					}
				
					k=1;
					
					if(piece_o != 'N' && piece_o != 'n' && piece_o != '_'){
						while(k <= max){
							
							/* Vertically */
							if( !locked_1 && row+k < DIM_MATRIX){
								if(piece_o == 'R' || piece_o == 'r' || piece_o == 'Q' || piece_o == 'q' || piece_o == 'K' || piece_o == 'k'){
									if( !isColor(src->currentPlayer, src->board[row+k][col]) ){
										piece_d = src->board[row+k][col];
										src->board[row+k][col] = piece_o;	
										if(!check(src)){
											src->board[row+k][col] = piece_d;
											finded = TRUE;
											break;
										}
										
										src->board[row+k][col] = piece_d;
										if(piece_d != '_'){
											locked_1 = TRUE;
										}
									}else{
										locked_1 = TRUE;
									}
								}
								
								if(piece_o == 'P'){
									if(src->board[row+k][col] == '_'){
										piece_d = src->board[row+k][col];
										src->board[row+k][col] = piece_o;
										if(!check(src)){
											src->board[row+k][col] = piece_d;
											finded = TRUE;
											break;
										}	
										src->board[row+k][col] = piece_d;
										
										if(piece_d != '_'){
											locked_1 = TRUE;
										}
									}else{
										locked_1 = TRUE;
									}
								}
							}
							
							if( !locked_2 &&  row-k >= 0){	
								if(piece_o == 'R' || piece_o == 'r' || piece_o == 'Q' || piece_o == 'q' || piece_o == 'K' || piece_o == 'k'){
									if( !isColor(src->currentPlayer, src->board[row-k][col]) ){
										piece_d = src->board[row-k][col];
										src->board[row-k][col] = piece_o;
										if(!check(src)){
											src->board[row-k][col] = piece_d;
											finded = TRUE;
											break;
										}	
										src->board[row-k][col] = piece_d;
										
										if(piece_d != '_'){
											locked_2 = TRUE;
										}
									}else{
										locked_2 = TRUE;
									}
								}
								
								if(piece_o == 'p'){
									if( src->board[row-k][col] == '_' ){
										piece_d = src->board[row-k][col];
										src->board[row-k][col] = piece_o;
										if(!check(src)){
											src->board[row-k][col] = piece_d;
											finded = TRUE;
											break;
										}	
										src->board[row-k][col] = piece_d;
										
										if(piece_d != '_'){
											locked_2 = TRUE;
										}
									}else{
										locked_2 = TRUE;
									}
								}
							}
								
							/* Horizontally */
							
							if( !locked_3 && col+k < DIM_MATRIX){	
								if(piece_o == 'R' || piece_o == 'r' || piece_o == 'Q' || piece_o == 'q' || piece_o == 'K' || piece_o == 'k'){
									if( !isColor(src->currentPlayer, src->board[row][col+k]) ){
										piece_d = src->board[row][col+k];
										src->board[row][col+k] = piece_o;
										if(!check(src)){
											src->board[row][col+k] = piece_d;
											finded = TRUE;
											break;
										}	
										src->board[row][col+k] = piece_d;
										
										if(piece_d != '_'){
											locked_3 = TRUE;
										}
									}else{
										locked_3 = TRUE;
									}
								}
							}
							
							if( !locked_4 && col-k >= 0){
								if(piece_o == 'R' || piece_o == 'r' || piece_o == 'Q' || piece_o == 'q' || piece_o == 'K' || piece_o == 'k'){
									if( !isColor(src->currentPlayer, src->board[row][col-k]) ){
										piece_d = src->board[row][col-k];
										src->board[row][col-k] = piece_o;
										if(!check(src)){
											src->board[row][col-k] = piece_d;
											finded = TRUE;
											break;
										}	
										src->board[row][col-k] = piece_d;
										
										if(piece_d != '_'){
											locked_4 = TRUE;
										}
									}else{
										locked_4 = TRUE;
									}
								}
							}
								
							/* Diagonally */
							
							if( !locked_5 && row+k < DIM_MATRIX && col+k < DIM_MATRIX ){
								if(piece_o == 'B' || piece_o == 'b' || piece_o == 'Q' || piece_o == 'q' || piece_o == 'K' || piece_o == 'k'){
									if( !isColor(src->currentPlayer, src->board[row+k][col+k]) ){
										piece_d = src->board[row+k][col+k];
										src->board[row+k][col+k] = piece_o;
										if(!check(src)){
											src->board[row+k][col+k] = piece_d;
											finded = TRUE;
											break;
										}	
										src->board[row+k][col+k] = piece_d;
											
										if(piece_d != '_'){
											locked_5 = TRUE;
										}
									}else{
										locked_5 = TRUE;
									}
								}
								
								if(piece_o == 'P'){
									locked_5 = TRUE;
									if( !isColor(src->currentPlayer, src->board[row+k][col+k]) && src->board[row+k][col+k] != '_'){
										piece_d = src->board[row+k][col+k];
										src->board[row+k][col+k] = piece_o;
										if(!check(src)){
											src->board[row+k][col+k] = piece_d;
											finded = TRUE;
											break;
										}	
										src->board[row+k][col+k] = piece_d;
									}
								}
							}
							
							if( !locked_6 && row-k >= 0 && col+k < DIM_MATRIX){
								if(piece_o == 'B' || piece_o == 'b' || piece_o == 'Q' || piece_o == 'q' || piece_o == 'K' || piece_o == 'k'){
									if( !isColor(src->currentPlayer, src->board[row-k][col+k]) ){
										piece_d = src->board[row-k][col+k];
										src->board[row-k][col+k] = piece_o;
										if(!check(src)){
											src->board[row-k][col+k] = piece_d;
											finded = TRUE;
											break;
										}	
										src->board[row-k][col+k] = piece_d;
										
										if(piece_d != '_'){
											locked_6 = TRUE;
										}
									}else{
										locked_6 = TRUE;
									}
								}
								
								if(piece_o == 'p'){
									locked_6 = TRUE;
									if( !isColor(src->currentPlayer, src->board[row-k][col+k]) && src->board[row-k][col+k] != '_'){
										piece_d = src->board[row-k][col+k];
										src->board[row-k][col+k] = piece_o;
										if(!check(src)){
											src->board[row-k][col+k] = piece_d;
											finded = TRUE;
											break;
										}	
										src->board[row-k][col+k] = piece_d;
									}
								}
							}
								
							if( !locked_7 && row+k < DIM_MATRIX && col-k >= 0 ){
								if(piece_o == 'B' || piece_o == 'b' || piece_o == 'Q' || piece_o == 'q' || piece_o == 'K' || piece_o == 'k'){
									if( !isColor(src->currentPlayer, src->board[row+k][col-k]) ){
										piece_d = src->board[row+k][col-k];
										src->board[row+k][col-k] = piece_o;
										if(!check(src)){
											src->board[row+k][col-k] = piece_d;
											finded = TRUE;
											break;
										}	
										src->board[row+k][col-k] = piece_d;
										
										if(piece_d != '_'){
											locked_7 = TRUE;
										}
									}else{
										locked_7 = TRUE;
									}
								}
								
								if(piece_o == 'P'){
									locked_7 = TRUE;
									if( !isColor(src->currentPlayer, src->board[row+k][col-k]) && src->board[row+k][col-k] != '_'){
										piece_d = src->board[row+k][col-k];
										src->board[row+k][col-k] = piece_o;
										if(!check(src)){
											src->board[row+k][col-k] = piece_d;
											finded = TRUE;
											break;
										}	
										src->board[row+k][col-k] = piece_d;
									}
								}
							}
							
							if( !locked_8 && row-k >= 0 && col-k >= 0){
								if(piece_o == 'B' || piece_o == 'b' || piece_o == 'Q' || piece_o == 'q' || piece_o == 'K' || piece_o == 'k'){
									if( !isColor(src->currentPlayer, src->board[row-k][col-k]) ){
										piece_d = src->board[row-k][col-k];
										src->board[row-k][col-k] = piece_o;
										if(!check(src)){
											src->board[row-k][col-k] = piece_d;
											finded = TRUE;
											break;
										}	
										src->board[row-k][col-k] = piece_d;
										
										if(piece_d != '_'){
											locked_8 = TRUE;
										}
									}else{
										locked_8 = TRUE;
									}
								}
								
								if(piece_o == 'p'){
									locked_8 = TRUE;
									if( !isColor(src->currentPlayer, src->board[row-k][col-k]) && src->board[row-k][col-k] != '_' ){
										piece_d = src->board[row-k][col-k];
										src->board[row-k][col-k] = piece_o;
										if(!check(src)){
											src->board[row-k][col-k] = piece_d;
											finded = TRUE;
											break;
										}	
										src->board[row-k][col-k] = piece_d;
									}
								}
							}
							k++;
						}
					}
					if((piece_o == 'N' || piece_o == 'n') && (piece_o != '_') ){
						if(row-2 >= 0 && col+1 < DIM_MATRIX){
							if( !isColor(src->currentPlayer, src->board[row-2][col+1]) ){
								piece_d = src->board[row-2][col+1];
								src->board[row-2][col+1] = piece_o;
								if(!check(src)){
									src->board[row-2][col+1] = piece_d;
									finded = TRUE;
								}	
								src->board[row-2][col+1] = piece_d;
							}
						}
						
						if(row-1 >= 0 && col+2 < DIM_MATRIX){
							if( !isColor(src->currentPlayer, src->board[row-1][col+2]) ){
								piece_d = src->board[row-1][col+2];
								src->board[row-1][col+2] = piece_o;
								if(!check(src)){
									src->board[row-1][col+2] = piece_d;
									finded = TRUE;
								}
								src->board[row-1][col+2] = piece_d;
							}
						}
						
						if(row+1 < DIM_MATRIX && col+2 < DIM_MATRIX){
							if( !isColor(src->currentPlayer, src->board[row+1][col+2]) ){
								piece_d = src->board[row+1][col+2];
								src->board[row+1][col+2] = piece_o;
								if(!check(src)){
									src->board[row+1][col+2] = piece_d;
									finded = TRUE;
								}
								src->board[row+1][col+2] = piece_d;
							}
						}
						
						if(row+2 < DIM_MATRIX && col+1 < DIM_MATRIX){
							if( !isColor(src->currentPlayer, src->board[row+2][col+1]) ){
								piece_d = src->board[row+2][col+1];
								src->board[row+2][col+1] = piece_o; 
								if(!check(src)){
									src->board[row+2][col+1] = piece_d;
									finded = TRUE;
								}
								src->board[row+2][col+1] = piece_d;
							}
						}
						
						if(row+2 < DIM_MATRIX && col-1 >= 0){
							if( !isColor(src->currentPlayer, src->board[row+2][col-1]) ){
								piece_d = src->board[row+2][col-1];
								src->board[row+2][col-1] = piece_o;
								if(!check(src)){
									src->board[row+2][col-1] = piece_d;
									finded = TRUE;
								}
								src->board[row+2][col-1] = piece_d;
							}
						}
						
						if(row+1 < DIM_MATRIX && col-2 >= 0){
							if( !isColor(src->currentPlayer, src->board[row+1][col-2]) ){
								piece_d = src->board[row+1][col-2];
								src->board[row+1][col-2] = piece_o;
								if(!check(src)){
									src->board[row+1][col-2] = piece_d;
									finded = TRUE;
								}
								src->board[row+1][col-2] = piece_d;
							}
						}
							
						if(row-1 >= 0 && col-2 >= 0){
							if( !isColor(src->currentPlayer, src->board[row-1][col-2]) ){
								piece_d = src->board[row-1][col-2];
								src->board[row-1][col-2] = piece_o;
								if(!check(src)){
									src->board[row-1][col-2] = piece_d;
									finded = TRUE;
								}
								src->board[row-1][col-2] = piece_d;
							}
						}
						
						if(row-2 >= 0 && col-1 >= 0){
							if( !isColor(src->currentPlayer, src->board[row-2][col-1]) ){
								piece_d = src->board[row-2][col-1];
								src->board[row-2][col-1] = piece_o;
								if(!check(src)){
									src->board[row-2][col-1] = piece_d;
									finded = TRUE;
								}
								src->board[row-2][col-1] = piece_d;
							}
						}
					}
					src->board[row][col] = piece_o;
				}
			}
			if(finded)
				break;
		}
		if(finded)
			break;
	}
	return finded;
}

/*
 * This function save the movement done by the player
 * */
void moveSave(SPChess* src, tMoves * history){
	if(history->n != 3){
		history->data[history->n].piece_o 	= src->piece_o;
		history->data[history->n].piece_d 	= src->piece_d;
		history->data[history->n].row_o 	= src->row_o;
		history->data[history->n].col_o 	= src->col_o;
		history->data[history->n].row_d 	= src->row_d;
		history->data[history->n].col_d 	= src->col_d;
		history->n+=1;
	 }else{
		history->data[0] = history->data[1];
						
		history->data[1] = history->data[2];
							
		history->data[2].piece_o 	= src->piece_o;
		history->data[2].piece_d 	= src->piece_d;
		history->data[2].row_o 		= src->row_o;
		history->data[2].col_o 		= src->col_o;
		history->data[2].row_d 		= src->row_d;
		history->data[2].col_d 		= src->col_d;
	}
	
}

bool isValidEntry(int row, int col) {
	if (row < 0 || row > SP_N_ROWS-1 || col < 0 || col > SP_N_COLUMNS-1) {
		return false;
	}
	return true;
}

/*
 * Default Game Settings
 * */
void spChessDefaultSettins(SPChess* src){
	src->gameMode 	= '1';
	src->diff		= '2';
	src->currentPlayer	= SP_WHITE;
}

/*
 * Print default Game Settings (console mode)
 * */
void spChessPrintSettins(SPChess* src){
	if(src->gameMode == '1'){
		printf("SETTINGS:\n");
		printf("GAME_MODE: 1\n");
		printf("DIFFICULTY_LVL: %c\n", src->diff);
		if(src->currentPlayer == SP_WHITE)
			printf("USER_CLR: WHITE\n");
		else
			printf("USER_CLR: BLACK\n");
	}else{
		printf("SETTINGS:\n");
		printf("GAME_MODE: 2\n");
	}
}

/*
 * This function create an initial chess game
 * */
SPChess* spChessCreate() {
	SPChess* res = (SPChess*) malloc(sizeof(SPChess));
	if (res == NULL ) {
		return NULL ;
	}
	
	spChessDefaultSettins(res);
	spChessRestart(res);
	res->currentPlayer = SP_WHITE;
	return res;
}

/*
 * The program state is switched to the setting state.
 * */
void spChessRestart(SPChess* res){
	int i, j;
	
	res->row_o = res->row_o = -1;
	res->row_d = res->row_d = -1;
	res->change = FALSE;
	res->check = CHESS_NOCHECK;
	res->checkMate = CHESS_NOCHECKMATE;
	res->posBlackKing.row = 0;
	res->posBlackKing.col = 4;
	res->posWhiteKing.row = 7;
	res->posWhiteKing.col = 4;
	res->board[0][0] = SP_BLACK_ROOK_SYMBOL; 									
	res->board[0][1] = SP_BLACK_KNIGHT_SYMBOL; 									
	res->board[0][2] = SP_BLACK_BISHOP_SYMBOL; 									
	res->board[0][3] = SP_BLACK_QUEEN_SYMBOL;
	res->board[0][4] = SP_BLACK_KING_SYMBOL;
	res->board[0][5] = SP_BLACK_BISHOP_SYMBOL;
	res->board[0][6] = SP_BLACK_KNIGHT_SYMBOL;
	res->board[0][7] = SP_BLACK_ROOK_SYMBOL;
	
	res->board[1][0] = SP_BLACK_PAWN_SYMBOL; 									
	res->board[1][1] = SP_BLACK_PAWN_SYMBOL; 									
	res->board[1][2] = SP_BLACK_PAWN_SYMBOL; 									
	res->board[1][3] = SP_BLACK_PAWN_SYMBOL;
	res->board[1][4] = SP_BLACK_PAWN_SYMBOL;
	res->board[1][5] = SP_BLACK_PAWN_SYMBOL;
	res->board[1][6] = SP_BLACK_PAWN_SYMBOL;
	res->board[1][7] = SP_BLACK_PAWN_SYMBOL;
	for (i = 2; i < SP_N_ROWS-2; i++) {
		for (j = 0; j < SP_N_COLUMNS; j++) {
			res->board[i][j] = SP_EMPTY_ENTRY;
		}
	}
	
	res->board[6][0] = SP_WHITE_PAWN_SYMBOL; 									
	res->board[6][1] = SP_WHITE_PAWN_SYMBOL; 									
	res->board[6][2] = SP_WHITE_PAWN_SYMBOL; 									
	res->board[6][3] = SP_WHITE_PAWN_SYMBOL;
	res->board[6][4] = SP_WHITE_PAWN_SYMBOL;
	res->board[6][5] = SP_WHITE_PAWN_SYMBOL;
	res->board[6][6] = SP_WHITE_PAWN_SYMBOL;
	res->board[6][7] = SP_WHITE_PAWN_SYMBOL;
	
	res->board[7][0] = SP_WHITE_ROOK_SYMBOL; 									
	res->board[7][1] = SP_WHITE_KNIGHT_SYMBOL; 									
	res->board[7][2] = SP_WHITE_BISHOP_SYMBOL; 									
	res->board[7][3] = SP_WHITE_QUEEN_SYMBOL;
	res->board[7][4] = SP_WHITE_KING_SYMBOL;
	res->board[7][5] = SP_WHITE_BISHOP_SYMBOL;
	res->board[7][6] = SP_WHITE_KNIGHT_SYMBOL;
	res->board[7][7] = SP_WHITE_ROOK_SYMBOL;
	//spChessResetHighLightBoard(res);
	playerHistory.n = 0;
	IAHistory.n = 0;
	if(res->gameMode == '2'){
		res->currentPlayer = SP_WHITE;
	}
}


void spChessResetHighLightBoard(SPChess* src){
	int i, j;
	for (i = 0; i < SP_N_ROWS; i++) {
		for (j = 0; j < SP_N_COLUMNS; j++) {
			src->highlightboard[i][j] = SP_EMPTY_ENTRY;
		}
	}
}

void spChessDestroy(SPChess* src) {
	if (!src) {
		return;
	}
	free(src);
}

void spChessSetPosOrigin(SPChess* src, int row, int col) {
	if (src == NULL || !isValidEntry(row, col)) {
		return;
	}
	
	src->piece_o = src->board[row][col];
	src->row_o = row;
	src->col_o = col;
	
}

void spChessSetPosDestiny(SPChess* src, int row, int col) {
	if (src == NULL || !isValidEntry(row, col)) {
		return;
	}
	
	src->piece_d = src->board[row][col];
	src->row_d = row;
	src->col_d = col;
}

/*
 * Print error (Cosole mode)
 * */
void printError(SP_CHESS_ERROR error){
	if(error == CHESS_ILLEGAL_MOVE)
		printf("Illegal move\n");
	else if(error == CHESS_NOT_CONTAIN_YOUR_PIECE)
		printf("The specified position does not contain your piece\n");
}

/*
 * This function do the user turn by moving the piece at
 * <x,y> to the <i,j> location. x and I represent the row number, which can be
 * between 1-8. The values of y and j represents the column letter, which can
 * be between A-H (upper case). For example:
 * move <2,A> to <3,A>
 * */
void spChessSetMove(SPChess* src) {
	char king;
	src->error = spChessCheckMove(src);
	if (src == NULL || src->error != CHESS_NOERR) {
		src->row_o = src->row_o = -1;
		src->row_d = src->row_d = -1;
		if(src->mode == 'c')
			printError(src->error);
		return;
	}
	
	src->board[src->row_d][src->col_d] = src->piece_o;
	src->board[src->row_o][src->col_o] = '_';
	if(src->piece_o == 'K'){
		src->posBlackKing.row = src->row_d;
		src->posBlackKing.col = src->col_d;
	}else{
		src->posWhiteKing.row = src->row_d;
		src->posWhiteKing.col = src->col_d;		
	}
	if(!check(src)){
		src->change = TRUE;
		moveSave(src, &playerHistory);
		if(src->currentPlayer == SP_WHITE)
			king = 'K';
		else
			king = 'k';
		src->currentPlayer = nextPlayer(src->currentPlayer);
		if(findKing(src->board, src->piece_o, src->row_d, src->col_d, king)){
			if(king == 'K')
				src->check = CHESS_CHECK_BLACK;
			else
				src->check = CHESS_CHECK_WHITE;
			
			if(outCheckMate(src)){
				src->checkMate = CHESS_NOCHECKMATE;
			}else{
				if(king == 'K'){
					src->check = CHESS_NOCHECK;
					src->checkMate = CHESS_CHECKMATE_BLACK;
				}else{
					src->check = CHESS_NOCHECK;
					src->checkMate = CHESS_CHECKMATE_WHITE;
				}
			}
		}else{
			src->check = CHESS_NOCHECK;
			src->checkMate = CHESS_NOCHECKMATE;
		}
		
		if(src->gameMode == '1'){
			spChessSetMoveIA(src);
		}
	}else{
		src->board[src->row_o][src->col_o] = src->piece_o;
		src->board[src->row_d][src->col_d] = src->piece_d;
	}

	src->row_o = src->row_o = -1;
	src->row_d = src->row_d = -1;
}

/*
 * This function do the Computer AI turn by moving the piece at
 * <x,y> to the <i,j> location. x and I represent the row number, which can be
 * between 1-8. The values of y and j represents the column letter, which can
 * be between A-H (upper case). For example: move <2,A> to <3,A>
 * */
void spChessSetMoveIA(SPChess* src) {
	char king;
	
	findPositionIA(src, src->currentPlayer , src->diff-'0', -1000, 1000);
	spChessSetPosOrigin(src, src->row_o, src->col_o);
	spChessSetPosDestiny(src, src->row_d, src->col_d);
	//moveSave(src, &IAHistory);
	src->board[src->row_d][src->col_d] = src->piece_o;
	src->board[src->row_o][src->col_o] = '_';
	
	if(src->piece_o == 'K'){
		src->posBlackKing.row = src->row_d;
		src->posBlackKing.col = src->col_d;
	}else{
		src->posWhiteKing.row = src->row_d;
		src->posWhiteKing.col = src->col_d;		
	}
	if(!check(src)){
		src->change = TRUE;
		moveSave(src, &IAHistory);
		if(src->currentPlayer == SP_WHITE)
			king = 'K';
		else
			king = 'k';
		src->currentPlayer = nextPlayer(src->currentPlayer);
		if(findKing(src->board, src->piece_o, src->row_d, src->col_d, king)){
			if(king == 'K')
				src->check = CHESS_CHECK_BLACK;
			else
				src->check = CHESS_CHECK_WHITE;
			
			if(outCheckMate(src)){
				src->checkMate = CHESS_NOCHECKMATE;
			}else{
				if(king == 'K'){
					src->check = CHESS_NOCHECK;
					src->checkMate = CHESS_CHECKMATE_BLACK;
				}else{
					src->check = CHESS_NOCHECK;
					src->checkMate = CHESS_CHECKMATE_WHITE;
				}
			}
		}else{
			src->check = CHESS_NOCHECK;
			src->checkMate = CHESS_NOCHECKMATE;
		}
	}else{
		src->board[src->row_o][src->col_o] = src->piece_o;
		src->board[src->row_d][src->col_d] = src->piece_d;
	}
	if(src->mode == 'c'){
		if(src->piece_o == 'P' || src->piece_o == 'p')
			printf("Computer: move [pawn] at <%c,%c> to <%c,%c>\n", getRow(src->row_o), getCol(src->col_o), getRow(src->row_d), getCol(src->col_d));
		else if(src->piece_o == 'B' || src->piece_o == 'b')
			printf("Computer: move [bishop] at <%c,%c> to <%c,%c>\n", getRow(src->row_o), getCol(src->col_o), getRow(src->row_d), getCol(src->col_d));
		else if(src->piece_o == 'N' || src->piece_o == 'n')	
			printf("Computer: move [knight] at <%c,%c> to <%c,%c>\n", getRow(src->row_o), getCol(src->col_o), getRow(src->row_d), getCol(src->col_d));
		else if(src->piece_o == 'R' || src->piece_o == 'r')	
			printf("Computer: move [rook] at <%c,%c> to <%c,%c>\n", getRow(src->row_o), getCol(src->col_o), getRow(src->row_d), getCol(src->col_d));
		else if(src->piece_o == 'Q' || src->piece_o == 'q')
			printf("Computer: move [queen] at <%c,%c> to <%c,%c>\n", getRow(src->row_o), getCol(src->col_o), getRow(src->row_d), getCol(src->col_d));
		else if(src->piece_o == 'K' || src->piece_o == 'k')
			printf("Computer: move [king] at <%c,%c> to <%c,%c>\n", getRow(src->row_o), getCol(src->col_o), getRow(src->row_d), getCol(src->col_d));
	}
}

bool spChessIsGameOver(SPChess* src) {
	int i, j;
	if (!src) {
		return true;
	}
	for ( i = 0; i < SP_N_ROWS; i++) {
		for (j = 0; j < SP_N_COLUMNS; j++) {
			if (src->board[i][j] == SP_EMPTY_ENTRY) {
				return false;
			}
		}
	}
	return true;
}

char spChessCheckWinner(SPChess* src) {
	int i, j;
	if (!src) {
		return '\0';
	}
	if (src->board[0][0] != SP_EMPTY_ENTRY
			&& src->board[0][0] == src->board[1][1]
			&& src->board[1][1] == src->board[2][2]) {
		return src->board[0][0];
	}
	if (src->board[0][2] != SP_EMPTY_ENTRY
			&& src->board[0][2] == src->board[1][1]
			&& src->board[1][1] == src->board[2][0]) {
		return src->board[0][2];
	}

	for (i = 0; i < SP_N_ROWS; i++) {
			char prev = src->board[i][0];
			if (prev == SP_EMPTY_ENTRY) {
				continue;
			}
			for (j = 0; j < SP_N_COLUMNS; j++) {
				if(src->board[i][j]!=prev){
					break;
				}
				if(SP_N_COLUMNS-1==j){
					return prev;
				}
			}
		}
	for (i = 0; i < SP_N_ROWS; i++) {
		char prev = src->board[0][i];
		if (prev == SP_EMPTY_ENTRY) {
			continue;
		}
		for (j = 0; j < SP_N_COLUMNS; j++) {
			if(src->board[j][i]!=prev){
				break;
			}
			if(SP_N_COLUMNS-1==j){
				return prev;
			}
		}
	}
	return SP_EMPTY_ENTRY;
}

char spChessGetPiece(SPChess* src, int row, int col){
	return src->board[row][col];
}

/*
 * this function check for errors 
 * */
SP_CHESS_ERROR spChessCheckMove(SPChess* src){
	if( !isColor(src->currentPlayer, src->piece_o) ){
		return CHESS_NOT_CONTAIN_YOUR_PIECE;
	}
	
	if( isColor(src->currentPlayer, src->piece_d) ){
		return CHESS_ILLEGAL_MOVE;
	}
	
	if( !findPosition(src) ){
		return CHESS_ILLEGAL_MOVE;
	}
	
	
	return CHESS_NOERR;
}

void spChessSetCurrentPlayer(SPChess* src, SP_COLOR currentPlayer){
	src->currentPlayer = currentPlayer;
}

void spChessSetDiff(SPChess* src, char diff){
	src->diff = diff;
}

void spChessSetGameMode(SPChess* src, char gameMode){
	src->gameMode = gameMode;
}
/*
 * Undo previous moves done by the user. This command is
 * available only in a '1-player' mode. The user may undo up to 3 moves. Thus,
 * you need to store the previous 3 moves for the user and the AI opponent.
 * The game saves the last three moves done by the user while least recent
 * moves will be forgotten. A move that is “forgotten” cannot be undone.
 * */
void spChessUndo(SPChess* src){
	if(playerHistory.n > 0){
		src->change = TRUE;
		playerHistory.n-=1;
		IAHistory.n-=1;
		
		if(src->mode == 'c'){
			if (src->currentPlayer == SP_WHITE){
				printf("Undo move for player white : <%c,%c> -> <%c,%c>\n", getRow(playerHistory.data[playerHistory.n].row_o), getCol(playerHistory.data[playerHistory.n].col_o), getRow(playerHistory.data[playerHistory.n].row_d), getCol(playerHistory.data[playerHistory.n].col_d));
				printf("Undo move for player black : <%c,%c> -> <%c,%c>\n", getRow(IAHistory.data[IAHistory.n].row_o), getCol(IAHistory.data[IAHistory.n].col_o), getRow(IAHistory.data[IAHistory.n].row_d), getCol(IAHistory.data[IAHistory.n].col_d));
			}else{
				printf("Undo move for player black : <%c,%c> -> <%c,%c>\n", getRow(playerHistory.data[playerHistory.n].row_o), getCol(playerHistory.data[playerHistory.n].col_o), getRow(playerHistory.data[playerHistory.n].row_d), getCol(playerHistory.data[playerHistory.n].col_d));
				printf("Undo move for player white : <%c,%c> -> <%c,%c>\n", getRow(IAHistory.data[IAHistory.n].row_o), getCol(IAHistory.data[IAHistory.n].col_o), getRow(IAHistory.data[IAHistory.n].row_d), getCol(IAHistory.data[IAHistory.n].col_d));
			}
		}
		src->board[IAHistory.data[IAHistory.n].row_o][IAHistory.data[IAHistory.n].col_o] = IAHistory.data[IAHistory.n].piece_o;
		src->board[IAHistory.data[IAHistory.n].row_d][IAHistory.data[IAHistory.n].col_d] = IAHistory.data[IAHistory.n].piece_d;
		
		src->board[playerHistory.data[playerHistory.n].row_o][playerHistory.data[playerHistory.n].col_o] = playerHistory.data[playerHistory.n].piece_o;
		src->board[playerHistory.data[playerHistory.n].row_d][playerHistory.data[playerHistory.n].col_d] = playerHistory.data[playerHistory.n].piece_d;

	}else if(src->mode == 'c'){
		printf("Empty history, move cannot be undone\n");
	}
}

/*
 * This function save the current game state to the specified file
 * */
void spChessLoad(SPChess* src){
	
	int i;
	FILE * chessFile;
    char row;
	
    chessFile = fopen(src->slot ,"r");
    int a;
    if (chessFile == NULL)
    {
        printf("Error: File doesn’t exist or cannot be opened\n");
    }
    else
    {
        
			fscanf(chessFile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
			fscanf(chessFile, "<game>\n");
			fscanf(chessFile, "<current_turn>%d</current_turn>\n",&a);
			src->currentPlayer = a;
			fscanf(chessFile, "<game_mode>%c</game_mode >\n", &src->gameMode);
			if(src->gameMode == '1'){
				fscanf(chessFile, "<difficulty>%c</difficulty>\n", &src->diff);
				fscanf(chessFile, "<user_color>%d</user_color>\n", &a);
				src->currentPlayer = a;
			}else{
				fscanf(chessFile, "<difficulty> </difficulty>\n");
				fscanf(chessFile, "<user_color> </user_color>\n");
			}
			fscanf(chessFile, "<board>\n");


			for(i = 0; i < DIM_MATRIX; i++){
				fscanf(chessFile, "<row_%c>%c%c%c%c%c%c%c%c</row_%c>\n", &row, &src->board[i][0], &src->board[i][1], &src->board[i][2], &src->board[i][3], &src->board[i][4], &src->board[i][5], &src->board[i][6], &src->board[i][7], &row);
				//printf("<row_%c>%c%c%c%c%c%c%c%c</row_%c>\n", row, src->board[i][0], src->board[i][1], src->board[i][2], src->board[i][3], src->board[i][4], src->board[i][5], src->board[i][6], src->board[i][7], row);

			}
			fscanf(chessFile, "</board>\n");
			fscanf(chessFile, "<general>\n");
			fscanf(chessFile, "<player_undos>%d</player_undos>\n", &playerHistory.n);
			fscanf(chessFile, "<player_undos>%d</player_undos>\n", &IAHistory.n);
			for(i = 0; i < playerHistory.n; i++){
				fscanf(chessFile, "<move>\n");
				fscanf(chessFile, "<player_history>(%d,%d) to (%d,%d)</player_history>\n", &playerHistory.data[i].row_o, &playerHistory.data[i].col_o, &playerHistory.data[i].row_d, &playerHistory.data[i].col_d);
				fscanf(chessFile, "<piece_o>%c</piece_o>\n", &playerHistory.data[i].piece_o);
				fscanf(chessFile, "<piece_d>%c</piece_d>\n", &playerHistory.data[i].piece_d);
				fscanf(chessFile, "<ia_history>(%d,%d) to (%d,%d)</ia_history>\n", &IAHistory.data[i].row_o, &IAHistory.data[i].col_o, &IAHistory.data[i].row_d, &IAHistory.data[i].col_d);
				fscanf(chessFile, "<piece_o>%c</piece_o>\n", &IAHistory.data[i].piece_o);
				fscanf(chessFile, "<piece_d>%c</piece_d>\n", &IAHistory.data[i].piece_d);
				fscanf(chessFile, "</move>\n");
			}
			fscanf(chessFile, "<check>%d</check>\n", &a);
			src->check = a;
			fscanf(chessFile, "<checkmate>%d</checkmate>\n", &a);
			src->checkMate = a;
			fscanf(chessFile, "</general>\n");
			fscanf(chessFile, "</game>\n");
            
    }
    
    
	
}
/*
 * This function save the current game state to the specified file 
 * */
 
void spChessSave(SPChess* src){
	
	int i, row;
	FILE * chessFile;
	
	
    chessFile = fopen(src->slot,"w");
 
	if (chessFile == NULL)
    {
        printf("File cannot be created or modified\n");
    }
    else
    {
		src->change = FALSE;
		fprintf(chessFile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		fprintf(chessFile, "<game>\n");
		fprintf(chessFile, "<current_turn>%d</current_turn>\n",src->currentPlayer);
		fprintf(chessFile, "<game_mode>%c</game_mode >\n", src->gameMode);
		if(src->gameMode == '1'){
			fprintf(chessFile, "<difficulty>%c</difficulty>\n", src->diff);
			fprintf(chessFile, "<user_color>%d</user_color>\n", src->currentPlayer);
		}else{
			fprintf(chessFile, "<difficulty> </difficulty>\n");
			fprintf(chessFile, "<user_color> </user_color>\n");
		}
		fprintf(chessFile, "<board>\n");
		
		row = 8;
		for(i = 0; i < DIM_MATRIX; i++){
			fprintf(chessFile, "<row_%c>%c%c%c%c%c%c%c%c</row_%c>\n", (row-i)+'0', src->board[i][0], src->board[i][1], src->board[i][2], src->board[i][3], src->board[i][4], src->board[i][5], src->board[i][6], src->board[i][7], (row-i)+'0');
			//printf("<row_%c>%c%c%c%c%c%c%c%c</row_%c>\n", row, src->board[i][0], src->board[i][1], src->board[i][2], src->board[i][3], src->board[i][4], src->board[i][5], src->board[i][6], src->board[i][7], row);
		}
				
		fprintf(chessFile, "</board>\n");
		fprintf(chessFile, "<general>\n");
		fprintf(chessFile, "<player_undos>%d</player_undos>\n", playerHistory.n);
		fprintf(chessFile, "<player_undos>%d</player_undos>\n", IAHistory.n);
		for(i = 0; i < playerHistory.n; i++){
			fprintf(chessFile, "<move>\n");
			fprintf(chessFile, "<player_history>(%d,%d) to (%d,%d)</player_history>\n", playerHistory.data[i].row_o, playerHistory.data[i].col_o, playerHistory.data[i].row_d, playerHistory.data[i].col_d);
			fprintf(chessFile, "<piece_o>%c</piece_o>\n", playerHistory.data[i].piece_o);
			fprintf(chessFile, "<piece_d>%c</piece_d>\n", playerHistory.data[i].piece_d);
			fprintf(chessFile, "<ia_history>(%d,%d) to (%d,%d)</ia_history>\n", IAHistory.data[i].row_o, IAHistory.data[i].col_o, IAHistory.data[i].row_d, IAHistory.data[i].col_d);
			fprintf(chessFile, "<piece_o>%c</piece_o>\n", IAHistory.data[i].piece_o);
			fprintf(chessFile, "<piece_d>%c</piece_d>\n", IAHistory.data[i].piece_d);
			fprintf(chessFile, "</move>\n");
		}
		fprintf(chessFile, "<check>%d</check>\n", src->check);
		fprintf(chessFile, "<checkmate>%d</checkmate>\n", src->checkMate);
		fprintf(chessFile, "</general>\n");
		fprintf(chessFile, "</game>\n");
 	}
 	
 	fclose ( chessFile );
   
	
}


void spChessSetSlot(SPChess* src, char* slot){
	sprintf(src->slot,"%s", slot);
}

SP_CHESS_ERROR spChessError(SPChess* src){
	return src->error;
}

boolean spChessChange(SPChess* src){
	return src->change;
}
