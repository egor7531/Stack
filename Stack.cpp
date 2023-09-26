#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "Stack.h"


error writeData(myStack * stk)
{
    stk -> data = (elem_t *)calloc(stk -> capacity * sizeof(elem_t), 1);        //stk -> data = (elem_t *)((char *)calloc(stk -> capacity * sizeof(elem_t) + 2 * sizeof(canary_t), 1) + sizeof(canary_t));

    assert(stk -> data != NULL);

    if(error err = stackCheck(stk))
    {
        stackDump(stk, __FILE__, __func__, __LINE__);
        return err;
    }

    //*(((canary_t *)stk -> data) - 1) = NUMCANARY;
    //((canary_t *)stk -> data)[stk -> capacity] = NUMCANARY;

    for(int i = 0; i < stk -> capacity; i++)
    {
        assert(0 <= i && i < stk -> capacity);

        stk -> data[i] = POISON;
    }

    return NO_ERR;
}

error stackCtor(myStack * stk)
{
    assert(stk != NULL);

    //stk -> leftCanary = NUMCANARY;
    //stk -> rightCanary = NUMCANARY;

    stk -> sizeStack = 0;
    stk -> capacity = 5;

    writeData(stk);

    return NO_ERR;
}

error stackDtor(myStack * stk)
{
    stackCheck(stk);

    stk -> sizeStack = -1;
    stk -> capacity = -1;
    free(stk -> data);

    return NO_ERR;
}


error stackRealloc(myStack * stk , capchange prm)
{
    if(error err = stackCheck(stk))
    {
        stackDump(stk, __FILE__, __func__, __LINE__);
        return err;
    }

    if(prm == INCREASE)
        stk -> capacity *= 2;

    else
        stk -> capacity /= 2;

    stk -> data = (elem_t *)(realloc(stk -> data, stk -> capacity * sizeof(elem_t));       //    stk -> data = (elem_t *)((char *)realloc(stk -> data - sizeof(canary_t), stk -> capacity * sizeof(elem_t) + 2 * sizeof(canary_t)) + sizeof(canary_t));


    if(error err = stackCheck(stk))
    {
        stackDump(stk, __FILE__, __func__, __LINE__);
        return err;
    }

    for(int i = stk -> sizeStack; i < stk -> capacity; i++)
    {
        assert(0 <= i && i< stk -> capacity);

        stk -> data[i] = POISON;
    }
    return NO_ERR;
}

error stackPush(myStack * stk, elem_t value)
{

    if(error err = stackCheck(stk))
    {
        stackDump(stk, __FILE__, __func__, __LINE__);
        return err;
    }

    if(stk -> sizeStack == stk -> capacity)
        stackRealloc(stk, INCREASE);

    stk -> data[stk -> sizeStack++] = value;

    return NO_ERR;

}

error stackPop(myStack * stk, elem_t * RetValue)
{
    if(error err = stackCheck(stk))
    {
        stackDump(stk, __FILE__, __func__, __LINE__);
        return err;
    }

    * RetValue = stk -> data[--stk -> sizeStack];

    stk -> data[stk -> sizeStack] = POISON;

    if(2*stk -> sizeStack < stk -> capacity)
        stackRealloc(stk, DECREASE);

    return NO_ERR;

}
