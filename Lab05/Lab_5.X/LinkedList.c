/* 
 * File:   LinkedList.c
 * Author: Neili Hu(nehu@ucsc.edu)
 * ID: 1752639
 *
 * Created on January 31, 2022, 1:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "BOARD.h"

/*
 * 
 */
ListItem *LinkedListNew(char *data)
{
    ListItem *link = (ListItem *)malloc(8*sizeof(data)) ;
    if (link == NULL) {
        return NULL;
    } else {
        link->previousItem = NULL;
        link->nextItem = NULL;
        link->data = data;
        return link;
    }
}

ListItem *LinkedListCreateAfter(ListItem *item, char *data)
{
    ListItem *link = (ListItem *)malloc(8*sizeof(data)),
             *i;
    
    if (link == NULL) {
        i = NULL;
    } else if (item == NULL) {
        link = LinkedListNew(data);
        i = link;
    } else if (item != NULL) {                       //There is two situation in there.
        if (item->nextItem == NULL) {                //if the linkedlist is single or more than two 
            item->nextItem = link;                   //This one is for the single
            link->previousItem = item;
            link->data = data;
            link->nextItem = NULL;
        } else if (item->nextItem != NULL) {         //This one is for the more than two.
            link->previousItem = item;
            link->data = data;
            link->nextItem = item->nextItem;
            item->nextItem = link;
            (link->nextItem)->previousItem = link;
        }
        i = link;
    } 
    return i;
}

char *LinkedListRemove(ListItem *item)
{
    char *i;
    
    if (item == NULL) {
        i = NULL;
    } else {
        i = item->data;
        if (item->previousItem != NULL) {
            if (item->nextItem != NULL) {             // removed item has before and after.
                (item->nextItem)->previousItem = item->previousItem; 
                (item->previousItem)->nextItem = item->nextItem;
            } else {                                  // removed item only has before
                (item->previousItem)->nextItem = NULL;
            }
        } else {                                      // removed item only has after
            if (item->nextItem != NULL) {
                (item->nextItem)->previousItem = NULL;
            }
        }    
    }    
    
    free(item);
    
    return i;
    
}

int LinkedListSize(ListItem *list)
{
    int i = 0, j1, j2;
    
    if (list == NULL) {                       //I didn't use malloc because I can't return NULL
        return 0;
    } else {
        for (;list->previousItem != NULL;) {   //for before parts
            list = list->previousItem;
            i++;
        }
        j1 = i;
        j2 = i;
        for (;j1 > 0; j1--) {                 //move back to original 
            list = list->nextItem;
        }
        
        for (;list->nextItem!= NULL;) {      // for after parts
            list = list->nextItem;
            i++;
        }
        list = LinkedListGetFirst(list);
        
        for (;j2 > 0; j2--) {               //move back to original
            list = list->nextItem;
        }
        return i+1;
    }
}

ListItem *LinkedListGetFirst(ListItem *list)
{
    int num;
    
    if (list == NULL) {
        return NULL;
    } else {                               // move to the first 
        for (;list->previousItem != NULL;) {
            list = list->previousItem;
            num++;
        }
        return list;
    }
    for (; num > 0; num--) {              //go back to the original 
        list = list->nextItem;
    }
}

ListItem *LinkedListGetLast(ListItem *list)
{
    int num;
    
    if (list == NULL) {
        return NULL;
    } else {                              //move to the next 
        for (;list->nextItem != NULL;) {
            list = list->nextItem;
            num++;
        }
        return list;
    }
    for (; num > 0; num--) {              //go back to the original 
        list = list->previousItem;
    }
}

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem)
{
    char *temp;

    if (firstItem == NULL || secondItem == NULL) {
        return STANDARD_ERROR;
    } else {                               // data change only
        temp = firstItem->data;
        firstItem->data = secondItem->data;
        secondItem->data = temp;
        return SUCCESS;
    }
}


int LinkedListPrint(ListItem *list)
{
    int num,counter=0;
    if (list == NULL) {
        return STANDARD_ERROR;
    } else {
        num = LinkedListSize(list);          // i can't use getfirst() because I can't go back to 
        for (;list->previousItem != NULL;) { // the original if i use it.
            list = list->previousItem;
            counter++;
        }
        
        printf("[");
        for (;num > 1 ; num--) {
            printf("%s, ", list->data);
            list = list->nextItem;
        }
        printf("%s", list->data);
        printf("]");
        
        list = LinkedListGetFirst(list);
        for(; counter > 0; counter--) {     // go back to the original.
            list = list->nextItem;
        }
        return SUCCESS;
    }
}