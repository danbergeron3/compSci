#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "status.h"

typedef void* STACK;

//init deafult
//pre-condtion: is given a valid stack handle
//post-condtion: returns an intizilized stack with head set to NULL
STACK stack_init_default(void);

/*/push
//pre-c:passes handle by reffrence and passes a char var by value
//post-c:a node will be added to stack, and hMystack will have been changed*/
Status stack_push(STACK hStack, char item);

Boolean stack_is_empty(STACK hStack);

/* pop removes top form stack
////pre-condtion valid handle is past to the function
////post-condition top item of stack is removed */
Status stack_pop(STACK hStack);

/*/top-gets first item in stack
//pre-condtion: item is past a valid stack handle 
//and a valid status pointer which can be assigned null
//post-condtion: the function will return the value of the
//item at the toip of the stack*/
char stack_top(STACK hStack, Status* pstatus);

void stack_destroy(STACK* phStack);

#endif
