#include <stdio.h>
#include <stdlib.h>

#include "output.h"

void toString(board_type *board)
{
	int y, x;
	
	for(y=board->rows-1; y>=0; y--)
	{
		for(x=0; x<board->cols; x++)
		{
			if(getState(board->grid[x][y]) == EMPTY)
				printf("-");
			else if(getState(board->grid[x][y])==PLAYER_ONE)
				printf("O");
			else
				printf("X");
		}
		printf("\n");
	}
	printf("\n");
}