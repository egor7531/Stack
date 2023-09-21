#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "Stack.h"

const char * nameFile2 = "Stack.cpp";

const Elem_t POISON = -777;

error stackCtor(Stack * stk)
{
    const char * nameFunction = "stackCtor()";

    assert(stk != NULL);

    stk -> sizeStack = 0;
    stk -> capacity = 5;
    stk -> data = (Elem_t *)calloc(stk -> capacity, sizeof(Elem_t));

    if(error err = stackCheck(stk))
    {
        stackDump(stk, nameFile2, nameFunction, 22);
        return err;
    }

    for(int i = 0; i < stk -> capacity; i++)
    {
        assert(0 <= i && i< stk -> capacity);

        stk -> data[i] = POISON;
    }
    return NOERROR;
}

error stackDtor(Stack * stk)
{
    const char * nameFunction = "stackDtor()";

    if(error err = stackCheck(stk))
    {
        stackDump(stk, nameFile2, nameFunction, 33);
        return err;
    }

    stk -> sizeStack = -1;
    stk -> capacity = -1;
    free(stk -> data);

    return NOERROR;
}


error stackRealloc(Stack * stk , change_capacity prm)
{
    const char * nameFunction = "stackRealloc()";

    if(error err = stackCheck(stk))
    {
        stackDump(stk, nameFile2, nameFunction, 57);
        return err;
    }


    if(prm == UP)
        stk -> capacity *= 2;

    else
        stk -> capacity /= 2;

    stk -> data = (Elem_t *)realloc(stk -> data, stk -> capacity*sizeof(Elem_t));

    if(error err = stackCheck(stk))
    {
        stackDump(stk, nameFile2, nameFunction, 72);
        return err;
    }

    for(int i = stk -> sizeStack; i < stk -> capacity; i++)
    {
        assert(0 <= i && i< stk -> capacity);

        stk -> data[i] = POISON;
    }
    return NOERROR;
}

error stackPush(Stack * stk, Elem_t value)
{
    const char * nameFunction = "stackPush()";

    if(error err = stackCheck(stk))
    {
        stackDump(stk, nameFile2, nameFunction, 84);
        return err;
    }

    if(stk -> sizeStack == stk -> capacity)
        stackRealloc(stk, UP);

    stk -> data[stk -> sizeStack++] = value;

    return NOERROR;

}

error stackPop(Stack * stk, Elem_t * RetValue)
{
    const char * nameFunction = "stackPush()";

    if(error err = stackCheck(stk))
    {
        stackDump(stk, nameFile2, nameFunction, 104);
        return err;
    }

    * RetValue = stk -> data[--stk -> sizeStack];

    stk -> data[stk -> sizeStack] = POISON;

    if(2*stk -> sizeStack < stk -> capacity)
        stackRealloc(stk, DOWN);

    return NOERROR;

}

error stackCheck(const Stack * stk)
{
    int err = NOERROR;

    if(!stk)                                err |= ENOSTK;
    if(!stk -> data)                        err |= ENODATA;
    if(stk -> sizeStack > stk -> capacity)  err |= ESIZEOUT;
    if(stk -> capacity <= 0)                err |= ECAPZERO;
    if(stk -> sizeStack < 0)                err |= ESIZE;

    return (error)err;
}

void stackDump(Stack * stk, const char * nameFile, const char * nameFunction, const size_t line)
{
    printf("called from %s %s(%d)\n", nameFile, nameFunction, line);
    printf("stack[%p]\n", stk);
    printf("size = %d\n", stk -> sizeStack);
    printf("capacity = %d\n", stk -> capacity);
    printf("data[%p]\n", stk -> data);

    for(int i = 0; i < stk -> capacity; i++)
    {
        if(stk -> data[0] == POISON)
            printf("[%d] = %d(POISON)\n", i, stk -> data[i]);

        else
            printf("*[%d] = %d\n", i, stk -> data[i]);
    }

    printf("\n");

}
