#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define STK_PROTECT

typedef int elem_t;

#ifdef STK_PROTECT
typedef unsigned long long hash_t;
typedef unsigned long long canary_t;
#endif

const elem_t POISON = -777;

struct Stack
{
    #ifdef STK_PROTECT
    canary_t leftCanary;
    #endif

    elem_t * data;
    int sizeStack;
    int capacity;
    int errors;

    #ifdef STK_PROTECT
    hash_t hash;
    canary_t rightCanary;
    #endif

};

enum stack_error_t
{
    NO_ERR              = 0 << 0,
    STACK_NULL          = 1 << 0,
    DATA_NULL           = 1 << 1,
    SIZE_LARGE_CAPACITY = 1 << 2,
    CAPACITY_ZERO       = 1 << 3,
    SIZE_NEGATIVE       = 1 << 4,
    CANARY_ERR_STK      = 1 << 5,
    CANARY_ERR_DATA     = 1 << 6,
    HASH_ERR            = 1 << 7
};

Stack* stack_ctor();
int stack_dtor(Stack * stk);
int stack_push(Stack * stk, elem_t value);
int stack_pop(Stack * stk, elem_t * retValue);

#endif // STACK_H_INCLUDED
