#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "ai_player.h"

int getRandomPlayerMove(board_type *board)
{
	//Replaced 7 with columns in whole function
	int ret = -1;
	int columns = board->cols;
	int possible[columns];
	int i;
	int rand_col; //random column number between 0 and 6
	
	for(i=0; i<columns; i++)
	{
		if( validMove(board, i) )
			possible[i] = 1;
		else
			possible[i] = 0;
	}

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
	
	for(i=0; i<QUARTETS; i++)
	{
		score = getScore(board->cl[i]);
		sum += (score > 0) ? weights[score] : -weights[-score];
	}
	
	return sum + ((board->cp == PLAYER_ONE) ? 16 : -16);
}


// don't change this unless you understand it
int minValue(board_type *board, int ply)
{
	//Replaced 7 with columns in whole function
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
				moves[i] = maxValue(board, ply-1);
			else 
				moves[i] = -getStrength(board);
			
			if(moves[i] < moves[lowest])
				lowest = i;
			
			undoMove(board);
		}
	}
	return moves[lowest];
}


//careful with this
int maxValue(board_type *board, int ply)
{
	//Replaced 7 with columns in whole function
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
			
			if(moves[i] > moves[highest])
				highest = i;
			
			undoMove(board);
		}
	}
	return moves[highest];
}


// should return a number
int getReasonedMove(board_type *board)
{
	//Replaced 7 with columns in whole function
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
