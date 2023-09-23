#include <stdio.h>

#include "Stack.h"

#define STACK_CTOR(stack) stackCtor((stack), #stack, __LINE__, __FILE__, __func__)


int main()
{
    Stack stk;

    STACK_CTOR(&stk);

    stackPush(&stk,1);

    stackDtor(&stk);

    return 0;
}
