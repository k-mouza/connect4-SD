#include <stdio.h>
#include <stdlib.h>

#include "../include/input.h"

void user_input(int *player2, int *difficulty, int *first_pl)
{
	char input, temp, temp1;
	
	printf("\nEnter the type of Player 2 ('1' or '2'):\n\t1. Computer\n\t2. Human\n");
	do
	{
		input = getchar();
		temp = getchar();

		*player2 = atoi(&input);
		
		// check if the user pressed a number and then <enter>
		if ( (*player2 != 1 && *player2 != 2) || temp != '\n' )
		{
			printf("Enter '1' or '2'\n");
			if (temp != '\n')
				while((temp1 = getchar()) != '\n' && temp1 != EOF);
		}
			
	}while( (*player2 != 1 && *player2 != 2) || temp != '\n' );


	if (*player2 == 1)
	{
		printf("Choose computer difficulty ('1', '2' or '3'):\n\t1. Easy\n\t2. Normal\n\t3. Hard\n");
		do
		{
			input = getchar();
			temp = getchar();

			*difficulty = atoi(&input);

			// check if the user pressed a number and then <enter>
			if ( (*difficulty != 1 && *difficulty != 2 && *difficulty != 3) || temp != '\n' )
			{
				printf("Enter '1', '2' or '3'\n");
				if (temp != '\n')
					while((temp1 = getchar()) != '\n' && temp1 != EOF);
			}
			
		}while( (*difficulty != 1 && *difficulty != 2 && *difficulty != 3) || temp != '\n' );
	}

	
	printf("Type '1' if you want to play first or '2' if you want Player 2 to play first:\n");
	do
	{
		input = getchar();
		temp = getchar();

		*first_pl = atoi(&input);
		
		// check if the user pressed a number and then <enter>
		if ( (*first_pl != 1 && *first_pl != 2) || temp != '\n' )
		{
			printf("Enter '1' or '2'\n");
			if (temp != '\n')
				while((temp1 = getchar()) != '\n' && temp1 != EOF);
		}
		
	}while( (*first_pl != 1 && *first_pl != 2) || temp != '\n' );
}