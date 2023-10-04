#include <stdio.h>

#include "Stack.h"
#include "StackDump.h"

int main()
{
    myStack stk = {};

    int err = NO_ERR;

    if(&stk == NULL)
        return STACK_NULL;

    StackCtor(&stk);

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

            StackPush(&stk, num);
        }

        else if(comand == 2)
        {
            elem_t num = 0;

            StackPop(&stk, &num);

            printf("\n" "num = %.2ex\n", num);
        }

        else if(comand == 0)
            break;

        STACK_DUMP(&stk, err);
    }

    StackDtor(&stk);

    return 0;
}
