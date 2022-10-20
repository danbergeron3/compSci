/*Daily 7 stack 
* Author: Daniel Bergeorn
* Date: 2/17/2022
* Time spent: 20hrs 
* Purpose: The purpose of this program will use a linked list implementation of a stack
* too check and see if a string operator is valid  by checking to see if 
* the strig brackets match and returning no if they do not.
*/
#include "stack.h"

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
	STACK hStack = stack_init_default();
	char c, top_item;
	int noc;
	Status check = FAILURE;
	Boolean flag1 = FALSE, flag2 = FALSE, flag3 = FALSE;

	/*stack_is_empty(hStack);

	stack_push(hStack, 'c');
	stack_push(hStack, 'u');
	stack_push(hStack, 'n');
	stack_push(hStack, 'n');
	stack_push(hStack, 'i');
	stack_push(hStack, 'n');
	stack_push(hStack, 'g');

	stack_pop(hStack);
	stack_pop(hStack);
	stack_pop(hStack);
	stack_pop(hStack);
	stack_pop(hStack);

	c = stack_top(hStack, &check);*/
	
	noc = scanf("%c", &c);
	while (noc == 1 && c != '\n')
	{
		if ((c == ']' || c == ')' || c == '}') && stack_is_empty(hStack))
		{
			flag1 = TRUE;
		}
		if (c == '(' || c == '[' || c == '{')
		{
			stack_push(hStack, c);
		}
		if ((c == '}' || c == ']' || c == ')'))
		{
			top_item = stack_top(hStack, &check);
			if (((int)top_item + 1 == (int)c) || (int)top_item + 2 == (int)c)
			{
				stack_pop(hStack);
			}
			else
			{
				flag2 = TRUE;
			}
		}

		
		noc = scanf("%c", &c);
	}
	if (!(stack_is_empty(hStack)))
	{
		flag3 = TRUE;
	}
	stack_destroy(&hStack);
	if (flag1 || flag2 || flag3)
	{
		return FALSE;
	}
	
	return TRUE;

	
}
