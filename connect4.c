#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "gameplay.h"
#include "ai_player.h"
#include "output.h"

int main(int argc, char **argv)
{
	int input;
	board_type *board = createBoard(7,6);

	srand (time(NULL));

	while((winnerIs(board)==0) && validMovesLeft(board))
	{
		if(getPlayer(board) == PLAYER_ONE)	
		{
			do
			{
				printf("Insert column number: ");
				scanf("%d", &input);
				printf("\n");
				
				if(input < 0 || input > board->cols-1)
					printf("Provide a column number between 0 and %d\n", board->cols-1);
				else if(!validMove(board, input))
					printf("Column is full. Choose another one.\n");
				
			}while( input < 0 || input > board->cols-1 || !validMove(board, input) );
			
			makeMove(board,input);// Make it so!
		}
		else
		{
			printf("Computer playing.\n");
			makeMove(board, getReasonedMove(board));// Make it so!
		}

		toString(board);
	}
	
	if(winnerIs(board) == PLAYER_ONE)
		printf("Player 1 is the winner !!!\n\n");
	else
		printf("Player 2 is the winner !!!\n\n");
		
	deleteboard(board);
	
	return 0;
}