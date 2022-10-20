#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include "status.h"

typedef void* STACK;

/*/push
//pre-c:passes handle by reffrence and passes a char var by value
//post-c:a node will be added to stack, and hMystack will have been changed*/
Status my_stack_push(STACK* phMy_stack, char item);

Boolean my_stack_is_empty(STACK hMy_stack);

Status my_stack_pop(STACK* phstack);

/*/top-gets first item in stack
//pre-condtion: item is past a valid stack handle 
//and a valid status pointer which can be assigned null
//post-condtion: the function will return the value of the
//item at the toip of the stack*/
char my_stack_top(STACK hstack, Status* pstatus);

void my_stack_destroy(STACK hMy_stack);

#endif
