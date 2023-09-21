#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef int Elem_t;

struct Stack
{
    Elem_t * data;
    size_t sizeStack;
    size_t capacity;
};

enum ERROR {NOERROR = 0, ENOSTK = 1, ENODATA = 2, ESIZEOUT = 4, ECAPZERO = 8};


ERROR stackCtor(Stack * stk);
ERROR stackDtor(Stack * stk);
ERROR stackCheck(const Stack * stk);
ERROR stackRealloc(Stack * stk);
void stackDump(Stack * stk, const char * nameFile, const char * nameFunction, const size_t line, ERROR err);
ERROR stackPush(Stack * stk, Elem_t value);
ERROR stackPop(Stack * stk, Elem_t * RetValue);

#endif // STACK_H_INCLUDED
