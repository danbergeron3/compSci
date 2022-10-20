/*
* FERRY LOADING
* Author: Daniel Bergeron
* Date: 2/21/2022
* Time Spent: 24hrs
* Purpose: This program is designed to simulate a fairy crossing a river 
* to pick up and drop of cars as efficently as possible. It acomplishes this 
* by taking advantage of using a queue data structure to populate each bank where 
* then the fairy which has limited space will take the first cars into the queue across
* the water. 
*/
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "queue.h"

void clear_key_board_buffer(void);
Status run_test(void);
void convert_to_meters_centimeters(int* length);
Status choose_q(QUEUE hLq, QUEUE hRq, char position[], int length);
Status get_output(QUEUE hLq, QUEUE hRq, int L_boat);

int main(int argc, char* argv[])
{
	int num_test, i;

	scanf("%d", &num_test);
	clear_key_board_buffer();

	for (i = 0; i < num_test; i++)
	{
		if (run_test() != SUCCESS)
		{
			return 1;
		}
	}
	return 0;
}

Status run_test(void)
{
	QUEUE hLq = queue_init_default();
	QUEUE hRq = queue_init_default();
	if (hLq == NULL || hRq == NULL)
	{
		printf("Failed to allocate space\n");
		exit(1);
	}
	int L_boat, L_car, items, i;
	char position[10];

	scanf("%d %d", &L_boat, &items);
	clear_key_board_buffer();
	convert_to_meters_centimeters(&L_boat);
	
	for(i = 0; i < items; i++)
	{
		scanf("%d %s", &L_car, position);
		clear_key_board_buffer();
		if (choose_q(hLq, hRq, position, L_car) != SUCCESS)
		{
			return FAILURE;
		}
	}
	if(get_output(hLq, hRq, L_boat) != SUCCESS)
	{
		return FAILURE;
	}

	queue_destroy(&hLq);
	queue_destroy(&hRq);
	return SUCCESS;
}

Status get_output(QUEUE hLq, QUEUE hRq, int L_boat)
{
	Status Status1 = SUCCESS, Status2 = SUCCESS;
	State Fairy = LEFT;
	int used_space = 0, trips = 0, temp;
	
	if (queue_is_empty(hLq) && queue_is_empty(hRq))
	{
		printf("%d", trips);
		return SUCCESS;
	}
	while (Status1 || Status2)
	{
		if (Fairy == LEFT)
		{
			temp = (queue_front(hLq, &Status1));
			if (Status1 == FAILURE)
			{
				if (Status2 != FAILURE)
				{
					trips++;
					used_space = 0;
					Fairy = RIGHT;
				}
				else if (used_space > 0)
				{
					trips++;
					used_space = 0;
					Fairy = RIGHT;
				}
			
			}
			else if (used_space + temp >= L_boat)
			{
				trips++;
				used_space = 0;
				Fairy = RIGHT;
			}
			else 
			{
				used_space = used_space + temp;
				queue_service(hLq);
			}
			
		}
		if (Fairy == RIGHT)
		{
			temp = (queue_front(hRq, &Status2));
			if (Status2 == FAILURE)
			{
				if (Status1 != FAILURE)
				{
					trips++;
					used_space = 0;
					Fairy = LEFT;
				}
				else if (used_space > 0)
				{
					trips++;
					used_space = 0;
					Fairy = LEFT;;
				}
			}
			else if (used_space + temp >= L_boat)
			{
				trips++;
				used_space = 0;
				Fairy = LEFT;
			}
			else
			{
				used_space = used_space + temp;
				queue_service(hRq);
			}
		}		
	}
	printf("%d\n", trips);
	return SUCCESS;
}
Status choose_q(QUEUE hLq, QUEUE hRq, char position[], int length)
{
	char strL[] = "left";
	char strR[] = "right";
	int i = 0;
	
	if (strcmp(strL, position) == 0)
	{
		while (strL[i] != '\0')
		{
			if (strL[i] != position[i])
			{
				return FAILURE;
			} 		
			i++;
		}
		if (queue_enqueue((hLq), length) != SUCCESS)
		{
			return FAILURE;
		}
	}
	else if (strcmp(strR, position) == 0)
	{
		while (strR[i] != '\0')
		{
			if (strR[i] != position[i])
			{
				return FAILURE;
			}	
			i++;
		}
		if (!queue_enqueue(hRq, length))
		{
			return FAILURE;
		}
	}
	else
	{
		return FAILURE;
	}
	return SUCCESS;
}
void convert_to_meters_centimeters(int* length)
{
	*length = *length * 100;
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
