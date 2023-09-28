#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "Stack.h"

size_t countMemory(myStack * stk)
{
    return stk -> capacity * sizeof(elem_t) + 2 * sizeof(canary_t);
}

void pointerOffset(myStack * stk)
{
    stk -> data = (elem_t *)((char *)(stk -> data) + sizeof(canary_t));

}

error fillPoison(myStack * stk)
{
    int err = NO_ERR;

    for(int i = stk -> sizeStack; i < stk -> capacity; i++)
    {
        if(!(0 <= i && i< stk -> capacity))
            err |= ARRAY_OUT;

        stk -> data[i] = POISON;
    }

    return (error)err;
}
error writeData(myStack * stk)
{
    int err = NO_ERR;

    stk -> data = (elem_t *)(calloc(countMemory(stk), sizeof(char)));

    if(stk -> data == NULL)
        err |= NO_DATA;

    pointerOffset(stk);

    ((canary_t *)(stk -> data))[-1] = NUM_CANARY_DATA;
    ((elem_t *)(stk -> data))[stk -> capacity] = NUM_CANARY_DATA;

    err |= fillPoison(stk);

    return (error)err;
}

error stackCtor(myStack * stk)
{
    int err = NO_ERR;

    stk -> leftCanary = NUM_CANARY_STACK;
    stk -> sizeStack = 0;
    stk -> capacity = 5;
    stk -> rightCanary = NUM_CANARY_STACK;

    err |= writeData(stk);

    return (error)err;
}

error stackDtor(myStack * stk)
{
    stk -> leftCanary = 0;
    stk -> sizeStack = -1;
    stk -> capacity = -1;
    stk -> rightCanary = 0;

    free((char *)stk -> data - sizeof(canary_t));

    return NO_ERR;
}


error stackRealloc(myStack * stk , capchange prm)
{
    int err = NO_ERR;

    canary_t copyCanary = ((elem_t *)(stk -> data))[stk -> capacity];

    if(prm == INCREASE)
        stk -> capacity *= 2;

    else
        stk -> capacity /= 2;

    stk -> data = (elem_t *)(realloc((char *)stk -> data - sizeof(canary_t), countMemory(stk)));

    if(stk -> data == NULL)
        err |= NO_DATA;

    pointerOffset(stk);

    ((elem_t *)(stk -> data))[stk -> capacity] = copyCanary;

    err |= fillPoison(stk);

    return (error)err;
}

error stackPush(myStack * stk, elem_t value)
{
    int err = NO_ERR;

    if(stk -> sizeStack == stk -> capacity)
        err |= stackRealloc(stk, INCREASE);

    stk -> data[stk -> sizeStack++] = value;

    err |= stackCheck(stk);

    return (error)err;
}

error stackPop(myStack * stk, elem_t * RetValue)
{
    int err = NO_ERR;

    * RetValue = stk -> data[--stk -> sizeStack];

    stk -> data[stk -> sizeStack] = POISON;

    if(2 * stk -> sizeStack < stk -> capacity)
        err |= stackRealloc(stk, DECREASE);

    err |= stackCheck(stk);

    return (error)err;
}
