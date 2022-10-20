#include "hangman.h"
#include "ctype.h"
void clear_keyboard_buffer(void);
void check_word_family(MY_STRING current_word_family);

GENERIC_VECTOR *hangman_set_up(GENERIC_VECTOR *array_hVector, int size)
{
	printf("Loading...\n");

	FILE *fp;
	int i;
	 
	AVL_TREE tree;
	fp = fopen("dictionary.txt", "r");
	ITEM hItem = my_string_init_default();

	for (i = 0; i < size; i++)
	{
		array_hVector[i] = generic_vector_init_default(my_string_assignment, my_string_destroy);
	}

	while (my_string_extraction(hItem, fp))
	{
		generic_vector_push_back(array_hVector[my_string_get_size(hItem)], hItem);
	}

	my_string_destroy(&hItem);
	fclose(fp);

	return *array_hVector;
}

int hangman_game_loop(GENERIC_VECTOR words_by_length[])
{
	int noc;
	int word_length;
	int guesses_remaining;
	int guess_count = 0;
	int vecSize = 0;
	int i;
	char c;
	AVL_TREE largest_node;
	GENERIC_VECTOR current_words = NULL ;
	MY_STRING current_word_family = NULL;
	MY_STRING new_key = NULL;
	Status status;
	char guessed_chars[90];


	while (1)
	{
		printf("Please pick a valid word length to play with: ");
		noc = scanf("%d", &word_length);
		clear_keyboard_buffer();

		if (noc == 1 && word_length > 0 && word_length < 30 && generic_vector_get_size(words_by_length[word_length])) {
			break;
		}
	}
	
	current_words = generic_vector_make_clone(words_by_length[word_length]);
	if(current_words == NULL)
	{
		return -3;
	}
	current_word_family = my_string_init_default();
	if (current_word_family == NULL) {
		return -4;
	}
	for (i = 0; i < word_length; i++)
	{
		if (my_string_push_back(current_word_family, '-') == FAILURE) {
			return -7;
		}
	}

	//guess loop
	while(1)
	{
		printf("How many guesses would you like: ");
		noc = scanf("%d", &guesses_remaining);
		clear_keyboard_buffer();
                if(noc == 1 && guesses_remaining > 0)
		{
			break;
		}
	}
	
	 int hints;
         while(1)
	{       
         	char response;
                printf("Do you want hints y/n: ");
                noc = scanf(" %c", &response);
                response = tolower(response);
		if(noc == 1 && (response == 'y' || response == 'n'))
		{
			switch(response){
				case 'y' :
				   hints = 1;
				   break;
				default:
			       	   hints = 0;
				   break; 
			}		
			break;
		}
	 }


	for(i = 0; i < 90; i++)
	{
		guessed_chars[i] = '0';
	}
	
	//main game loop
	while (guesses_remaining != 0)
	{		
		
		printf("You have %d guesses left!\n", guesses_remaining);
		printf("Used letters: %.*s\n", guess_count, guessed_chars);
		
		//display chosen word
		display_key(current_word_family);
		
		//validation loop
		while(1)
		{
			printf("Please enter your guess: ");
			noc = scanf(" %c", &c);
			clear_keyboard_buffer();
			c = tolower(c);
			i = 0;
			while(guessed_chars[i] != '\0')
			{
				if(guessed_chars[i] == c)
				{
					noc = -1;
				}
				i++;
			}
			if(noc == 1 && isalpha(c))
			{
				break;
			}
		}
		
		AVL_TREE key_closet = avl_tree_init_default();
		for (i = 0; i < generic_vector_get_size(current_words); i++)
		{
			new_key = my_string_init_default();
			MY_STRING word = *generic_vector_at(current_words, i);

			//gets new value 
			if (get_word_key_value(current_word_family, new_key, word, c) == FAILURE)
			{
				return -5;
			} 
			
			//fill key closet
			if (avl_tree_insert(&key_closet, new_key, word, hints) == FAILURE)
			{
				printf("avl_tree_insert failed\n");
				return -6;
			}
		}

		//finds largest vector in tree using key values then destroys tree once vec is found
		largest_node = avl_get_largest_node(key_closet);
		generic_vector_destroy(&current_words);	
		avl_get_key_take_value(largest_node, &current_word_family, &current_words);
		avl_tree_destroy(&key_closet);

		//handles guess count
		for (i = 0; i < my_string_get_size(current_word_family); i++)
		{
			if (*my_string_at(current_word_family, i) == c)
			{
				guesses_remaining++;
				break;
			}
		}
		guessed_chars[guess_count++] = c;
		guesses_remaining--;
		
		int flag = 0;
		for(i = 0; i < my_string_get_size(current_word_family); i++)
		{
			if(*(my_string_at(current_word_family, i))== '-')
			{
				flag = 1;
			        break;	
			}
		}
		if(flag == 0)
		{
			printf("YOU WON!\n");
			printf("The word was ");
			display_key(*generic_vector_at(current_words,0));
			break;
		}
		
		if(guesses_remaining == 0)
		{
			printf("You are out of choices!\n");
			printf("The word was ");
                        display_key(*generic_vector_at(current_words,rand() % generic_vector_get_size(current_words)));
			printf("GAME OVER!\n");
			break;
		}
		if(hints)
		{
			printf("choices left: %d\n", generic_vector_get_size(current_words));
		}
	}
		

	my_string_destroy(&current_word_family);
	generic_vector_destroy(&current_words);
	return 1;
}

//will display the 
void display_key(MY_STRING current_word_family)
{
	//int i = my_string_get_size(current_word_family);

	printf("%s\n", my_string_c_str(current_word_family));
}


void clear_keyboard_buffer(void)
{
	char c;
	scanf("%c", &c);
	while (c != '\n')
	{
		scanf("%c", &c);
	}
}
