#include <stdio.h>

#include "Stack.h"

const char * nameFile1 = "Main.cpp";

int main()
{

    Stack stk = {};

    stackDtor(&stk);

    return 0;
}
