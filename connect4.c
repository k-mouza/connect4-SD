#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "gameplay.h"
#include "ai_player.h"
#include "output.h"

#define MAXNAME 20

int main(int argc, char **argv)
{
	int player2, difficulty=1, first_pl;
	board_type *board;
	
	srand (time(NULL));

	printf("\nEnter the type of Player 2 (\"1\" or \"2\"):\n\t1. Computer\n\t2. Human\n");
	do
	{
		scanf("%d", &player2);
	}while( player2 != 1 && player2 != 2 );


	if (player2 == 1)
	{
		printf("Choose computer difficulty (1, 2 or 3):\n\t1. Easy\n\t2. Normal\n\t3. Hard\n");
		do
		{
			scanf("%d", &difficulty);
		}while( difficulty != 1 && difficulty != 2 && difficulty != 3);
	}

	
	printf("Type \"1\" if you want to be first OR \"2\" if you want Player 2 to be first:\n");
	do
	{
		scanf("%d", &first_pl);
	}while( first_pl != 1 && first_pl != 2 );
	
	
	parse_input(&player2, difficulty, &first_pl);
	
	board = createBoard(7, 6, first_pl);
	toString(board);

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
	
	if(winnerIs(board) == PLAYER_ONE)
		printf("Player 1 is the winner !!!\n\n");
	else if(winnerIs(board) == PLAYER_TWO)
		printf("Player 2 is the winner !!!\n\n");
	else
		printf("It's a tie\n\n");
		
	deleteboard(board);
	
	return 0;
}