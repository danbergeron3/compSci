#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"
#include "hangman.h"

void clear_keyboared_buffer(void);

int main(int argc, char* argv[])
{
	GENERIC_VECTOR Array_hVectors[30];
	unsigned int size = 30;
	int game = 1;
	*Array_hVectors = hangman_set_up(Array_hVectors, size);
	char c;
	int noc;

	for (int i = 0; i < size; i++)
	{
		printf("word size: %d size of vector: %d\n",i, generic_vector_get_size(Array_hVectors[i]));
	}

	while (game == 1)
	{
		game = hangman_game_loop(Array_hVectors);
		if(game != 1 && game != 0)
		{
			printf("CRITICAL ERROR: %d\n", game);
			exit(1);
		}

		do{
		
			printf("Would you like to play again? y/n: ");
			noc = scanf(" %c", &c);
			clear_keyboared_buffer();
		
		}while(noc == 1 && c != 'y' && c != 'Y' && c != 'n' && c != 'N');
		if(noc != 1)
		{
			break;
		}
		if(c == 'n' || c == 'N')
		{
			game = 0;
		}
	}

	for (int i = 0; i < size; i++)
	{
		generic_vector_destroy(&(Array_hVectors[i]));
	}

	return 0;
}

void clear_keyboared_buffer(void)
{
	char c;
	scanf("%c", &c);
	while (c != '\n')
	{
		scanf("%c", &c);
	}
}
