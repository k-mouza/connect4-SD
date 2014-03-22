#ifndef __GAME_H
#define __GAME_H

#include <stdio.h>
#include <stdlib.h>

#define QUARTETS 	69	// total winning quartets in a 7x6 grid

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

/*
 * Allocates and returns a point at coordinates (a,b)
 */
point_type * newPoint(int a, int b);

/*
 * Frees the allocated space of a point
 */
void deletepoint(point_type *point);

/*
 * Sets the state of a point to represent a player
 */
void setState(point_type *point, int player);

/*
 * Returns the state of the given point
 */
int getState(point_type *point);

/*
 * Returns the current player for the given board
 */
int getPlayer(board_type *board);

/*
 * Allocates and returns an array of all the possible winning quartets of points
 * of a given grid with given dimensions
 */
static point_type*** generateWinLines(point_type ***grid, int cols, int rows);

/*
 * Allocates, initializes and returns a board, with given dimensions
 * and the player that plays first
 */
board_type * createBoard(int a, int b, int first_pl);

/*
 * Frees an allocated board and its components
 */
void deleteboard(board_type* board);

/*
 * Returns 1 (true) if the given column has space for another move
 * or 0 (false) if it doesn't
 */
int validMove(board_type *board, int column);

/*
 * Places a token of the current player in the given column
 */
void makeMove(board_type *board, int column);

/*
 * It is the turn of a human player, whose id equals pl_id, to play
 */
void human_play(board_type *board, int pl_id);

/*
 * It is the turn of the computer to play
 */
void com_play(board_type *board);

/*
 * Undos the move of the last player
 * (removes the token from the last played column)
 */
void undoMove(board_type *board);

/*
 * Returns the number of left moves in the given board
 */
int validMovesLeft(board_type *board);

/*
 * Returns the score of the given winning line
 * 0 if the line contains tokens from both players
 * >0 if the line contains tokens only from player 1
 * <0 if the line contains tokens only from player 2
 */
int getScore(point_type **points);

/*
 * Returns the player that won (PLAYER_ONE or PLAYER_TWO)
 * or 0 if nobody won yet
 */
int winnerIs(board_type *board);

/*
 * Returns the difficulty that the user has set
 * (DIFF_EASY, DIFF_NORM or DIFF_HARD)
 */
int getDifficulty(void);

/*
 * Sets the variables player2, first_pl and the static int DIFFICULTY
 * according to user's input
 */
void parse_input(int *player2, int difficulty, int *first_pl);

#endif