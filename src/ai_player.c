#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/ai_player.h"

int getRandomPlayerMove(board_type *board)
{
	// Replaced 7 with columns in whole function
	int ret = -1;
	int columns = board->cols;
	int possible[columns];
	int i;
	int rand_col; 	// random column number between 0 and 6
	
	// check each column to see if it has space for another move
	for(i=0; i<columns; i++)
	{
		if( validMove(board, i) )
			possible[i] = 1;
		else
			possible[i] = 0;
	}

	/*
	 * Generate a random number between 0 and 6.
	 * If the column, that this number represents, is eligible for a move, return the number.
	 */
	while(ret == -1)
	{
		rand_col = rand() % (columns-1);
		if(possible[rand_col] == 1)
			ret = rand_col;
	}
	
	return ret;
}


int getStrength(board_type *board)
{
	int sum=0;
	int weights[5] = {0,1,10,50,600};
	int i;
	int score;
	
	/*
	 * The last element of the weights[] array is used when a player has 
	 * completed a winning line, which gives an extra weight (600) to the total
	 * move strength. If the difficulty is HARD then add even more weight (2600).
	 */
	if (getDifficulty() == DIFF_HARD)
		weights[4] = 2600;
		
	for(i=0; i<getQuartets(); i++)
	{
		score = getScore(board->win_lines[i]);
		sum += (score > 0) ? weights[score] : -weights[-score];
	}
	
	return sum + ((board->curr_pl == PLAYER_ONE) ? 16 : -16);
}


// the MAX function of the MIN-MAX AI algorithm
static int minValue(board_type *board, int ply)
{
	// Replaced 7 with columns in whole function
	int columns = board->cols;
	int moves[columns];
	int lowest = 0;
	int i;
	
	for(i=0; i<columns; i++)
	{
		moves[i] = INT_MAX;
		if(validMove(board, i))
		{
			makeMove(board, i);
			
			if( (winnerIs(board) == 0) && (ply > 0) )
			{
				if (getDifficulty() == DIFF_HARD)
					moves[i] = maxValue_hard(board, ply-1);
				else
					moves[i] = maxValue_norm(board, ply-1);
			}
			else 
				moves[i] = -getStrength(board);
			
			if(moves[i] < moves[lowest])
				lowest = i;
			
			undoMove(board);
		}
	}
	return moves[lowest];
}


/*
 * The MAX function of the MIN-MAX AI algorithm, for the HARD difficulty.
 * The comments indicate the changes to the algorithm.
 * Basically, it now represents the MAX player (initialises the move with
 * INT_MIN and then checks for a grater one), whereas the initial function
 * did the opposite thing, which made it the same as the MIN function.
 */
static int maxValue_hard(board_type *board, int ply)
{
	// Replaced 7 with columns in whole function
	int columns = board->cols;
	int moves[columns];
	int highest = 0;
	int i;
		
	for(i=0; i<columns; i++)
	{
		moves[i] = INT_MIN;		// changed this from INT_MAX to INT_MIN
		if(validMove(board, i))
		{
			makeMove(board, i);
			
			if( (winnerIs(board) == 0) && (ply > 0) )
				moves[i] = minValue(board, ply-1);
			else 
				moves[i] = -getStrength(board);
			
			if(moves[i] >= moves[highest])	// changed the comparison from "<" to ">="
				highest = i;
			
			undoMove(board);
		}
	}
	return moves[highest];
}

/*
 * The max function of the MIN-MAX AI algorithm, for the NORMAL difficulty.
 * It is the same as the initial one.
 */
static int maxValue_norm(board_type *board, int ply)
{
	// Replaced 7 with columns in whole function
	int columns = board->cols;
	int moves[columns];
	int highest = 0;
	int i;
		
	for(i=0; i<columns; i++)
	{
		moves[i] = INT_MAX;
		if(validMove(board, i))
		{
			makeMove(board, i);
			
			if( (winnerIs(board) == 0) && (ply > 0) )
				moves[i] = minValue(board, ply-1);
			else 
				moves[i] = -getStrength(board);
			
			if(moves[i] < moves[highest])
				highest = i;
			
			undoMove(board);
		}
	}
	return moves[highest];
}

/* 
 * This is basically the start of the MIN-MAX algorithm and
 * it represents the MAX player
 */
int getReasonedMove(board_type *board)
{
	// Replaced 7 with columns in whole function
	int columns = board->cols;
	int moves[columns];
	int highest = 0;
	int i;
		
	for(i=0; i<columns; i++)
	{
		moves[i] = INT_MIN;
		if(validMove(board, i))
		{
			makeMove(board, i);
			moves[i] = minValue(board, 4);
			
			if(moves[i] >= moves[highest])
				highest = i;
			
			undoMove(board);
		} 
	}
	return highest;
}
