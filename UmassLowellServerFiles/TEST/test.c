#include "test.h"

typedef struct stack Stack;

struct stack
{
	char data;
	Stack* next;
};

/*/push
//pre-c:passes handle by reffrence and passes a char var by value
//post-c:a node will be added to stack, and hMystack will have been changed*/
Status my_stack_push(STACK* phMy_stack, char item)
{
	/*/casts the derreffrenced handle to the known type, 
	//assigns new pointers to hold object addresses*/
	Stack* phead = (Stack*)*phMy_stack;
	Stack* temp, *next;
	next = phead;

	/*/creates space for new node*/
	temp = (Stack*)malloc(sizeof(Stack));
	if (temp == NULL)
	{
		return FAILURE;
	}

	//assigns values to node
	temp->data = item;
	temp->next = next;

	/*/gives pheand temps address there by pushing down entire stack*/
	phead = temp;

	/*/casts phead to void star and gives the handle new value*/
	*phMy_stack = (STACK)phead;
	
	return SUCCESS;
}


Boolean my_stack_is_empty(STACK hMy_stack)
{
	Stack* pstack = (Stack*)hMy_stack;
	if (pstack == NULL)
	{
		return TRUE;
	}
	/*/printf("stack is empty\n");*/
	return FALSE;

}
/*/top-gets first item in stack
//pre-condtion: item is past a valid stack handle 
//and a valid status pointer which can be assigned null
//post-condtion: the function will return the value of the
//item at the toip of the stack*/
char my_stack_top(STACK hMy_stack, Status* pstatus)
{
	Stack* pstack = (Stack*)hMy_stack;
	
	if (my_stack_is_empty(hMy_stack))
	{
		/*/if user past null in as an argument for pstatus it will not change*/
		if (pstatus != NULL)
		{
			*pstatus = FAILURE;
		}
		return -39342069;
	}
	if (pstatus != NULL)
	{
		*pstatus = SUCCESS;
	}
	 
	return pstack->data;
}

/*/pop removes top form stack
//pre-condtion valid handle is past to the function
//post-conditiok top itme fo stack has been removed */
Status my_stack_pop(STACK* phMy_stack)
{
	Stack* pstack = (Stack*)*phMy_stack;
	Stack* temp;
	/*/checks if stack is empty*/
	if (my_stack_is_empty(*phMy_stack))
	{
		return FAILURE;
	}
	
	temp = pstack;/*sets temp = first node//moves head to second noe//passes the address to the handle ny reffrence*/
	pstack = pstack->next;
	*phMy_stack = (STACK)pstack;

	free(temp);/*/removes possible memory leek*/
	temp = NULL;

	return SUCCESS;
}

/*/destroy/bookend
//pre-c: valid object handle is past
//post-c:allocated space is freed & addresses are set to NULL*/
void my_stack_destroy(STACK hMy_stack)
{
	Stack* pstack = (Stack*)hMy_stack;
	
	if (!(my_stack_is_empty(hMy_stack)))
	{
		my_stack_destroy(pstack->next);
		free(pstack);
		pstack = NULL;
	}

	return;
}


