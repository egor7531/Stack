#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "Stack.h"

/*#define DATA_TYPE    %d
#define POSION_TYPE  %d         ???
#define CANARY_TYPE  %x
#define HASH_TYPE    %llu */

//enum change_capacity_t {INCREASE, DECREASE};

const int coeffIncrease = 2;
const int coeffDecrease = 2;

#ifdef PROTECT
const canary_t NUM_CANARY_STACK = 0xDEDABABA;
const canary_t NUM_CANARY_DATA = 0xBADCAFE;
#endif

const elem_t POISON = -777;

const int initialCapacity = 4;
const int initialSize = 0;

#ifdef PROTECT
hash_t GetValueHash(const myStack * stk)
{
    assert(stk         != NULL);
    assert(stk -> data != NULL);

    const int initialValue = 5831;
    const int coeffChange = 33;

    hash_t hash = initialValue;

    for (size_t i = 0; i < sizeof(myStack); i++)
    {
        assert(i < sizeof(myStack));

        hash = coeffChange * hash + *((char *)(stk) + i);
    }

    for (size_t i = 0; i < (size_t)stk -> capacity; i++)
    {
        assert(i < (size_t)stk -> capacity);

        hash = coeffChange * hash + *((char *)(stk -> data) + i);
    }

    return hash;
}

bool HashCheck(myStack * stk)
{
    assert(stk != NULL);

    hash_t hashRef = stk -> hash;

    stk -> hash = 0;

    return hashRef != GetValueHash(stk);
}
#endif

stack_error_t StackCheck(myStack * stk)
{
    assert(stk != NULL);

    int err = NO_ERR;

    if(stk -> sizeStack > stk -> capacity)                                                                      err |= SIZE_LARGE_CAPACITY;
    if(stk -> capacity <= 0)                                                                                    err |= CAPACITY_ZERO;
    if(stk -> sizeStack < 0)                                                                                    err |= SIZE_NEGATIVE;

    #ifdef PROTECT
    if(stk -> leftCanary != NUM_CANARY_STACK || stk -> rightCanary != NUM_CANARY_STACK)                         err |= CANARY_ERR_STK;
    if(((canary_t *)stk -> data)[-1] != NUM_CANARY_DATA || stk -> data[stk -> capacity] != NUM_CANARY_DATA)     err |= CANARY_ERR_DATA;
    if(HashCheck(stk))                                                                                          err |= HASH_ERR;
    #endif

    return (stack_error_t)err;
}

void PrintError(stack_error_t err)
{
    printf("status: ");

    if(err == 0)
        printf("No error\n");

    if(err & NO_STACK)
        printf("Pointer on stack NULL\n");

    if(err & NO_DATA)
        printf("Pointer on data NULL\n");

    if(err & SIZE_LARGE_CAPACITY)
        printf("Size > Capacity\n");

    if(err & CAPACITY_ZERO)
        printf("Capacity is negative or zero\n");

    if(err & SIZE_NEGATIVE)
        printf("Size is negative\n");

    if(err & CANARY_ERR_STK)
        printf("Value of Canary in struct change\n");

    if(err & CANARY_ERR_DATA)
        printf("Value of Canary in array of Data change\n");

    if(err & HASH_ERR)
        printf("Hash change\n");
}

void StackDump(myStack * stk, const char * nameFile, const char * nameFunc, const size_t line, stack_error_t err)
{
    assert(stk         != NULL);
    assert(stk -> data != NULL);

    printf("called from %s %s(%d)\n", nameFile, nameFunc, line);
    printf("stack[%p]\n", stk);
    printf("size = %d\n", stk -> sizeStack);
    printf("capacity = %d\n", stk -> capacity);
    printf("data[%p]\n", stk -> data);

    #ifdef PROTECT
    printf("leftCanary = %x\n", stk -> leftCanary);
    printf("rightCanary = %x\n", stk -> rightCanary);
    printf("hash = %llu\n", stk -> hash);
    #endif

    printf("err = %d\n", err);

    PrintError(err);

    for(int i = -1; i <= stk -> capacity; i++)
    {
        assert(-1 <= i && i <= stk -> capacity);

       if(stk -> data[i] == POISON)
            printf("%p [%d] = %d(POISON)\n", stk -> data + i, i, stk -> data[i]);

        #ifdef PROTECT
        else if(i == -1)
            printf("%p <%x>\n", ((canary_t *)(stk -> data)) + i, ((canary_t *)(stk -> data))[i]);

        else if(i == stk -> capacity)
            printf("%p <%x>\n", stk -> data + i, stk -> data[i]);
        #endif

        else
            printf("%p *[%d] = %d\n", stk -> data + i, i, stk -> data[i]);
    }

    printf("\n");
}

stack_error_t CheckFunc(myStack * stk, stack_error_t err)
{
    assert(stk != NULL);

    if(err > 0)
        StackDump(stk, __FILE__, __func__, __LINE__, err);

    return err;
}

#ifdef PROTECT
void GetCanary(myStack * stk)
{
    assert(stk         != NULL);
    assert(stk -> data != NULL);

    ((canary_t *)(stk -> data))[-1] = NUM_CANARY_DATA;
    *(canary_t *)(((elem_t *)(stk -> data)) + stk -> capacity) = NUM_CANARY_DATA;
}
#endif

size_t GetSizeMemory(myStack * stk)
{
    assert(stk != NULL);

    return stk -> capacity * sizeof(elem_t) + 2 * sizeof(canary_t);
}

void FillPoison(myStack * stk)
{
    assert(stk         != NULL);
    assert(stk -> data != NULL);

    for(size_t i = stk -> sizeStack; i < (size_t)stk -> capacity; i++)
    {
        assert(i < (size_t)stk -> capacity);

        stk -> data[i] = POISON;
    }

}

stack_error_t StackCtor(myStack * stk)
{
    #ifdef PROTECT
    stk -> leftCanary = NUM_CANARY_STACK;
    stk -> rightCanary = NUM_CANARY_STACK;
    #endif

    stk -> sizeStack = initialSize;
    stk -> capacity = initialCapacity;

    stk -> data = (elem_t *)(calloc(GetSizeMemory(stk), sizeof(char)));

    if(stk -> data == NULL)
        return NO_DATA;

    stk -> data = (elem_t *)((char *)(stk -> data) + sizeof(canary_t));

    FillPoison(stk);

    #ifdef PROTECT
    GetCanary(stk);
    stk -> hash = GetValueHash(stk);
    #endif

    return NO_ERR;
}

stack_error_t StackDtor(myStack * stk)
{
    assert(stk != NULL);

    #ifdef PROTECT
    stk -> leftCanary = 0;
    stk -> rightCanary = 0;
    stk -> hash = -1;
    #endif

    stk -> sizeStack = -1;
    stk -> capacity = -1;

    free((char *)stk -> data - sizeof(canary_t));

    return NO_ERR;
}


stack_error_t StackRealloc(myStack * stk)
{
    assert(stk         != NULL);
    assert(stk -> data != NULL);

    if(stk -> sizeStack == stk -> capacity)
        stk -> capacity *= coeffIncrease;

    else if(coeffDecrease * stk -> sizeStack < stk -> capacity)
        stk -> capacity /= coeffDecrease;

    else
        return NO_ERR;

    stk -> data = (elem_t *)(realloc((char *)stk -> data - sizeof(canary_t), GetSizeMemory(stk)));

    if(stk -> data == NULL)
        return NO_DATA;

    stk -> data = (elem_t *)((char *)(stk -> data) + sizeof(canary_t));

    FillPoison(stk);

    #ifdef PROTECT
    GetCanary(stk);
    #endif

    return NO_ERR;
}

stack_error_t StackPush(myStack * stk, elem_t value)
{
    assert(stk != NULL);

    stack_error_t err = CheckFunc(stk, StackCheck(stk));

    if(err  > 0)
        return err;

    if(stk -> sizeStack == stk -> capacity)
    {
        err = CheckFunc(stk, StackRealloc(stk));

        if(err > 0)
            return err;
    }

    stk -> data[stk -> sizeStack] = value;

    stk -> sizeStack++;
    #ifdef PROTECT
    stk -> hash = GetValueHash(stk);
    #endif

    return NO_ERR;
}

stack_error_t StackPop(myStack * stk, elem_t * RetValue)
{
    assert(stk         != NULL);
    assert(stk -> data != NULL);

    stack_error_t err = CheckFunc(stk, StackCheck(stk));

    --stk -> sizeStack;

    if(err  > 0)
        return err;

    * RetValue = stk -> data[stk -> sizeStack];

    stk -> data[stk -> sizeStack] = POISON;

    if(coeffDecrease * stk -> sizeStack < stk -> capacity)
    {
        err = CheckFunc(stk, StackRealloc(stk));

        if(err > 0)
            return err;
    }

    #ifdef PROTECT
    stk -> hash = GetValueHash(stk);
    #endif

    return NO_ERR;
}

size_t GetSizeStack(myStack * stk)
{
    assert(stk != NULL);

    return sizeof(*stk) + GetSizeMemory(stk);
}
