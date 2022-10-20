#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include"status.h"

typedef void* QUEUE;

/*pre:void
returns an address to a queue object if successfull
returns Null if it failed*/
QUEUE queue_init_default(void);

/*/adds using a head insert
//pre-condtion: hQ is a handle to a valid queue object and is given an integer value to insert
//ost-condition: returns success when node has been added to the object and failure if it fails
to allocate memory */
Status queue_enqueue(QUEUE hQ, int val);

/*/pre:a status is past by reffrence, along with a valid
//handle operator
//post: returns the value at the front of the Q, as 
//well as changes a status variable by refrence*/
int queue_front(QUEUE hQ, Status* pStatus);

/*/removes node at the front of the q
//pre: past the address of the handle 
//post: returns a status and a modified head node*/
Status queue_service(QUEUE hQ);

/*pre: hQ is a handle to a valid string object
post: returns true if q is empty and false if it is not*/ 
Boolean queue_is_empty(QUEUE hQ);

void  queue_destroy(QUEUE* phQ);

#endif
