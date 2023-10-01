#include <stdio.h>

#include "Stack.h"

int main()
{
    myStack stk = {};

    if(&stk == NULL)
        return NO_STACK;

    stack_error_t err = CheckFunc(&stk, StackCtor(&stk));

    if(err > 0)
        return err;

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
            int num = 0;

            printf("num = ");
            scanf("%d", &num);

            err = CheckFunc(&stk, StackPush(&stk, num));

            if(err > 0)
                return err;
        }

        else if(comand == 2)
        {
            int num = 0;

            err = CheckFunc(&stk, StackPop(&stk, &num));

            if(err> 0)
                return err;

            printf("\nnum = %d\n", num);
        }

        else if(comand == 0)
            break;

        StackDump(&stk, __FILE__, __func__, __LINE__, NO_ERR);
    }

    StackDtor(&stk);

    return 0;
}
