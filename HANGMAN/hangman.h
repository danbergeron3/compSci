#ifndef HANGMAN_H
#define HANGMAN_H

#include "my_string.h"
#include "generic_vector.h"
#include "avl_tree.h"
#include "generic.h"
#include "status.h"

//returns an array 
GENERIC_VECTOR* hangman_set_up(GENERIC_VECTOR* hVector, int size);

//pre: takes a valid item handle, a valid vector, and the valid size
//Status fill_vector_to_size(GENERIC_VECTOR hVector, IT);

void display_key(MY_STRING current_word_family);

//runs one play through of the game and returns a continuation value
int hangman_game_loop(GENERIC_VECTOR hVector[]);

#endif 


