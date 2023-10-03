#include <stdio.h>

#include "Stack.h"
#include "StackDump.h"

int main()
{
    myStack stk = {};

    if(&stk == NULL)
        return STACK_NULL;

    int err = StackCtor(&stk);

    if(err != NO_ERR)
    {
        STACK_DUMP(&stk, err);
        return err;
    }

    while(true)
    {
        printf("Press 0 to finish\n");
        printf("Press 1 to call Push\n");
        printf("Press 2 to call Pop\n");

        int comand = 0;

        printf("command = ");
        scanf("%d", &comand);

        if(comand == 1)
        {
            elem_t num = 0;

            printf("num = ");
            scanf("%lf", &num);

            err = StackPush(&stk, num);

            if(err != NO_ERR)
            {
                STACK_DUMP(&stk, err);
                return err;
            }
        }

        else if(comand == 2)
        {
            elem_t num = 0;

            err = StackPop(&stk, &num);

            if(err != NO_ERR)
            {
                STACK_DUMP(&stk, err);
                return err;
            }

            printf("\nnum = %.2ex\n", num);
        }

        else if(comand == 0)
            break;

        STACK_DUMP(&stk, err);
    }

    StackDtor(&stk);

    return 0;
}
