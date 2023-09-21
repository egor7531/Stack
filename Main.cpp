#include <stdio.h>

#include "Stack.h"

const char * nameFile1 = "Main.cpp";

int main()
{
    const char * nameFunction = "main()";

    Stack stk = {};

    stackCtor(&stk);

    stackDump(&stk, nameFile1, nameFunction, 15, NOERROR);

    stackPush(&stk, 10);

    stackDump(&stk, nameFile1, nameFunction, 19, NOERROR);

    stackPush(&stk, 20);

    stackDump(&stk, nameFile1, nameFunction, 23, NOERROR);

    stackPush(&stk, 30);

    stackDump(&stk, nameFile1, nameFunction, 27, NOERROR);

    stackPush(&stk, 40);

    stackDump(&stk, nameFile1, nameFunction, 31, NOERROR);

    stackPush(&stk, 50);

    stackDump(&stk, nameFile1, nameFunction, 35, NOERROR);

    stackPush(&stk, 60);

    stackDump(&stk, nameFile1, nameFunction, 39, NOERROR);

    return 0;
}
