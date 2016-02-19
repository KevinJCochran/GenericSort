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
}

int SLInsert(SortedListPtr list, void *newObj)
{
    //initialize the new node
    ListNodePtr newNode = (ListNodePtr)malloc(sizeof(ListNodePtr));
    newNode->refCount = 1;
    newNode->data = newObj;
    newNode->next = NULL;

    ListNodePtr currentNode = list->head;
    ListNodePtr prevNode = list->head;
    int compareValue = list->compare(currentNode->data,newObj);

    //Check if list is empty:
    if(currentNode == NULL)
    {
        list->head = newNode;
        return 1;
    }
    
    //Check if newNode belongs in front of list
    if(compareValue < 0)
    {
        newNode = list->head;
        list->head = newNode;
        return 1;
    }

    //Step current node one forward from prev node
    currentNode = currentNode->next;

    //Check if newNode belongs in middle of list
    while(currentNode->next != NULL)
    {
        currentNode = currentNode->next;
        compareValue = list->compare(currentNode->data,newObj);
        if(compareValue > 0)
        {
            prevNode = currentNode;
        }
        else if(compareValue < 0)
        {
            prevNode->next = newNode;
            newNode->next = currentNode;
            return 1;
        }
    }

    //newNode belongs at end of list
    currentNode->next = newNode;
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
}


void * SLNextItem(SortedListIteratorPtr iter)
{

}


void * SLGetItem( SortedListIteratorPtr iter )
{

}
