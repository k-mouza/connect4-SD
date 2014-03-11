#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <stdio.h>

#include "../ai_player.h"
#include "../output.h"
#include "../gameplay.h"


double m_Tolerance = 1e-10;


/*
 * Tests for functions of file gameplay.c
 */

void test_newPoint(void)
{
	point_type *test_point = newPoint(1,1);
		
	CU_ASSERT_EQUAL(test_point->x, 1);
	CU_ASSERT_EQUAL(test_point->y, 1);
	CU_ASSERT_EQUAL(test_point->state, EMPTY);
	
	deletepoint(test_point);
}

void test_setState(void)
{
	point_type point = {1,1,0};
	
	setState(&point, 1);
	
	CU_ASSERT_EQUAL(point.state, 1);
}

void test_getState(void)
{
	point_type point = {1,1,0};
	int expected_state;
	
	expected_state = getState(&point);
	
	CU_ASSERT_EQUAL(expected_state, 0)
}

void test_getPlayer(void)
{
	board_type board;
	int player;
	
	board.curr_pl = 1;
	
	player = getPlayer(&board);
	
	CU_ASSERT_EQUAL(1, player);
}

void test_createBoard(void)
{
	int i;
	board_type *board = createBoard(4,5);
	
	CU_ASSERT_EQUAL(board->cols, 4);
	CU_ASSERT_EQUAL(board->rows, 5);
	CU_ASSERT_EQUAL(board->moves_made, -1);
	CU_ASSERT_EQUAL(board->curr_pl, 1);
	
	for(i=0; i<4; i++)
		CU_ASSERT_EQUAL(board->heights[i], 0);
	
	CU_ASSERT_PTR_NOT_NULL(board->win_lines);
	
	deleteboard(board);
}

void test_validMove(void)
{
	int ret, ret1;
	
	board_type *board = (board_type*)malloc(sizeof(board_type));
	if(!board)
	{
		printf("Not enough memory. Exiting...\n");
		exit(-1);
	}
	board->cols = 7;
	board->rows = 6;
	board->heights = (int *)malloc(board->cols * sizeof(int));
	if(!board->heights)
	{
		printf("Not enough memory. Exiting...\n");
		exit(-1);
	}

	board->heights[3] = 4;
	ret = validMove(board, 3);

	board->heights[4] = 6;
	ret1 = validMove(board, 4);
	
	CU_ASSERT_EQUAL(ret, 1);
	CU_ASSERT_EQUAL(ret1, 0);
	
	free(board->heights);
	free(board);
}

void test_makeMove(void)
{
	int state;
	board_type *board = createBoard(7,6);
	
	makeMove(board, 3);
	
	state = getState(board->grid[3][0]);
	CU_ASSERT_EQUAL(state, 1);
	CU_ASSERT_EQUAL(board->heights[3], 1);
	CU_ASSERT_EQUAL(board->moves_made, 0);
	CU_ASSERT_EQUAL(board->moves[0], 3);
	CU_ASSERT_EQUAL(board->curr_pl, -1);
}

void test_undoMove(void)
{
	int state;
	board_type *board = createBoard(7,6);
	makeMove(board, 3);
	
	undoMove(board);
	
	state = getState(board->grid[3][0]);
	CU_ASSERT_EQUAL(state, 0);
	CU_ASSERT_EQUAL(board->heights[3], 0);
	CU_ASSERT_EQUAL(board->moves_made, -1);
	CU_ASSERT_EQUAL(board->curr_pl, 1);
}

void test_validMovesLeft(void)
{
	int ret, ret1;
	board_type *board = createBoard(7,6);
	
	board->moves_made = 5;
	ret = validMovesLeft(board);
	
	board->moves_made = 41;
	ret1 = validMovesLeft(board);
	
	CU_ASSERT_EQUAL(ret, 1);
	CU_ASSERT_EQUAL(ret1, 0);
}

void test_getScore(void)
{
	int i, ret, ret1, ret2;
	point_type **line = (point_type **)malloc(4 * sizeof(point_type *));
	if(!line)
	{
		printf("Not enough memory. Exiting...\n");
		exit(-1);
	}
	for(i=0; i<4; i++)
		line[i] = newPoint(0, i);
	
	line[0]->state = PLAYER_ONE;
	line[1]->state = PLAYER_ONE;
	line[2]->state = PLAYER_ONE;
	line[3]->state = EMPTY;
	ret = getScore(line);
	
	line[0]->state = PLAYER_TWO;
	line[1]->state = EMPTY;
	line[2]->state = PLAYER_TWO;
	line[3]->state = EMPTY;
	ret1 = getScore(line);
	
	line[0]->state = PLAYER_ONE;
	line[1]->state = PLAYER_ONE;
	line[2]->state = PLAYER_TWO;
	line[3]->state = EMPTY;
	ret2 = getScore(line);
	
	CU_ASSERT_EQUAL(ret, 3);
	CU_ASSERT_EQUAL(ret1, -2);
	CU_ASSERT_EQUAL(ret2, 0);
	
	for(i=0; i<4; i++)
		free(line[i]);
	free(line);
}

void test_winnerIs(void)
{
	int ret, ret1, ret2;
	board_type *board = createBoard(7,6);
	
	board->win_lines[3][0]->state = PLAYER_ONE;
	board->win_lines[3][1]->state = PLAYER_ONE;
	board->win_lines[3][2]->state = PLAYER_ONE;
	board->win_lines[3][3]->state = PLAYER_ONE;
	ret = winnerIs(board);
	
	board->win_lines[2][0]->state = PLAYER_TWO;
	board->win_lines[2][1]->state = PLAYER_TWO;
	board->win_lines[2][2]->state = PLAYER_TWO;
	board->win_lines[2][3]->state = PLAYER_TWO;
	ret1 = winnerIs(board);
	
	board->win_lines[1][0]->state = PLAYER_TWO;
	board->win_lines[1][1]->state = PLAYER_ONE;
	board->win_lines[1][2]->state = EMPTY;
	board->win_lines[1][3]->state = PLAYER_ONE;
	ret2 = winnerIs(board);
	
	CU_ASSERT_EQUAL(ret, PLAYER_ONE);
	CU_ASSERT_EQUAL(ret1, PLAYER_TWO);
	CU_ASSERT_EQUAL(ret2, 0);
	
	deleteboard(board);
}

/*
 * Test(s) for functions of file ai_player.c
 */

void test_getRandomPlayerMove(void)
{
	int ret, expected;
	board_type *board = createBoard(7,6);
	
	srand(8);
	ret = getRandomPlayerMove(board);
	
	srand(8);
	expected = rand() % (board->cols-1);
	CU_ASSERT_EQUAL(ret, expected);
	
	deleteboard(board);
}

void test_getStrength(void)
{
	int ret, ret1;
	board_type *board = createBoard(7,6);
	
	ret = getStrength(board);
	
	board->curr_pl = -board->curr_pl;
	ret1 = getStrength(board);
	
	CU_ASSERT_EQUAL(ret, 16);
	CU_ASSERT_EQUAL(ret1, -16);
}


int main()
{
	CU_pSuite gameplay_pSuite = NULL;
	CU_pSuite ai_player_pSuite = NULL;

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	/* add suites to the registry */
	gameplay_pSuite = CU_add_suite("Gameplay Tests Suite", NULL, NULL);
	if (NULL == gameplay_pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	ai_player_pSuite = CU_add_suite("AI player Tests Suite", NULL, NULL);
	if (NULL == ai_player_pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	

	/* add the tests to the appropriate suites */
	/* NOTE - ORDER IS IMPORTANT */
	if ( (NULL == CU_add_test(gameplay_pSuite, "Testing newPoint correctness", test_newPoint)) ||
		 (NULL == CU_add_test(gameplay_pSuite, "Testing setState correctness", test_setState)) ||
		 (NULL == CU_add_test(gameplay_pSuite, "Testing getState correctness", test_getState)) ||
		 (NULL == CU_add_test(gameplay_pSuite, "Testing getPlayer correctness", test_getPlayer)) ||
		 (NULL == CU_add_test(gameplay_pSuite, "Testing createBoard correctness", test_createBoard)) ||
		 (NULL == CU_add_test(gameplay_pSuite, "Testing validMove correctness", test_validMove)) ||
		 (NULL == CU_add_test(gameplay_pSuite, "Testing makeMove correctness", test_makeMove)) ||
		 (NULL == CU_add_test(gameplay_pSuite, "Testing undoMove correctness", test_undoMove)) ||
		 (NULL == CU_add_test(gameplay_pSuite, "Testing validMovesLeft correctness", test_validMovesLeft)) ||
		 (NULL == CU_add_test(gameplay_pSuite, "Testing getScore correctness", test_getScore)) ||
		 (NULL == CU_add_test(gameplay_pSuite, "Testing winnerIs correctness", test_winnerIs)) ||
		 (NULL == CU_add_test(ai_player_pSuite, "Testing getRandomPlayerMove correctness", test_getRandomPlayerMove)) ||
		 (NULL == CU_add_test(ai_player_pSuite, "Testing getStrength correctness", test_getStrength)) )
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE); 
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
