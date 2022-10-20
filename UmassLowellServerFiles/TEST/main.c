/*Daily 7 stack 
* Author: Daniel Bergeorn
* Date: 2/17/2022
* Time spent: 20hrs 
* Purpose: The purpose of this program will use a linked list implementation of a stack
* too check and see if a string operator is valid  by checking to see if 
* the strig brackets match and returning no if they do not.
*/
#include "test.h"

void clear_key_board_buffer(void);
Boolean test_case_is_valid(void);

int main(int argc, char* argv[])
{
	int cases, i;

	scanf("%d", &cases);
	clear_key_board_buffer();

	for (i = 0; i < cases; i++)
	{

		if (test_case_is_valid())
		{
			printf("Yes\n");
		}
		else
		{	
			printf("No\n");
		}

	}	

	return 0;
}

void clear_key_board_buffer(void)
{
	int noc;
	char c;
	noc = scanf("%c", &c);
	while (noc == 1 && c != '\n')
	{
		noc = scanf("%c", &c);
	}
}
Boolean test_case_is_valid(void)
{
	STACK hMy_stack = NULL;
	char c, top_item;
	int noc;
	Status check = FAILURE;
	Boolean flag1 = FALSE, flag2 = FALSE, flag3 = FALSE;
	
	noc = scanf("%c", &c);
	while (noc == 1 && c != '\n')
	{
		if ((c == ']' || c == ')' || c == '}') && my_stack_is_empty(hMy_stack))
		{
			flag1 = TRUE;
		}
		if (c == '(' || c == '[' || c == '{')
		{
			my_stack_push(&hMy_stack, c);
		}
		if ((c == '}' || c == ']' || c == ')'))
		{
			top_item = my_stack_top(hMy_stack, &check);
			if (((int)top_item + 1 == (int)c) || (int)top_item + 2 == (int)c)
			{
				my_stack_pop(&hMy_stack);
			}
			else
			{
				flag2 = TRUE;
			}
		}

		
		noc = scanf("%c", &c);
	}
	if (!(my_stack_is_empty(hMy_stack)))
	{
		flag3 = TRUE;
	}
	my_stack_destroy(hMy_stack);
	if (flag1 || flag2 || flag3)
	{
		return FALSE;
	}
	
	return TRUE;
}




