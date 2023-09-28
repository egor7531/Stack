#include <stdio.h>

#include "Stack.h"

#define DEBUG

//#define STACK_CTOR(stack) stackCtor((stack), #stack, __LINE__, __FILE__, __func__)


int main()
{
#ifdef DEBUG

    myStack stk = {};

    if(&stk == NULL)
        return NO_STACK;

    error err = stackCtor(&stk);

    if(err > 0)
        stackDump(&stk, __FILE__, __func__, __LINE__, err);

    while(true)
    {
        printf("Press 0 to finish\n");
        printf("Press 1 to call Push\n");
        printf("Press 2 to call Pop\n");

        int comand = 0;

        printf("comand = ");
        scanf("%d", &comand);

        if(comand == 1)
        {
            int num = 0;

            printf("num = ");
            scanf("%d", &num);

            err = stackPush(&stk, num);
            if(err > 0)
                stackDump(&stk, __FILE__, __func__, __LINE__, err);

        }

        else if(comand == 2)
        {
            int num = 0;

            err = stackPop(&stk, &num);
            if(err > 0)
                stackDump(&stk, __FILE__, __func__, __LINE__, err);

            printf("num = %d\n", num);
        }

        else if(comand == 0)
            break;

        stackDump(&stk, __FILE__, __func__, __LINE__, NO_ERR);

    }

    return stackDtor(&stk);

#endif

}
