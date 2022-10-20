#include "queue.h"

typedef struct queue Queue;

typedef struct node Node;

struct node
{
	int data;
	Node* next;
};

struct queue
{
	Node* front;
	Node* back;
};

QUEUE queue_init_default(void)
{
	/*Intiates queue with null*/
	Queue* temp = (Queue*)malloc(sizeof(Queue));
	if (temp == NULL)
	{
		return NULL;
	}
	temp->front = NULL;
	temp->back = NULL;

	return temp;
}

Status queue_enqueue(QUEUE hQ, int val)
{
	/*will add item to the back of the q*/
	Queue* pQ = (Queue*)hQ;
	Node* temp, *previous;
	
	if (pQ->front == NULL && pQ->back == NULL)
	{
		temp = (Node*)malloc(sizeof(Node));
		if (temp == NULL)
		{
			return FAILURE;
		}
		temp->next = NULL;
		temp->data = val;
		pQ->front = temp;
		pQ->back = temp;
	}
	else
	{
		previous = pQ->back;
		temp = (Node*)malloc(sizeof(Node));
		if (temp == NULL)
		{
			return FAILURE;
		}
		temp->next = NULL;
		temp->data = val;
		previous->next = temp;
		pQ->back = temp;
	}
	return SUCCESS;
}

int queue_front(QUEUE hQ, Status* pStatus)
{
	Queue* pQ = (Queue*)hQ;
	Node* pNode;
	if (queue_is_empty(hQ))
	{
		if (pStatus != NULL)
		{
			*pStatus = FAILURE;
		}
			return -39369420;
	}
	else
	{
		*pStatus = SUCCESS;
	}
	pNode = pQ->front;
	return pNode->data;
}

Boolean queue_is_empty(QUEUE hQ)
{
	Queue* pQ = (Queue*)hQ;
	if (pQ->front == NULL)
	{
		return TRUE;
	}
	return FALSE;
}

Status queue_service(QUEUE hQ)
{
	Queue* pQ = (Queue*)hQ;
	Node* pNode = pQ->front;
	
	if (queue_is_empty(hQ))
	{
		return FAILURE;
	}

	pQ->front = pNode->next;
	free(pNode);
	pNode = NULL;
	return SUCCESS;
}

void queue_destroy(QUEUE* phQ)
{
	Queue* pQ = (Queue*)*phQ;
	Node* pNode, *temp;
	pNode = pQ->front;
	while (pNode != NULL)
	{
		temp = pNode;
		pNode = pNode->next;
		free(temp);
	}
	free(pQ);
	*phQ = NULL;
}


