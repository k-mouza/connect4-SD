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
	point_type expected = {1,1,0}, *test_point;
	
	test_point = newPoint(1,1);
	
	CU_ASSERT_EQUAL(test_point->x, expected.x);
	CU_ASSERT_EQUAL(test_point->y, expected.y);
	CU_ASSERT_EQUAL(test_point->state, expected.state);
	
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
	
	CU_ASSERT_EQUAL(0, expected_state)
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
	board_type *board = createBoard(7,6);
	
	CU_ASSERT_EQUAL(board->cols, 7);
	CU_ASSERT_EQUAL(board->rows, 6);
	CU_ASSERT_EQUAL(board->moves_made, -1);
	CU_ASSERT_EQUAL(board->curr_pl, 1);
	
	for(i=0; i<7; i++)
		CU_ASSERT_EQUAL(board->heights[i], 0);
	
	CU_ASSERT_PTR_NOT_NULL(board->win_lines);
	
	deleteboard(board);
}

void test_validMove(void)
{
	int ret, ret1;
	
	board_type *board = (board_type*)malloc(sizeof(board_type));
	board->cols = 7;
	board->rows = 6;
	board->heights = (int *)malloc(board->cols * sizeof(int));

	board->heights[3] = 4;
	ret = validMove(board, 3);

	board->heights[4] = 6;
	ret1 = validMove(board, 4);
	
	CU_ASSERT_EQUAL(ret, 1);
	CU_ASSERT_EQUAL(ret1, 0);
	
	free(board->heights);
	free(board);
}

/*
 * Test(s) for function insertHalos() in file ai_player.c
 */




int main()
{
	CU_pSuite gameplay_pSuite = NULL;
	CU_pSuite ai_player_pSuite = NULL;
	CU_pSuite output_pSuite = NULL;

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
	
	output_pSuite = CU_add_suite("Output Suite", NULL, NULL);
	if (NULL == output_pSuite) {
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
		 (NULL == CU_add_test(gameplay_pSuite, "Testing validMove correctness", test_validMove)) )
		 //(NULL == CU_add_test(ai_player_pSuite, "Testing  correctness", test_)) ||
		 //(NULL == CU_add_test(output_pSuite, "Testing  correctness", test_)) )
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
