//  File: List.c
//  Class: CMPS 101
//  Assignment: PA5
//  Student: Arseniy Khmelidze (akhmelid)
//  Date created: 02/21/17
//
//  Copyright © 2017 Arseniy Khmelidze. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "List.h"


// Defining Node object
typedef struct NodeObject
{
    int data;
    struct NodeObject *next;
    struct NodeObject *previous;
} NodeObject;




// Creating List structure using Node
typedef NodeObject* Node;
typedef struct ListObject
{
    Node front;
    Node back;
    Node cursor;
    int index;
    int length;
} ListObject;


Node newNode(int d)
{
    Node new_node = malloc(sizeof(NodeObject));

    new_node -> data = d;
    new_node -> previous = NULL;
    new_node -> next = NULL;

    return (new_node);
}


void freeNode(Node *n)
{
    if (n != NULL && *n != NULL)
    {
        free(*n);
        *n = NULL;
    }
}


List newList(void)
{
    List L = malloc(sizeof(ListObject));

    L -> front = NULL;
    L -> back = NULL;
    L -> cursor = NULL;
    L -> index = -1;
    L -> length = 0;

    return L;
}


void freeList(List* pL)
{
    if(*pL != NULL && pL != NULL)
    {
        Node n = (*pL) -> front;

        while(n != NULL)
        {
            Node temp = n;
            n = n -> next;
            free(temp);
        }

        free(*pL);
        *pL = NULL;
    }
}




// Access functions -----------------------------------------------------------

int length(List L)
{
    return L -> length;
}


int index(List L)
{
    return L -> index;
}


int front(List L)
{
    if (L -> length > 0)
    {
        return L -> front -> data;
    }

    return -1;
}


int back(List L)
{
    if (L -> length > 0)
    {
        return L -> back -> data;
    }
    return -1;
}


int get(List L)
{
    if (L -> length > 0)
    {
        return L -> cursor -> data;
    }
    return -1;
}


int equals(List A, List B)
{
    Node listA = A -> front;
    Node listB = B -> front;

    if (A -> length != B -> length)
    {
        return 0;
    }

    if (A -> back -> data != B -> back -> data)
    {
        return 0;
    }

    while (listA -> next != NULL)
    {
        if (listA -> data != listB -> data)
        {
            return 0;
        }

        listA = listA -> next;
        listB = listB -> next;
    }

    return 1;
}


void advanceTo(List L, int i)
{
    if(L == NULL)
    {
        printf("Calling advanceTo() on an empty list. \n");
        exit(1);
    }

    if(i >= 0 && i <= (length(L) - 1))
    {
        int j = 0;
        L -> cursor = L -> front;

        while (i > 0)
        {
            L -> cursor = L -> cursor -> next;
            i--;
            j++;
        }

        L -> index = j;
    }

    else if(i == (length(L) - 1))
    {
        L -> cursor = L -> back;
        L -> index = (length(L) - 1);
    }

    else
    {
    	L -> cursor = NULL;
    }
}


// Manipulation procedures ----------------------------------------------------
void clear(List L)
{
    if(L -> front == NULL)
    {
    	return;
    }

    else
    {
        Node temp = L -> front;

        while(temp != NULL)
        {
            Node x = temp -> next;
            free(temp);
            temp = x;
        }

        L -> front = NULL;
        L -> back = NULL;
        L -> cursor = NULL;
        L -> length = 0;
    }
}


void moveFront(List L)
{
    if (L -> length > 0)
    {
        L -> cursor = L -> front;
        L -> index = 0;
    }
}


void moveBack(List L)
{
    if (L -> length > 0)
    {
        L -> cursor = L -> back;
        L -> index = L -> length - 1;
    }
}


void movePrev(List L)
{
    if (L -> cursor != NULL && L -> cursor != L -> front)
    {
        L -> cursor = L -> cursor -> previous;
        --L -> index;
    }

    else if (L -> cursor != NULL && L -> cursor == L -> front)
    {
        L -> cursor = NULL;
        L -> index = -1;
    }

    else
    {
        return;
    }
}


void moveNext(List L)
{
    if (L -> cursor != NULL && L -> cursor != L -> back)
    {
        L -> cursor = L -> cursor -> next;
        ++L -> index;
    }

    else if (L -> cursor != NULL && L -> cursor == L -> back)
    {
        L -> cursor = NULL;
        L -> index = -1;
    }

    else
    {
        return;
    }
}


void prepend(List L, int data)
{
    Node newnode = newNode(data);

    if (L -> length > 0)
    {
        (newnode) -> next = L -> front;
        L -> front -> previous = (newnode);
        L -> front = (newnode);

        ++L -> length;
        ++L -> index;
    }

    else
    {
        L -> front = newnode;
        L -> back = newnode;

        ++L -> length;
        ++L -> index;
    }
}


void append(List L, int data)
{
    Node newnode = newNode(data);

    if (L -> length > 0)
    {
        (newnode) -> previous = L -> back;
        L -> back -> next = (newnode);
        L -> back = (newnode);
    }

    else
    {
        L -> front = (newnode);
        L -> back = (newnode);
    }

    ++L -> length;
}


void insertBefore(List L, int data)
{
    if (L -> length > 0 && L -> index >= 0)
    {
        if (L -> length <= 0)
        {
            printf("Cannot insert before - list is empty. \n");
            exit (1);
        }

        if (L -> index < 0)
        {
            printf("Cannot insert before - cursor undefined. \n");
            exit (1);
        }

        else if (L -> cursor == L -> front)
        {
            prepend(L, data);
        }

        else
        {
            Node newnode = newNode(data);

            newnode -> previous = L -> cursor -> previous;
            newnode -> next = L -> cursor;

            L -> cursor -> previous -> next = newnode;
            L -> cursor -> previous = newnode;
            L -> index++;
            L -> length++;
        }
    }

}


void insertAfter(List L, int data)
{
    if (L -> length > 0 && L -> index >= 0)
    {
    	if (L -> cursor -> next == NULL)
    	{
    		append(L, data);
    	}

    	else
    	{
    		Node newnode = newNode(data);
    		newnode -> previous = L -> cursor;
    		newnode -> next = L -> cursor -> next;

    		L -> cursor -> next -> previous = newnode;
    		L -> cursor -> next = newnode;
    		L -> length++;
    	}
    }
}


void deleteFront(List L)
{
    if(length(L) == 0)
    {
        fprintf(stderr, "Cannot delete front - list is empty. \n");
        exit(EXIT_FAILURE);
    }

    else if(L == NULL)
    {
        fprintf(stderr, "Cannot delete front - list is null. \n");
        exit(EXIT_FAILURE);
    }

    else
    {
        if(length(L) > 1)
        {
            L -> front = L -> front -> next;
            freeNode(&L -> front -> previous);
            L -> front -> previous = NULL;
        }

        else
        {
            freeNode(&L -> front);
        	L -> front = L -> back = NULL;
        }
    }

    L -> length--;
}


void deleteBack(List L)
{
    if(length(L) == 0)
    {
        fprintf(stderr,"Cannot delete back - list is empty. \n");
        exit(EXIT_FAILURE);
    }

    else if(L == NULL)
    {
        fprintf(stderr,"Cannot insert before - list is null. \n");
        exit(EXIT_FAILURE);
    }

    else
    {
        if(length(L) > 1)
        {
            L -> back = L -> back -> previous;
            freeNode(&L -> back -> next);
            L -> back -> next = NULL;
        }

        else
        {
            freeNode(&L -> front);
        	L -> front = L -> back = NULL;
        }
    }

    L -> length--;
}


void delete(List L)
{
    if (L -> length > 0 && L -> index >= 0)
    {
        if(L -> cursor == L -> back)
        {
            deleteBack(L);
        }

        else if (L -> cursor == L -> front)
        {
            deleteFront(L);
        }

        else
        {
            L -> cursor -> next -> previous = L -> cursor -> previous;
            L -> cursor -> previous -> next = L -> cursor -> next;

            freeNode(&L -> cursor);

            L -> index = -1;
            L -> cursor = NULL;

            --L -> length;
        }
    }
}




// Other operations -----------------------------------------------------------
void printList(FILE* out, List L)
{
    if (L == NULL)
    {
        printf("List Error: calling printList() on NULL List reference. \n");
        exit(1);
    }

    Node N = NULL;

    if (out == NULL)
    {
        out = stdout;
    }

    for (N = L -> front; N != NULL; N = N->next)
    {
        fprintf(out, "%d ", N->data);
    }

    printf("\n");
}


List copyList(List L)
{
    List temp_list = newList();
    Node temp_node = L -> front;

    while (temp_node -> next != NULL)
    {
        append(temp_list, temp_node -> data);
        temp_node = temp_node -> next;
    }

    append(temp_list, temp_node -> data);

    return temp_list;
}
