#include <stdio.h>
#include <stdlib.h>

#include "output.h"

void toString(board_type *board)
{
	int y, x;
	point_type *curr_point;
	
	for(y=board->rows-1; y>=0; y--)
	{
		for(x=0; x<board->cols; x++)
		{
			curr_point = board->grid[x][y];
			
			if(getState(curr_point) == EMPTY)
				printf("-");
			else if(getState(curr_point) == PLAYER_ONE)
				printf("O");
			else
				printf("X");
		}
		printf("\n");
	}
	printf("\n");
}