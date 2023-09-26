#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED

//#define STACK_DUMP(stack) stackDump((stack), __FILE__, __func__, __LINE__)

typedef int elem_t;

typedef unsigned long long canary_t;

struct myStack
{
    //canary_t leftCanary = 0;
    elem_t * data = 0;
    int sizeStack = 0;
    int capacity = 0;
    /*char * nameStack;
    int line = 0;
    char * nameFile;
    char * nameFunc; */
    //canary_t rightCanary = 0;

};

const elem_t POISON = -777;
const canary_t NUMCANARY = 1e6;

enum error {NO_ERR = 0, NO_STACK = 1, NO_DATA = 2, SIZE_OUT = 4, CAPACITY_ZERO = 8, SIZE_NEGATIVE = 16, CANARY_ERR_STK = 32, CANARY_ERR_DATA = 64};
enum capchange {INCREASE, DECREASE};

#endif // CONSTS_H_INCLUDED
