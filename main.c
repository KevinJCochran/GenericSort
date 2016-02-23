#include <stdlib.h>
#include <stdio.h>
#include "sorted-list.h"

int compareInt(void* a, void* b)
{
    int* x = (int*)a;
    int* y = (int*)b;

    if(*x > *y)
    {
        return 1;
    }
    else if(*x < *y)
    {
        return -1;
    }
    else if(*x == *y)
    {
        return 0;
    }
    return -2;
}

void destroyInt(void* i)
{
    return;
}

int main(int argc, char ** argv)
{   
    int testNums[] = {2,3,5,4,6,1,0,7,9,8};
    int x = 0;

    int (*compare)(void*, void*) = compareInt;
    void (*destroy)(void*) = destroyInt;

    SortedListPtr myList = SLCreate(compare,destroy);
    
    printf("\n=====Insertion=====\n");

    int i = 0;
    for(i = 0; i < 10; i++)
    {
        int check = SLInsert(myList,(void*)(&testNums[i]));
        printf("check %d: %d\n",i,check);
    }

    SLPrintList(myList);

    printf("\n=====Removal=====\n");

    int * testNum = &x;

    int check = SLRemove(myList,(void*)testNum);
    printf("check: %d\n",check);

    *testNum = 3; 
    check = SLRemove(myList,(void*)testNum);
    printf("check: %d\n",check);

    *testNum = 9;
    check = SLRemove(myList,(void*)testNum);
    printf("check: %d\n",check);

    SLPrintList(myList);

    printf("\n=====PrintList=====\n");

    SortedListIteratorPtr itr = SLCreateIterator(myList);
    int* data = &x;

    for(i = 0; i < 15; i++)
    {
        data = (int*)SLGetItem(itr);
        SLNextItem(itr);
        printf("Data%d: %d\n",i,*data);
    }
    return 0;

    SLDestroyIterator(itr);
    SLDestroy(myList);
}
