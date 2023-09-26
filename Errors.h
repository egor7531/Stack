#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

#include <stdio.h>

#include "Consts.h"

error stackCheck(const myStack * stk);
void stackDump(myStack * stk, const char * nameFile, const char * nameFunction, const size_t line);

#endif // ERRORS_H_INCLUDED
