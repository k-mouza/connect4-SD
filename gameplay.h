#ifndef __GAME_H
#define __GAME_H

#include <stdio.h>
#include <stdlib.h>

#define QUARTETS 	69

#define PLAYER_ONE	1
#define PLAYER_TWO	-1
#define EMPTY	 	0

#define COMPUTER	1
#define HUMAN		2

#define DIFF_EASY	1
#define DIFF_NORM	2
#define DIFF_HARD	3


typedef struct point point_type;
struct point
{
	int x, y, state;
};

typedef struct board board_type;
struct board
{
	point_type ***grid;
	int *heights;

	int cols;
	int rows;

	int *moves;
	int moves_made;

	int curr_pl;
	point_type ***win_lines;
};

point_type * newPoint(int a, int b);

void deletepoint(point_type *point);

void setState(point_type *point, int player);

int getState(point_type *point);

int getPlayer(board_type *board);

static point_type*** generateWinLines(point_type ***grid, int cols, int rows);

board_type * createBoard(int a, int b, int first_pl);

void deleteboard(board_type* board);

int validMove(board_type *board, int column);

void makeMove(board_type * board, int column);

void human_play(board_type *board, int pl_id);

void com_play(board_type *board);

void undoMove(board_type *board);

int validMovesLeft(board_type *board);

int getScore(point_type **points);

int winnerIs(board_type *board);

int getDifficulty(void);

void parse_input(int *player2, int difficulty, int *first_pl);

#endif