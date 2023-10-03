#include <assert.h>
#include <stdio.h>

#include "StackDump.h"
#include "Stack.h"

#define DATA_TYPE     "%0.2lf"
#define POSION_TYPE   "%0.2lf"
#define CANARY_TYPE   "%x"
#define HASH_TYPE     "%llu"

void PrintError(int err)
{
    printf("status: ");

    if(err == NO_ERR)
        printf("No error\n");

    if(err & STACK_NULL)
        printf("Pointer on stack NULL\n");

    if(err & DATA_NULL)
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

void StackDump(myStack * stk, const char * nameFile, const char * nameFunc, const size_t line, int err)
{
    assert(stk         != NULL);
    assert(stk -> data != NULL);

    printf("\n");
    printf("called from %s %s(%d)\n", nameFile, nameFunc, line);
    printf("stack[%p]\n", stk);
    printf("size = %d\n", stk->sizeStack);
    printf("capacity = %d\n", stk->capacity);
    printf("data[%p]\n", stk->data);

    #ifdef STK_PROTECT
    printf("leftCanary = " CANARY_TYPE "\n", stk->leftCanary);
    printf("rightCanary = " CANARY_TYPE "\n", stk->rightCanary);
    printf("hash = " HASH_TYPE "\n", stk->hash);
    #endif

    PrintError(err);

    #ifdef STK_PROTECT
    printf("%p <" CANARY_TYPE ">\n", ((canary_t *)(stk -> data)) + -1, ((canary_t *)(stk -> data))[-1]);
    #endif

    for(size_t i = 0; i < (size_t)stk -> capacity; i++)
    {
        assert(i < (size_t)stk -> capacity);

       if(stk -> data[i] == POISON)
            printf("%p [%d] = " POSION_TYPE "(POISON)\n", stk -> data + i, i, stk -> data[i]);

        else
            printf("%p *[%d] = " DATA_TYPE "\n", stk -> data + i, i, stk -> data[i]);
    }

    #ifdef STK_PROTECT
    printf("%p <" CANARY_TYPE ">\n", stk -> data + stk -> capacity, stk -> data[stk -> capacity]);
    #endif

    printf("\n");
}
