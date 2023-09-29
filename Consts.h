#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED

#define DEBUG

#ifdef DEBUG

    #define STACK_CTOR(stack) stackCtor((stack), #stack, __LINE__, __FILE__, __func__)

#endif

typedef int elem_t;
typedef unsigned long long canary_t;
typedef unsigned long long hash_t;

struct myStack
{
    #ifdef DEBUG
    canary_t leftCanary = 0;
    #endif

    elem_t * data = NULL;
    int sizeStack = 0;
    int capacity = 0;

    #ifdef DEBUG
    const char * nameStack = NULL;
    size_t line = 0;
    const char * nameFile = NULL;
    const char * nameFunc = NULL;

    hash_t myHash = 0;
    canary_t rightCanary = 0;
    #endif

};

const elem_t POISON = -777;
const canary_t NUM_CANARY_STACK = 654321;
const canary_t NUM_CANARY_DATA = 123456;

enum error
{
    NO_ERR           = 0 << 0,
    NO_STACK         = 1 << 0,
    NO_DATA          = 1 << 1,
    SIZE_OUT         = 1 << 2,
    CAPACITY_ZERO    = 1 << 3,
    SIZE_NEGATIVE    = 1 << 4,
    CANARY_ERR_STK   = 1 << 5,
    CANARY_ERR_DATA  = 1 << 6,
    ARRAY_OUT        = 1 << 7,
    HASH_ERR         = 1 << 8
};

enum capchange {INCREASE, DECREASE};

#endif // CONSTS_H_INCLUDED
