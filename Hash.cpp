#include <stdio.h>

#include "Hash.h"

hash_t getHash(const myStack * stk)
{
    hash_t myHash = 5831;

    for (int i = 0; i < sizeof(myStack); i++)
        myHash = 33 * myHash + *((char *)(stk) + i);

    for (int i = 0; i < stk -> capacity; i++)
        myHash = 33 * myHash + *((char *)(stk -> data) + i);

    return myHash;
}

error hashCheck(myStack * stk)
{
    hash_t myHashRef = stk -> myHash;
    stk -> myHash = 0;

    if(myHashRef != getHash(stk))
        return HASH_ERR;

    return NO_ERR;
}
