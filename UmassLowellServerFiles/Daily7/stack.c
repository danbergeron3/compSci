#include "stack.h"

typedef struct node Node;

struct node
{
	char data;
	Node* next;
};

struct stack
{
	Node* head;
};

typedef struct stack Stack;


STACK stack_init_default(void)
{
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack == NULL)
	{
		printf("FAILED TO INIT STACK\n");
		return pStack;
	}
	pStack->head = NULL;

	return pStack;
}

Status stack_push(STACK hStack, char item)
{
	Stack* pStack = (Stack*)hStack;
	Node* temp;

	if (pStack != NULL)
	{
		temp = (Node*)malloc(sizeof(Node));
		if (temp == NULL)
		{
			return FAILURE;
		}
		temp->data = item;
		temp->next = pStack->head;
		pStack->head = temp;
	}
	else
	{
		return FAILURE;
	}

	return SUCCESS;
}

Status stack_pop(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	Node* temp;
	if (stack_is_empty(hStack))
	{
		return FAILURE;
	}
	temp = pStack->head;
	pStack->head = temp->next;
	free(temp);

	return SUCCESS;
}

Boolean stack_is_empty(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	if (pStack == NULL)
	{
		return TRUE;
	}
	if (pStack->head == NULL)
	{
		return TRUE;
	}
	
	return FALSE;
}

char stack_top(STACK hStack, Status* pStatus)
{
	Stack* pStack = (Stack*)hStack;
		
	if (stack_is_empty(hStack))
	{
		if (*pStatus != NULL)
		{
			*pStatus = FAILURE;
		}
		return NULL;
	}

	Node* pNode = pStack->head;
	if (*pStatus != NULL)
	{
		*pStatus = SUCCESS;
	}

	return pNode->data;
	
}


void stack_destroy(STACK* phStack)
{
	Stack* pStack = (Stack*)*phStack;
	Node* pNode = pStack->head, *temp;
	
	while (pNode != NULL)
	{
		temp = pNode->next;
		free(pNode);
		pNode = temp;
	}

	free(pStack);
	*phStack = NULL;
	//printf("Destroyification complete\n");
}
