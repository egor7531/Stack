#ifndef STACKDUMP_H_INCLUDED
#define STACKDUMP_H_INCLUDED

#include "Stack.h"

#define STACK_DUMP(stk) stack_dump(stk, __FILE__, __func__, __LINE__)

void stack_dump(const Stack * stk, const char * nameFile,
                const char * nameFunc, const size_t line);

#endif // STACKDUMP_H_INCLUDED
