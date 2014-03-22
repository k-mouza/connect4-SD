#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "../include/gameplay.h"
#include "../include/ai_player.h"
#include "../include/output.h"

#define MAXNAME 20

int main(int argc, char **argv)
{
	int player2, difficulty, first_pl;
	board_type *board;
	
	srand (time(NULL));

	user_input(&player2, &difficulty, &first_pl);
	
	parse_input(&player2, difficulty, &first_pl);
	
	board = createBoard(7, 6, first_pl);
	
	if (first_pl == PLAYER_ONE || player2 == HUMAN)
		// if the first player is human then print the empty board
		toString(board);

	// main loop that ends when a winner is found or when it is a tie
	while((winnerIs(board)==0) && validMovesLeft(board))
	{
		if (getPlayer(board) == PLAYER_ONE)
			human_play(board, PLAYER_ONE);
		else if (player2 == HUMAN)
			human_play(board, PLAYER_TWO);
		else
			com_play(board);

		toString(board);
	}
	
	// print the final winner or a message that it is a tie
	if(winnerIs(board) == PLAYER_ONE)
		printf("Player 1 is the winner !!!\n\n");
	else if(winnerIs(board) == PLAYER_TWO)
		printf("Player 2 is the winner !!!\n\n");
	else
		printf("It's a tie\n\n");
		
	deleteboard(board);
	
	return 0;
}