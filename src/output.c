#include <stdio.h>
#include <stdlib.h>

#include "../include/output.h"

void toString(board_type *board)
{
	int y, x, i;
	point_type *curr_point;
	
	// print the column numbers above the board
	for(i=0; i<board->cols; i++)
		printf("%d ", i+1);
	printf("\n");
	
	// print the tokens of each player for the current state
	// of the board
	for(y=board->rows-1; y>=0; y--)
	{
		for(x=0; x<board->cols; x++)
		{
			curr_point = board->grid[x][y];
			
			if(getState(curr_point) == EMPTY)
				printf("_ ");
			else if(getState(curr_point) == PLAYER_ONE)
				printf("O ");
			else
				printf("X ");
		}
		printf("\n");
	}
	printf("\n");
}