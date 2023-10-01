#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define DEBUG
#define PROTECT

typedef int elem_t;
typedef unsigned long long hash_t;
typedef unsigned long long canary_t;

struct myStack
{
    #ifdef PROTECT
    canary_t leftCanary;
    #endif

    elem_t * data;
    int sizeStack;
    int capacity;

    #ifdef PROTECT
    hash_t hash;
    canary_t rightCanary;
    #endif

};

enum stack_error_t
{
    NO_ERR              = 0 << 0,
    NO_STACK            = 1 << 0,
    NO_DATA             = 1 << 1,
    SIZE_LARGE_CAPACITY = 1 << 2,
    CAPACITY_ZERO       = 1 << 3,
    SIZE_NEGATIVE       = 1 << 4,
    CANARY_ERR_STK      = 1 << 5,
    CANARY_ERR_DATA     = 1 << 6,
    HASH_ERR            = 1 << 7
};

stack_error_t StackCtor(myStack * stk);
stack_error_t StackDtor(myStack * stk);
stack_error_t StackPush(myStack * stk, elem_t value);
stack_error_t StackPop(myStack * stk, elem_t * RetValue);

#ifdef DEBUG
stack_error_t CheckFunc(myStack * stk, stack_error_t err);
void StackDump(myStack * stk, const char * nameFile, const char * nameFunc, const size_t line, stack_error_t err);
#endif


#endif // STACK_H_INCLUDED
