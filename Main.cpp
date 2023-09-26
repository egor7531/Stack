#include <stdio.h>

#include "Stack.h"

#define DEBUG

//#define STACK_CTOR(stack) stackCtor((stack), #stack, __LINE__, __FILE__, __func__)


int main()
{
    myStack stk = {};

    stackCtor(&stk);

#ifdef DEBUG

    while(true)
    {
        int comand = 0;

        printf("comand = ");
        scanf("%d", &comand);

        if(comand == 1)
        {
            int num = 0;
            printf("num = ");
            scanf("%d", &num);
            stackPush(&stk, num);
        }

        else if(comand == 2)
        {
            int num = 0;
            stackPop(&stk, &num);
            printf("num = %d\n", num);
        }

        else if(comand == 777)
            break;

        stackDump(&stk, __FILE__, __func__, __LINE__);

    }

#endif

    stackDtor(&stk);

    return 0;
}
