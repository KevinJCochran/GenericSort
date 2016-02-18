#include <stdlib.h>
#include <stdio.h>
#include "sorted-list.h"

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df)
{
    SortedListPtr list = (SortedListPtr)malloc(sizeof(SortedListPtr));
    list->head = NULL;
    list->compare = cf;
    list->destroy = df;
}

void SLDestroy(SortedListPtr list)
{
    return 0;
}

int SLInsert(SortedListPtr list, void *newObj)
{
    /*
    ListNode newNode = {0,newObj,NULL};
    ListNode prevNode = list->head;
    compareValue = 0;
    while(node->next != NULL)
    {
        compareValue = list->compare(node->data,newObj);
        if(compareValue > 0)
        {
            node = node->next;
        }
        else if(compareValue < 0)
        {
            
        }
    }
    */
    return 1;
}

int SLRemove(SortedListPtr list, void *newObj)
{
    return 1;
}


SortedListIteratorPtr SLCreateIterator(SortedListPtr list)
{
    return NULL;
}


void SLDestroyIterator(SortedListIteratorPtr iter)
{
    return 
}


void * SLNextItem(SortedListIteratorPtr iter)
{

}


void * SLGetItem( SortedListIteratorPtr iter )
{

}
