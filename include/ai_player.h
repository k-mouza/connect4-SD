#ifndef __AI_H
#define __AI_H

#include "gameplay.h"

/*
 * Returns a randomly selected, valid, column number for the AI to play
 */
int getRandomPlayerMove(board_type *board);

/*
 * Returns the strength of a move according to the values 
 * of all the winning lines of the board, that this move generates
 */
int getStrength(board_type *board);

/*
 * Min-Max AI algorithm that tests the strenght of all the possible moves
 * on the given board.
 */
static int minValue(board_type *board, int ply);
static int maxValue_hard(board_type *board, int ply);
static int maxValue_norm(board_type *board, int ply);

/*
 * Returns a valid column number, based on the MIN-MAX
 * algorithm, for the AI to play
 */
int getReasonedMove(board_type *board);


#endif