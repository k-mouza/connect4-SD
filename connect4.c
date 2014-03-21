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
	int player2, difficulty, first_pl;
	board_type *board;
	
	srand (time(NULL));

	printf("\nEnter the type of Player 2 ('1' or '2'):\n\t1. Computer\n\t2. Human\n");
	do
	{
		scanf("%d", &player2);
		if (player2 != 1 && player2 != 2)
			printf("Enter '1' or '2'\n");
			
	}while( player2 != 1 && player2 != 2 );


	if (player2 == 1)
	{
		printf("Choose computer difficulty ('1', '2' or '3'):\n\t1. Easy\n\t2. Normal\n\t3. Hard\n");
		do
		{
			scanf("%d", &difficulty);
			if (difficulty != 1 && difficulty != 2 && difficulty != 3)
				printf("Enter '1', '2' or '3'\n");
			
		}while( difficulty != 1 && difficulty != 2 && difficulty != 3 );
	}

	
	printf("Type '1' if you want to play first or '2' if you want Player 2 to play first:\n");
	do
	{
		scanf("%d", &first_pl);
		if (first_pl != 1 && first_pl != 2)
			printf("Enter '1' or '2'\n");
		
	}while( first_pl != 1 && first_pl != 2 );
	
	
	parse_input(&player2, difficulty, &first_pl);
	
	board = createBoard(7, 6, first_pl);
	
	if (first_pl == PLAYER_ONE || player2 == HUMAN)
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