#include <stdio.h>
#include "Errors.h"

error stackCheck(const myStack * stk)
{
    int err = NO_ERR;

    if(!stk)                                                                                                    err |= NO_STACK;
    if(!stk -> data)                                                                                            err |= NO_DATA;
    if(stk -> sizeStack > stk -> capacity)                                                                      err |= SIZE_OUT;
    if(stk -> capacity <= 0)                                                                                    err |= CAPACITY_ZERO;
    if(stk -> sizeStack < 0)                                                                                    err |= SIZE_NEGATIVE;
    if(stk -> leftCanary != NUM_CANARY_STACK || stk -> rightCanary != NUM_CANARY_STACK)                                       err |= CANARY_ERR_STK;
    if(((canary_t *)stk -> data)[-1] != NUM_CANARY_DATA || stk -> data[stk -> capacity] != NUM_CANARY_DATA)   err |= CANARY_ERR_DATA;

    return (error)err;
}

void stackDump(myStack * stk, const char * nameFile, const char * nameFunc, const size_t line)
{
    printf("called from %s %s(%d)\n", nameFile, nameFunc, line);
    printf("stack[%p]\n", stk);
    printf("size = %d\n", stk -> sizeStack);
    printf("capacity = %d\n", stk -> capacity);
    printf("data[%p]\n", stk -> data);
    printf("leftCanary = %llu\n", stk -> leftCanary);
    printf("rightCanary = %llu\n", stk -> rightCanary);

    for(int i = -1; i <= stk -> capacity; i++)
    {
        if(i == -1)
            printf("%p <%llu>\n", ((canary_t *)(stk -> data)) + i, ((canary_t *)(stk -> data))[i]);

        else if(i == stk -> capacity)
            printf("%p <%d>\n", stk -> data + i, stk -> data[i]);

        else if(stk -> data[0] == POISON)
            printf("%p [%d] = %d(POISON)\n", stk -> data + i, i, stk -> data[i]);

        else
            printf("%p *[%d] = %d\n", stk -> data + i, i, stk -> data[i]);
    }

    printf("\n");

}
