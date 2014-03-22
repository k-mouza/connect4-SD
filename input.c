#include <stdio.h>
#include <stdlib.h>

#include "input.h"

void user_input(int *player2, int *difficulty, int *first_pl)
{
	printf("\nEnter the type of Player 2 ('1' or '2'):\n\t1. Computer\n\t2. Human\n");
	do
	{
		scanf("%d", player2);
		if (*player2 != 1 && *player2 != 2)
			printf("Enter '1' or '2'\n");
			
	}while( *player2 != 1 && *player2 != 2 );


	if (*player2 == 1)
	{
		printf("Choose computer difficulty ('1', '2' or '3'):\n\t1. Easy\n\t2. Normal\n\t3. Hard\n");
		do
		{
			scanf("%d", difficulty);
			if (*difficulty != 1 && *difficulty != 2 && *difficulty != 3)
				printf("Enter '1', '2' or '3'\n");
			
		}while( *difficulty != 1 && *difficulty != 2 && *difficulty != 3 );
	}

	
	printf("Type '1' if you want to play first or '2' if you want Player 2 to play first:\n");
	do
	{
		scanf("%d", first_pl);
		if (*first_pl != 1 && *first_pl != 2)
			printf("Enter '1' or '2'\n");
		
	}while( *first_pl != 1 && *first_pl != 2 );
}