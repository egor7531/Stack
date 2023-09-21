#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "Stack.h"

const char * nameFile2 = "Stack.cpp";

const Elem_t POISON = -777;

ERROR stackCtor(Stack * stk)
{
    assert(stk != NULL);

    stk -> sizeStack = 0;
    stk -> capacity = 5;
    stk -> data = (Elem_t *)calloc(stk -> capacity, sizeof(Elem_t));

    assert(stk -> data != NULL);

    for(size_t i = 0; i < stk -> capacity; i++)
        stk -> data[i] = POISON;

    return NOERROR;
}

ERROR stackDtor(Stack * stk)
{
    assert(stk != NULL);

    stk -> sizeStack = 0;
    stk -> capacity = 0;
    free(stk -> data);

    return NOERROR;
}

ERROR stackCheck(const Stack * stk)
{
    int err = NOERROR;

    if(!stk)                                err |= ENOSTK;
    if(!stk -> data)                        err |= ENODATA;
    if(stk -> sizeStack > stk -> capacity) err |= ESIZEOUT;
    if(!stk -> capacity)                    err |= ECAPZERO;

    return (ERROR)err;
}

ERROR stackRealloc(Stack * stk)
{
    assert(stk != NULL);

    stk -> capacity = 2*stk -> capacity;

    stk -> data = (Elem_t *)realloc(stk -> data, stk -> capacity*sizeof(Elem_t));

    assert(stk -> data != NULL);

    return NOERROR;
}

void stackDump(Stack * stk, const char * nameFile, const char * nameFunction, const size_t line, ERROR err)
{
    printf("called from %s %s(%d)\n", nameFile, nameFunction, line);
    printf("Error = %d\n", err);
    printf("stack[%p]\n", stk);
    printf("size = %d\n", stk -> sizeStack);
    printf("capacity = %d\n", stk -> capacity);
    printf("data[%p]\n", stk -> data);

    for(size_t i = 0; i < stk -> capacity; i++)
    {
        if(stk -> data[0] == POISON)
            printf("[%d] = %d(POISON)\n", i, stk -> data[i]);

        else
            printf("*[%d] = %d\n", i, stk -> data[i]);
    }

    printf("\n");

}

ERROR stackPush(Stack * stk, Elem_t value)
{
    const char * nameFunction = "stackPush()";

    ERROR err = stackCheck(stk);
    if(err)
        stackDump(stk, nameFile2, nameFunction, 85, err);

    if(stk -> sizeStack >= stk -> capacity)
        stackRealloc(stk);

    stk -> data[stk -> sizeStack++] = value;

    return NOERROR;

}

ERROR stackPop(Stack * stk, Elem_t * RetValue)
{
    assert(stk != NULL);

    * RetValue = stk -> data[--stk -> sizeStack];

    stk -> data[stk -> sizeStack] = POISON;

    return NOERROR;

}
