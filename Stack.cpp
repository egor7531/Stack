#include <assert.h>
#include <stdlib.h>

#include "Stack.h"
#include "StackDump.h"

const int coeffIncrease = 2;
const int coeffDecrease = 2;

#ifdef STK_PROTECT
const canary_t NUM_CANARY_STACK = 0xDEDABABA;
const canary_t NUM_CANARY_DATA  = 0xBADCAFE;
#endif

const int initialCapacity = 4;

#ifdef STK_PROTECT
hash_t get_value_hash(const Stack * stk)
{
    assert(stk       != NULL);
    assert(stk->data != NULL);

    const int initialValue = 5831;
    const int coeffChange = 33;

    hash_t hash = initialValue;

    for (int i = 0; i < sizeof(Stack); i++)
        hash = coeffChange * hash + *((char *)(stk) + i);

    for (int i = 0; i < stk->capacity; i++)
        hash = coeffChange * hash + *((char *)(stk->data) + i);

    return hash;
}

bool hash_check(Stack * stk)
{
    assert(stk != NULL);

    hash_t hashRef = stk->hash;

    stk->hash = 0;

    return hashRef != get_value_hash(stk);
}
#endif

int stack_check(Stack * stk)
{
    int err = NO_ERR;

    if(stk == NULL)                                     return STACK_NULL;
    if(stk->data == NULL)                               return stk->errors = DATA_NULL;

    if(stk->sizeStack > stk->capacity)                  err |= SIZE_LARGE_CAPACITY;
    if(stk->capacity <= 0)                              err |= CAPACITY_ZERO;
    if(stk->sizeStack < 0)                              err |= SIZE_NEGATIVE;

    #ifdef STK_PROTECT
    if(stk->leftCanary != NUM_CANARY_STACK
    || stk->rightCanary != NUM_CANARY_STACK)
                                                        err |= CANARY_ERR_STK;

    if(((canary_t *)stk->data)[-1] != NUM_CANARY_DATA
    || *(canary_t *)(((elem_t *)(stk->data)) + stk->capacity) != NUM_CANARY_DATA)
                                                        err |= CANARY_ERR_DATA;
    if(hash_check(stk))                                 err |= HASH_ERR;
    #endif

    stk->errors |= err;

    return stk->errors;
}

#ifdef STK_PROTECT
void set_canary(Stack * stk)
{
    assert(stk         != NULL);
    assert(stk -> data != NULL);

    ((canary_t *)(stk->data))[-1] = NUM_CANARY_DATA;
    *(canary_t *)(((elem_t *)(stk->data)) + stk -> capacity) = NUM_CANARY_DATA;
}
#endif

size_t get_data_size(Stack * stk)
{
    assert(stk != NULL);

    size_t sizeCanary = 0;

    #ifdef STK_PROTECT
    sizeCanary += 2 * sizeof(canary_t);
    #endif

    return stk->capacity * sizeof(elem_t) + sizeCanary;
}

void fill_poison(Stack * stk)
{
    assert(stk       != NULL);
    assert(stk->data != NULL);

    for(int i = stk->sizeStack; i < stk->capacity; i++)
    {
        assert(stk->sizeStack <= i && i < stk->capacity);

        stk->data[i] = POISON;
    }

}

int stack_ctor(Stack * stk)
{
    if(stk == NULL)
    {
        STACK_DUMP(stk);
        stack_dtor(stk);
        return STACK_NULL;
    }

    #ifdef STK_PROTECT
    stk->leftCanary  = NUM_CANARY_STACK;
    stk->rightCanary = NUM_CANARY_STACK;
    #endif

    stk->sizeStack = 0;
    stk->capacity  = initialCapacity;

    stk->data = (elem_t *)(calloc(get_data_size(stk), sizeof(char)));

    if(stk->data == NULL)
    {
        stk->errors |= DATA_NULL;
        STACK_DUMP(stk);
        stack_dtor(stk);
        return stk->errors;
    }

    #ifdef STK_PROTECT
    stk->data = (elem_t *)((char *)stk->data + sizeof(canary_t));
    #endif

    fill_poison(stk);

    #ifdef STK_PROTECT
    set_canary(stk);
    stk->hash = get_value_hash(stk);
    #endif

    return NO_ERR;
}

int stack_dtor(Stack * stk)
{
    assert(stk != NULL);

    stk->data = (elem_t *)((char *)stk->data - sizeof(canary_t));
    free(stk->data);
    stk->data = NULL;
    stk = NULL;

    return NO_ERR;
}


int stack_realloc_if_needed(Stack * stk)
{
    assert(stk       != NULL);
    assert(stk->data != NULL);

    if(stk->sizeStack == stk->capacity)
        stk->capacity *= coeffIncrease;

    else if(coeffDecrease * stk->sizeStack  < stk->capacity && stk->capacity > initialCapacity)
        stk->capacity /= coeffDecrease;

    else
        return NO_ERR;

    #ifdef STK_PROTECT
    stk->data = (elem_t *)((char *)stk->data - sizeof(canary_t));
    #endif

    stk->data = (elem_t *)(realloc(stk->data, get_data_size(stk)));

    if(stk->data == NULL)
    {
        stk->errors |= DATA_NULL;
        STACK_DUMP(stk);
        stack_dtor(stk);
        return stk->errors;
    }

    #ifdef STK_PROTECT
    stk->data = (elem_t *)((char *)stk->data + sizeof(canary_t));
    #endif

    fill_poison(stk);

    #ifdef STK_PROTECT
    set_canary(stk);
    #endif

    return NO_ERR;
}

int stack_push(Stack * stk, elem_t value)
{
    int err = stack_check(stk);
    if(stk != NULL)
        stk->errors |= err;
    if(err != NO_ERR)
    {
        STACK_DUMP(stk);
        stack_dtor(stk);
        return err;
    }

    stack_realloc_if_needed(stk);

    stk->data[stk->sizeStack] = value;

    stk->sizeStack++;

    #ifdef STK_PROTECT
    stk->hash = get_value_hash(stk);
    #endif

    return NO_ERR;
}

int stack_pop(Stack * stk, elem_t * retValue)
{
    assert(stk         != NULL);
    assert(stk->data   != NULL);
    assert(retValue    != NULL);    // ???

    int err = stack_check(stk);
    if(stk != NULL)
        stk->errors |= err;
    if(err != NO_ERR)
    {
        STACK_DUMP(stk);
        stack_dtor(stk);
        return err;
    }

    --stk->sizeStack;

    if(stk->sizeStack < 0)
    {
        stk->errors |= SIZE_NEGATIVE;
        STACK_DUMP(stk);
        stack_dtor(stk);
        return err;
    }

    *retValue = stk->data[stk->sizeStack];

    stk->data[stk->sizeStack] = POISON;

    stack_realloc_if_needed(stk);

    #ifdef STK_PROTECT
    stk->hash = get_value_hash(stk);
    #endif

    return NO_ERR;
}
