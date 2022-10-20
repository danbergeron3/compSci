#include "bit_flags.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 2000000000

int main(int argc, char* argv[])
{
	BIT_FLAGS hBit = bit_flags_init_number_of_bits(30);
	int i;
	int val;

	if (hBit == NULL)
	{
		return 1;
	}
	bit_flags_set_flag(hBit, 0);
	bit_flags_set_flag(hBit, 2);
	bit_flags_set_flag(hBit, 3);
	bit_flags_set_flag(hBit, 1);
	bit_flags_set_flag(hBit, 4);
	bit_flags_set_flag(hBit, 5);
	bit_flags_set_flag(hBit, 6);
	bit_flags_set_flag(hBit, 7);
	bit_flags_set_flag(hBit, 8);
	bit_flags_set_flag(hBit, 9);
	bit_flags_set_flag(hBit, 10);
	bit_flags_set_flag(hBit, 11);
	bit_flags_set_flag(hBit, 30);
	bit_flags_set_flag(hBit, 31);
	
	bit_flags_set_flag(hBit, 39);
	
	bit_flags_set_flag(hBit, 64);
	bit_flags_set_flag(hBit, 65);
	//bit_flags_set_flag(hBit, 499);
	bit_flags_set_flag(hBit, 95);

	//bit_flags_set_flag(hBit, 200000000);
	val = bit_flags_get_capacity(hBit);
	for (i = 1; i <= val; i++)
	{

		printf("%d", bit_flags_check_flag(hBit, (i - 1)));
		if (i % 4 == 0)
		{
			printf(" ");
		}
		if (i % 32 == 0)
		{
			printf("\n");
		}
	}
	printf("\n\n\n\n");


	printf("size: %d Bits.\n", bit_flags_get_size(hBit));
	printf("Can hold up to %d Bits\n\n", bit_flags_get_capacity(hBit));

	bit_flags_unset_flag(hBit, 0);
	bit_flags_unset_flag(hBit, 2);
	bit_flags_unset_flag(hBit, 3);
	bit_flags_unset_flag(hBit, 1);
	bit_flags_unset_flag(hBit, 4);
	bit_flags_unset_flag(hBit, 91);
	bit_flags_unset_flag(hBit, 23);
	bit_flags_unset_flag(hBit, 499);
	bit_flags_unset_flag(hBit, 500);
	bit_flags_unset_flag(hBit, 510);
	val = bit_flags_get_capacity(hBit);
	for (i = 1; i <= val; i++)
	{

		printf("%d", bit_flags_check_flag(hBit, (i - 1)));
		if (i % 4 == 0)
		{
			printf(" ");
		}
		if (i % 32 == 0)
		{
			printf("\n");
		}
	}
	printf("\n");

	printf("Status: %d\n", bit_flags_unset_flag(hBit, 6));

	printf("size: %d Bits.\n", bit_flags_get_size(hBit));
	printf("Can hold up to %d Bits\n\n", bit_flags_get_capacity(hBit));

	bit_flags_destroy(&hBit);
	return 0;
}