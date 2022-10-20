#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"


typedef struct priority_queue Priority_queue;
typedef struct data_node Data_node;

struct priority_queue
{
	int size; 
	int capacity; 
	Data_node* data;
};

typedef struct data_node
{
	int priority;
	int value;
};

//pre: handed a valid node array, and valid index
//modifies heep into order of priority
void fix_up(Data_node heap[], int index);

void fix_down(Data_node heap[], int index, int size);

PRIORITY_QUEUE priority_queue_init_default(void)
{
	Priority_queue* pQ = (Priority_queue*)malloc(sizeof(Priority_queue));
	if (pQ != NULL)
	{
		pQ->size = 0;
		pQ->capacity = 4;
		pQ->data = (Data_node*)malloc(sizeof(Data_node) * pQ->capacity);
		if (pQ->data == NULL)
		{
			free(pQ);
			return NULL;
		}
	}
	return pQ;
}

Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item)
{
	int i;
	Priority_queue* pQ = (Priority_queue*)hQueue;
	Data_node* temp;
	//resize operation if need before any insertions are done
	if (pQ->size >= pQ->capacity)
	{
		temp = (Data_node*)malloc(sizeof(Data_node) * pQ->capacity * 2);
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pQ->size; i++)
		{
			//should copy addresses over from old array
			temp[i] = pQ->data[i];
		}
			free(pQ->data);
			pQ->data = temp;
			pQ->capacity = pQ->capacity * 2;
	}
	
	
		//inserts value into a node on the heap array
		//store addres of node on variable for easier access
		
		pQ->data[pQ->size].priority = priority_level;
		pQ->data[pQ->size].value = data_item;
		pQ->size++;

		fix_up((*pQ).data, pQ->size-1);

	return SUCCESS;
}

Status priority_queue_service(PRIORITY_QUEUE hQueue)
{
	Priority_queue* pQ = (Priority_queue*)hQueue;
	if (priority_queue_is_empty(pQ))
	{
		return FAILURE;
	}
	int temp, tempVal;
	temp = pQ->data[0].priority;
	tempVal = pQ->data[0].value;
	pQ->data[0].priority = pQ->data[pQ->size-1].priority;
	pQ->data[0].value = pQ->data[pQ->size - 1].value;
	pQ->data[pQ->size - 1].priority = temp;
	pQ->data[pQ->size - 1].value = tempVal;
	pQ->size--;
	//print_q(pQ);
	fix_down(pQ->data, 0, pQ->size);
	return SUCCESS;
}

Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue)
{
	Priority_queue* pQ = (Priority_queue*)hQueue;
	if (pQ->size > 0)
	{
		return FALSE;
	}
	return TRUE;

}

int priority_queue_front(PRIORITY_QUEUE hQueue, Status* pStatus)
{
	Priority_queue* pQ = (Priority_queue*)hQueue;
	if (priority_queue_is_empty(pQ))
	{
		if (pStatus != NULL)
		{
			*pStatus = FAILURE;
		}
		return -393420;
	}
	*pStatus = SUCCESS;
	return pQ->data[0].value;
}

void fix_down(Data_node heap[], int index, int size)
{
	int index_of_left_child = (index * 2) + 1;
	int index_of_right_child = (index * 2) + 2;
	int index_of_largest_child;
	

	if (index_of_left_child < size)//means there exsists one child
	{
		if (index_of_right_child < size)//there are two children
		{
			index_of_largest_child = (heap[index_of_left_child].priority) > (heap[index_of_right_child].priority) ? index_of_left_child : index_of_right_child;
		}
		else if (index_of_left_child < size)
		{
			index_of_largest_child = index_of_left_child;
		}
		if (heap[index_of_largest_child].priority > (heap[index].priority))
		{
			int temp, tempVal;
			temp = heap[index].priority;
			tempVal = heap[index].value;
			heap[index].priority = heap[index_of_largest_child].priority;
			heap[index].value = heap[index_of_largest_child].value;
			heap[index_of_largest_child].priority = temp;
			heap[index_of_largest_child].value = tempVal;

			fix_down(heap, index_of_largest_child, size);
		}
	}
}

void fix_up(Data_node heap[], int index)
{
	int index_of_parent;
	
	if (index > 0)
	{
		index_of_parent = (index - 1) / 2;
		//tells wether one index is a higher priority than another
		if (heap[index].priority > heap[index_of_parent].priority)
		{
			//swaps the indexs if they are
			Data_node* temp;
			int value, priority;
			
			
			//vars temporarily hold node values of int type and and address
			priority = heap[index].priority;
			value = heap[index].value;
			temp = heap + index;

			heap[index] = heap[index_of_parent];
			heap[index_of_parent] = *temp;
			//temp = temp;
			heap[index_of_parent].priority = priority;
			heap[index_of_parent].value = value;
 			fix_up(heap, index_of_parent);
		}

	}
	return;
}

void priority_queue_print(PRIORITY_QUEUE hQueue)
{
	Priority_queue* pQ = (Priority_queue*)hQueue;
	printf("PRIORITY   DATA   ADDRESS\n");
	printf("________________________________\n");
	for (int i = 0; i < pQ->capacity; i++)
	{
		printf("%5d %7d %10p \n", pQ->data[i].priority, pQ->data[i].value, pQ->data+i);
	}
	printf("\n");
}

void priority_queue_destroy(PRIORITY_QUEUE* phQueue)
{
	Priority_queue* pQ = (Priority_queue*)*phQueue;
	free(pQ->data);
	free(pQ);
	*phQueue = NULL;
}
