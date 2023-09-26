#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "Errors.h"

error stackCtor(myStack * stk);
error stackDtor(myStack * stk);
error stackPush(myStack * stk, elem_t value);
error stackPop(myStack * stk, elem_t * RetValue);

#endif // STACK_H_INCLUDED
