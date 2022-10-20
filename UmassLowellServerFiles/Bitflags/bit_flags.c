/*
* Author: Daniel Bergeron
* Date: 2/21/2022
* Effort: 9hrs
* Purpose: The purpose of this program is to create a bit flag object,
* whos characteristics allow the user to take and estimatied range of bits
* and manipulate the bits contained within that range if for some reason the estimated
* range is of the object will resize to fit more bits(resize n-bit). Changing the bits is
* helped by a dynamic array whose job it is to old each n-bit integer that contains the bits,
* if a user requests a bit outside the integer the arry will move to the next integer in it.
* Interface Proposal: I believe the interface would benifit from having a function that allows
* the user to remove bit segments from the array. The function would go to a selceted index that
* contains an integer and wipe it, it would have to move elements to avoid empty spaces, though
* if the data structure only removed bits from the back like a stack or implemented techiques
* from a queue this function could be very efficent, this function is importent beacuase the user
* can decide what bit segments are importent.
*/

#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"

typedef struct bit_flags Bit_flags;

struct bit_flags {
	int size;
	int capacity;
	unsigned *data;
};

int const BITS_PER_INTEGER = sizeof(unsigned) * 8;
int how_many_uints_for_bits(int bit_count);


//dont want user to have direct resize option
Status bit_flags_resize(BIT_FLAGS hBit_flags, int flag_position);

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
	//gets amount of bits program will run on 
	Bit_flags* pflag = (Bit_flags*)malloc(sizeof(Bit_flags));
	if (pflag == NULL)
	{
		return NULL;
	}

	int uint_count = how_many_uints_for_bits(number_of_bits); 
	pflag->data = (unsigned *)malloc(sizeof(unsigned) * uint_count);
	if (pflag->data == NULL)
	{
		free(pflag);
		return NULL;
	}

	pflag->size = 0;
	pflag->capacity = BITS_PER_INTEGER * uint_count;
	for (int i = 0; i < uint_count; i++)
	{
		pflag->data[i] = 0;
	}
	
	return pflag;
}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	//flag position offset by one since its an index
	Bit_flags* pflag = (Bit_flags*)hBit_flags;
	
	//resize if needed
	
	if (!bit_flags_resize(hBit_flags, flag_position))
	{
		return FAILURE;
	}
		
	if (flag_position >= pflag->size)
	{
		//ensures new size assigment
		pflag->size = flag_position + 1;
	}
	
	int uint_index = flag_position / BITS_PER_INTEGER;
	int bit_index = flag_position % BITS_PER_INTEGER;

	//uses position to create binary number to compare holder with, then adds a one to that location through or operation
	pflag->data[uint_index] = pflag->data[uint_index] | (1 << bit_index);
	
	return SUCCESS;

}

Status bit_flags_resize(BIT_FLAGS hBit_flags, int flag_position)
{
	unsigned* temp;
	Bit_flags* pflag = (Bit_flags*)hBit_flags;
	int i;
	

	if(flag_position >= pflag->capacity)
	{
		//gets new capacity based of the out of bounds position
		int new_uint_count = how_many_uints_for_bits(flag_position + 1);

		//increase current size by flag position since it is out of bounds
		temp = (unsigned*)malloc(sizeof(unsigned) * new_uint_count);
		if (temp == NULL)
		{
			printf("ERROR: FAILED TO ALLOCATE MEMORY\n");
			return FAILURE;
		}
		
		//will copy original elemts over then fill rest of array with 0
		//includes guard so origninal array doesent go out of bounds
		//fills empty/extra space with zeros
		int old_uint_count = how_many_uints_for_bits(pflag->capacity);
		
		for (i = 0; i < new_uint_count; i++)
		{
			if (i < old_uint_count)
			{
				temp[i] = pflag->data[i];
			}
			else
			{
				temp[i] = 0;
			}
		}

		//replace and resize operations 
		free(pflag->data);
		pflag->data = temp;
		pflag->capacity = new_uint_count * BITS_PER_INTEGER;
		pflag->size = flag_position + 1;
	}
	return SUCCESS;
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pFlag = (Bit_flags*)hBit_flags;

	if (!bit_flags_resize(hBit_flags, flag_position))
	{
		return FAILURE;
	}

	if(flag_position >= pFlag->size)
	{
		//ensures new size assigment
		pFlag->size = flag_position + 1;
	}
	
	//flips bits of numbers at index 
	//goes to positon and unsets 
	//then inverts again canceling out fromer operation and turning the added 1 from set flag to a zero
	
	int uint_index = flag_position / BITS_PER_INTEGER;
	int bit_index = flag_position % BITS_PER_INTEGER;

	pFlag->data[uint_index] = ~(pFlag->data[uint_index]);
	pFlag->data[uint_index] =  pFlag->data[uint_index] | (1 << bit_index);	
	pFlag->data[uint_index] = ~(pFlag->data[uint_index]);
	
	return SUCCESS;
}


int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pflag = (Bit_flags*)hBit_flags;
	
	if (flag_position >= pflag->size)
	{
		return -1;
	}

	int uint_index = flag_position / BITS_PER_INTEGER;
	int bit_index = flag_position % BITS_PER_INTEGER;

	//returns 1 if bits line up in and operation,else 0, then moves bits to ones spot and returns
	return ((pflag->data[uint_index] & (1 << bit_index)) >> bit_index);
}


int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
	Bit_flags* pflag = (Bit_flags*)hBit_flags;
	return pflag->size;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
	Bit_flags* pflag = (Bit_flags*)hBit_flags;
	return pflag->capacity;
}

//takes bits value and converts it to int
int how_many_uints_for_bits(int bit_count)
{
	return (bit_count + BITS_PER_INTEGER - 1) / BITS_PER_INTEGER;
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
	Bit_flags* pflag = (Bit_flags*)*phBit_flags;
	free(pflag->data);
	free(pflag);
	*phBit_flags = NULL;

}
