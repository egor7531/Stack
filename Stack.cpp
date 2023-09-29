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
    for(int i = stk -> sizeStack; i < stk -> capacity; i++)
    {
        if(!(0 <= i && i< stk -> capacity))
            return ARRAY_OUT;

        stk -> data[i] = POISON;
    }

    return NO_ERR;
}
error writeData(myStack * stk)
{
    stk -> data = (elem_t *)(calloc(countMemory(stk), sizeof(char)));

    if(stk -> data == NULL)
        return NO_DATA;

    pointerOffset(stk);

    ((canary_t *)(stk -> data))[-1] = NUM_CANARY_DATA;
    ((elem_t *)(stk -> data))[stk -> capacity] = NUM_CANARY_DATA;

    error err = NO_ERR;

    if((err = fillPoison(stk)) > 0)
        return err;

    return NO_ERR;
}

error stackCtor(myStack * stk, const char * nameStack, size_t line, const char * nameFile, const char * nameFunc)
{
    #ifdef DEBUG
        stk -> leftCanary = NUM_CANARY_STACK;
        stk -> rightCanary = NUM_CANARY_STACK;

        stk -> nameStack = nameStack;
        stk -> line = line;
        stk -> nameFile = nameFile;
        stk -> nameFunc = nameFunc;
    #endif

    stk -> sizeStack = 0;
    stk -> capacity = 5;
    error err = NO_ERR;

    if((err = writeData(stk)) > 0)
        return err;

    #ifdef DEBUG
        stk -> myHash = getHash(stk);
    #endif
    return NO_ERR;
}

error stackDtor(myStack * stk)
{
    #ifdef DEBUG
    stk -> leftCanary = 0;
    stk -> rightCanary = 0;
    stk -> myHash = -1;
    #endif

    stk -> sizeStack = -1;
    stk -> capacity = -1;

    free((char *)stk -> data - sizeof(canary_t));

    return NO_ERR;
}


error stackRealloc(myStack * stk , capchange prm)
{
    canary_t copyCanary = ((elem_t *)(stk -> data))[stk -> capacity];

    if(prm == INCREASE)
        stk -> capacity *= 2;

    else
        stk -> capacity /= 2;

    stk -> data = (elem_t *)(realloc((char *)stk -> data - sizeof(canary_t), countMemory(stk)));

    if(stk -> data == NULL)
        return NO_DATA;

    pointerOffset(stk);

    ((elem_t *)(stk -> data))[stk -> capacity] = copyCanary;

    error err = NO_ERR;

    if((err = fillPoison(stk)) > 0)
        return err;

    return NO_ERR;
}

error stackPush(myStack * stk, elem_t value)
{
    error err = NO_ERR;

    if((err = hashCheck(stk)) > 0)
        return err;

    if(stk -> sizeStack == stk -> capacity)
    {
        if((err = stackRealloc(stk, INCREASE)) > 0)
            return err;
    }

    stk -> data[stk -> sizeStack++] = value;

    if((err = stackCheck(stk)) > 0)
        return err;

    stk -> myHash = getHash(stk);

    return NO_ERR;
}

error stackPop(myStack * stk, elem_t * RetValue)
{
    error err = NO_ERR;

    if((err = hashCheck(stk)) > 0)
        return err;

    * RetValue = stk -> data[--stk -> sizeStack];

    stk -> data[stk -> sizeStack] = POISON;

    if(2 * stk -> sizeStack < stk -> capacity)
    {
        if((err = stackRealloc(stk, DECREASE)) > 0)
            return err;
    }


    if((err = stackCheck(stk)) > 0)
        return err;

    stk -> myHash = getHash(stk);

    return NO_ERR;
}

void printStack(myStack * stk)
{
    printf("\n");

    for(size_t i = 0; i < stk -> sizeStack; i++)
        printf("[%d] = %d\n", i, stk -> data[i]);

    printf("\n");
}


