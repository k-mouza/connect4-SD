#include <stdio.h>
#include <stdlib.h>

#include "../include/gameplay.h"
#include "../include/ai_player.h"

static int DIFFICULTY;
static int QUARTETS;	// total winning quartets in the board

point_type* newPoint(int a, int b)
{
	point_type *point = (point_type*)malloc(sizeof(point_type));
	if(!point)
	{
		printf("Not enough memory. Exiting...\n");
		exit(-1);
	}
	point->x = a;
	point->y = b;
	point->state = EMPTY; // no starting player
	return point;
}


void deletepoint(point_type *point)
{
	free(point);
}


void setState(point_type *point, int player)
{
	point->state = player;
}


int getState(point_type *point)
{
	return point->state;
}


int getPlayer(board_type *board)
{
	return board->curr_pl;
}


int getDifficulty(void)
{
	return DIFFICULTY;
}


int getQuartets(void)
{
	return QUARTETS;
}


static point_type*** generateWinLines(point_type ***grid, int cols, int rows)
{
	int i, y, x, t;
	int count = 0;
	
	point_type ***lines = (point_type ***)malloc(getQuartets() * sizeof(point_type **));
	if(!lines)
	{
		printf("Not enough memory. Exiting...\n");
		exit(-1);
	}
/*	for(i=0; i<getQuartets(); i++)
	{
		lines[i] = (point_type **)malloc(4 * sizeof(point_type *));
		if(!lines[i])
		{
			printf("Not enough memory. Exiting...\n");
			exit(-1);
		}
	}
*/
	
	// compute vertical winning lines
	for(y=0; y<rows; y++)
	{
		for(x=0; x<cols-3; x++)
		{
			point_type **temp = (point_type **)malloc(4 * sizeof(point_type *));
			if(!temp)
			{
				printf("Not enough memory. Exiting...\n");
				exit(-1);
			}
			
			for(i=x; i<x+4; i++)
			{
				temp[i-x] = grid[i][y];
			}
			lines[count] = temp;
			count++;
		}
	}

	// compute horizontal winning lines
	for(x=0; x<cols; x++)
	{
		for(y=0; y<rows-3; y++)
		{
			point_type **temp = (point_type **)malloc(4 * sizeof(point_type *));
			if(!temp)
			{
				printf("Not enough memory. Exiting...\n");
				exit(-1);
			}
			
			for(i=y; i<y+4; i++)
			{
				temp[i-y] = grid[x][i];
			}
			lines[count] = temp;
			count++;
		}
	}

	// compute diagonal (bottom left to top right) winning lines
	for(x=0; x<cols-3; x++)
	{
		for(y=0; y<rows-3; y++)
		{
			point_type **temp = (point_type **)malloc(4 * sizeof(point_type *));
			if(!temp)
			{
				printf("Not enough memory. Exiting...\n");
				exit(-1);
			}
			
			for(t=x,i=y; t<x+4 && i<y+4; t++,i++)
			{
				temp[i-y] = grid[t][i];
			}
			lines[count] = temp;
			count++;
		}
	}
	
	// compute diagonal (top left to bottom right) winning lines
	for(x=0; x<cols-3; x++)
	{
		for(y=rows-1; y>2; y--)
		{
			point_type **temp = (point_type **)malloc(4 * sizeof(point_type *));
			if(!temp)
			{
				printf("Not enough memory. Exiting...\n");
				exit(-1);
			}
			
			for(t=x,i=y; t<x+4 && i>-1; t++,i--)
			{
				temp[t-x] = grid[t][i];
			}
			lines[count] = temp;
			count++;
		}
	}
	
	return lines;
}


board_type* createBoard(int a, int b, int first_pl)
{
	int x, y;

	if( a<4 || b<4 )
	{
		printf("Board must at least be 4x4. Exiting...\n");
		exit(-1);
	}

	board_type *board = (board_type*)malloc(sizeof(board_type));
	if(!board)
	{
		printf("Not enough memory. Exiting...\n");
		exit(-1);
	}
	
	board->cols = a;
	board->rows = b;
	board->moves_made = -1;
	board->curr_pl = first_pl;
	board->heights = (int *)malloc(board->cols * sizeof(int));
	board->grid = (point_type ***)malloc(board->cols * sizeof(point_type **));
	board->moves = (int *)malloc(board->cols * board->rows * sizeof(int));
	
	if(!board->heights || !board->grid || !board->moves)
	{
		printf("Not enough memory. Exiting...\n");
		exit(-1);
	}

	// allocate the grid points and set the heights of each column to 0
	for(x=0; x<board->cols; x++)
	{
		board->grid[x] =(point_type **)malloc(board->rows * sizeof(point_type *));
		if(!board->grid[x])
		{
			printf("Not enough memory. Exiting...\n");
			exit(-1);
		}
		
		board->heights[x] = 0;

		for(y=0; y<board->rows; y++)
		{
			board->grid[x][y] = newPoint(x,y);
		}
	}
	
	QUARTETS = board->rows*(board->cols-3) + board->cols*(board->rows-3) + 2*(board->cols-3)*(board->rows-3);
	
	board->win_lines = generateWinLines(board->grid, board->cols, board->rows);
	
	return board;
}


void deleteboard(board_type* board)
{
	int i, x, y;
	
	for(i=0; i<getQuartets(); i++)
		free(board->win_lines[i]);
	free(board->win_lines);
	
	for(x=0; x<board->cols; x++)
	{
		for(y=0; y<board->rows; y++)
		{
			deletepoint(board->grid[x][y]);
		}
		free(board->grid[x]);
	}
	free(board->grid);
	
	free(board->heights);
	free(board->moves);
	free(board);
}


int validMove(board_type *board, int column)
{
	return (board->heights[column] < board->rows);
}


void makeMove(board_type *board, int column)
{
	// the row of the grid is determined by the height of the given column
	int row = board->heights[column];
	
	// set the state of the corresponding point to the current player
	setState(board->grid[column][row], board->curr_pl);

	board->heights[column]++;					// increase the column height
	board->moves_made++;						// increase the total moves made
	board->moves[board->moves_made] = column;	// store the column played
	board->curr_pl = -board->curr_pl;			// change the current player
}

void human_play(board_type *board, int pl_id)
{
	int input;
	
	if (pl_id == PLAYER_ONE)
		pl_id = 1;
	else
		pl_id = 2;
	
	do
	{
		printf("Player %d insert column number (1-7): ", pl_id);
		scanf("%d", &input);
		printf("\n");
		
		if(input < 1 || input > board->cols)
			printf("Provide a column number between 1 and %d\n", board->cols);
		else if(!validMove(board, input-1))
			printf("Column is full. Choose another one.\n");
		
	}while( input < 1 || input > board->cols || !validMove(board, input-1) );
	
	makeMove(board, input-1);
}

void com_play(board_type *board)
{
	printf("Computer playing.\n\n");
	
	if (getDifficulty() == DIFF_EASY)
		makeMove(board, getRandomPlayerMove(board));
	else
		makeMove(board, getReasonedMove(board));
}

void undoMove(board_type *board)
{
	// find the last played column from the moves[] array
	int column = board->moves[board->moves_made];
	// the row of the grid is determined by the height of the above column
	int row = board->heights[column]-1;
	
	setState(board->grid[column][row], EMPTY); // set the state of the point to EMPTY
	
	board->heights[column]--;			// decrease the column height
	board->moves_made--;				// decrase the total moves made
	board->curr_pl = -board->curr_pl;	// change current player
}


int validMovesLeft(board_type *board)
{
	return board->moves_made < ((board->cols * board->rows)-1);
}


int getScore(point_type **win_line)
{
	int playerone=0;
	int playertwo=0;
	int i;
	
	for(i=0; i<4; i++)
	{
		if(getState(win_line[i]) == PLAYER_ONE)
			playerone++;
		else if(getState(win_line[i]) == PLAYER_TWO)
			playertwo++;
	}
	
	if( (playerone + playertwo > 0) && (!(playerone > 0 && playertwo > 0)) )
		return (playerone != 0) ? playerone : -playertwo;
	else
		return 0;
}


int winnerIs(board_type *board)
{
	int i;
	
	for(i=0; i<getQuartets(); i++)
	{
		// a score equal to 4 or -4 means that PLAYER_ONE or PLAYER_TWO, accordingly,
		// has completed one of the winning quartets, so he is the winner
		if(getScore(board->win_lines[i]) == 4)
			return PLAYER_ONE;
		else if(getScore(board->win_lines[i]) == -4)
			return PLAYER_TWO;
	}
	
	return 0;
}


void parse_input(int *player2, int diffic, int *first_pl)
{
	switch (*player2)
	{
		case 1:
			*player2 = COMPUTER;
			break;
		case 2:
			*player2 = HUMAN;
			break;
	}
	
	switch (diffic)
	{
		case 1:
			DIFFICULTY = DIFF_EASY;
			break;
		case 2:
			DIFFICULTY = DIFF_NORM;
			break;
		case 3:
			DIFFICULTY = DIFF_HARD;
			break;
	}
	
	switch (*first_pl)
	{
		case 1:
			*first_pl = PLAYER_ONE;
			break;
		case 2:
			*first_pl = PLAYER_TWO;
			break;
	}
}

