#include <stdlib.h>
#include <stdio.h>
#include "sorted-list.h"

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df)
{
    SortedListPtr list = (SortedListPtr)malloc(sizeof(SortedListPtr));
    //check malloc success 
    list->head = NULL;
    list->compare = cf;
    list->destroy = df;
}

void SLDestroy(SortedListPtr list)
{
    ListNodePtr currentNode = list->head;
    ListNodePtr prevNode = list->head;

    //Check if list is empty
    if(currentNode == NULL)
    {
        return;
    }
    
    //Empty list from tail to head
    while(list->head != NULL)
    {
        while(currentNode->next != NULL)
        {
            prevNode = currentNode;
            currentNode = currentNode->next;   
        }
        list->destroy(currentNode->data);
        currentNode = prevNode;
        free(currentNode->next);
        currentNode->next = NULL;
        currentNode = list->head;
        prevNode = list->head;
    }

    //Free the list ptr once list is empty
    free(list);
    return;
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

    //Check if list is empty:
    if(currentNode == NULL)
    {
        list->head = newNode;
        return 1;
    }
    
    //Check if newNode belongs in front of list
    int compareValue = list->compare(currentNode->data,newObj);
    if(compareValue < 0)
    {
        newNode->next = list->head;
        list->head = newNode; //is this line needed?
        return 1;
    }

    //Check if newNode belongs in middle of list
    while(currentNode->next != NULL)
    {
        currentNode = currentNode->next;
        compareValue = list->compare(currentNode->data,newObj);
        if(compareValue > 0)
        {
            prevNode = currentNode;
        }
        else if(compareValue <= 0)
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
    ListNodePtr currentNode = list->head;
    ListNodePtr prevNode = list->head;
    int compareValue = list->compare(currentNode->data,newObj);

    //Check if list is empty:
    if(currentNode == NULL)
    {
        return -1;
    }
    
    //Check if Obj is first node
    if(compareValue == 0)
    {
        list->head = currentNode->next;
        if(currentNode->refCount <= 1)
        {
            list->destroy(currentNode->data);
            free(currentNode);
        }
        return 1;
    }

    //Check if Obj is in middle of list
    while(currentNode->next != NULL)
    {
        currentNode = currentNode->next;
        compareValue = list->compare(currentNode->data,newObj);
        if(compareValue > 0)
        {
            prevNode = currentNode;
        }
        else if(compareValue == 0)
        {
            prevNode->next = currentNode->next;
            list->destroy(currentNode->data);
            free(currentNode);
            return 1;
        }
        else if(compareValue < 0)
        {
            return -2;
        }
    }
    //SLRemove could not find Obj
    return -2;
}
void SLPrintList(SortedListPtr list)
{
    ListNodePtr node = list->head;
    int i = 1;

    while(node != NULL)
    {
        printf("%d: %d\n",i,*((int*)node->data));
        node = node->next;
        i++;
    }
    return;
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list)
{
   //create a pointer to the linkedlist
   SortedListIteratorPtr it =(SortedListIteratorPtr)malloc(sizeof(SortedListIteratorPtr));
   it->node = list->head;
   it->list = list;
   if(it->node == NULL)
   {
       return it;
   }
   
   (it->node)->refCount++; //increment refCount since iterator points to node
   return it;
}


void SLDestroyIterator(SortedListIteratorPtr iter)
{
    free(iter);
}


void * SLNextItem(SortedListIteratorPtr iter)
{ 
    //all iterator elements have been iterated through 
    if(iter->node == NULL)
    {
      return NULL;   
    }
    ListNodePtr dNode = iter->node;


   //advance iterator to next node
    iter->node = iter->node->next;
   //(iter->node)->refCount++;
    if(dNode->refCount <= 1)
    {
        iter->list->destroy(dNode->data);
        free(dNode);
    }
    return (iter->node);
}


void * SLGetItem( SortedListIteratorPtr iter )
{
    if(iter->node == NULL)
    {
       return NULL;
    }
    else
    {
       return iter->node->data;
    }
}
