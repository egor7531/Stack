#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef int Elem_t;

struct Stack
{
    Elem_t * data = 0;
    int sizeStack = 0;
    int capacity = 0;
};

enum error {NOERROR = 0, ENOSTK = 1, ENODATA = 2, ESIZEOUT = 4, ECAPZERO = 8, ESIZE = 16};

enum change_capacity {UP, DOWN};


error stackCtor(Stack * stk);
error stackDtor(Stack * stk);
error stackCheck(const Stack * stk);
error stackRealloc(Stack * stk, change_capacity prm);
error stackPush(Stack * stk, Elem_t value);
error stackPop(Stack * stk, Elem_t * RetValue);
void stackDump(Stack * stk, const char * nameFile, const char * nameFunction, const size_t line);

#endif // STACK_H_INCLUDED
