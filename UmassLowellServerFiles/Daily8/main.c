#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

int main(int argc, char* argv[])
{
	PRIORITY_QUEUE hQ = priority_queue_init_default();
	Status status;
	int size = 1;

	priority_queue_insert(hQ, 17, size);
	priority_queue_insert(hQ, 10, size);
	priority_queue_insert(hQ, 90, size);
	priority_queue_insert(hQ, 47, size);
	priority_queue_insert(hQ, 34, size);
	priority_queue_insert(hQ, 68, size);
	priority_queue_insert(hQ, 45, size);
	priority_queue_insert(hQ, 70, size);
	priority_queue_insert(hQ, 1, size);
	priority_queue_insert(hQ, 56, size);
	priority_queue_insert(hQ, 99, size);
	printf("%d\n",priority_queue_front(hQ, &status));
	priority_queue_print(hQ);
	printf("%d\n", priority_queue_is_empty(hQ));
	priority_queue_service(hQ);
	priority_queue_service(hQ);
	priority_queue_service(hQ);
	priority_queue_service(hQ);
	priority_queue_service(hQ);
	priority_queue_service(hQ);
	priority_queue_service(hQ);
	priority_queue_service(hQ);
	priority_queue_service(hQ);
	priority_queue_service(hQ);
	priority_queue_service(hQ);
	printf("%d\n", priority_queue_front(hQ, &status));
	printf("%d\n",priority_queue_front(hQ, NULL));

	priority_queue_print(hQ);
	printf("%d\n", priority_queue_is_empty(hQ));
	
	priority_queue_destroy(&hQ);
	return 0;
}
