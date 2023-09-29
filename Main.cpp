#include <stdio.h>

#include "Stack.h"
#include "Consts.h"

int main(int argc, char * argv[])
{
#ifdef DEBUG

    myStack stk = {};

    if(&stk == NULL)
        return NO_STACK;

    if(checkFunc(&stk, STACK_CTOR(&stk)) > 0)
        return -1;

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

            if(checkFunc(&stk, stackPush(&stk, num)) > 0)
                return -1;
        }

        else if(comand == 2)
        {
            int num = 0;

            if(checkFunc(&stk, stackPop(&stk, &num)) > 0)
                return -1;

            printf("\nnum = %d\n", num);
        }

        else if(comand == 0)
            break;

        printStack(&stk);
    }

    return stackDtor(&stk);

#endif

}
