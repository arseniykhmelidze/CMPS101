//  File: List.c
//  Class: CMPS 101
//  Assignment: PA2
//  Student: Arseniy Khmelidze (akhmelid)
//  Date created: 01/23/17
//
//  Copyright © 2017 Arseniy Khmelidze. All rights reserved.
//

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
typedef NodeObject *Node;
typedef struct ListObject
{
    Node front;
    Node back;
    Node cursor;
    int index;
    int length;

} ListObject;


void freeNode(Node *n)
{
    if (n != NULL && *n != NULL)
    {
        free(*n);
        *n = NULL;
    }
}


Node newNode(int d)
{
    Node n = malloc(sizeof(NodeObject));
    n -> data = d;
    n -> previous = NULL;
    n -> next = NULL;
    return (n);
}


List newList(void)
{
    List temp = malloc(sizeof(ListObject));
    temp -> front = temp -> back = temp -> cursor = NULL;
    temp -> index = -1;
    temp -> length = 0;
    return temp;
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




// Manipulation procedures ----------------------------------------------------
void clear(List L)
{
    if(L == NULL)
    {
        printf("The list is empty.");
        return;
    }

    Node temp = L -> front;

    while(temp != NULL)
    {
        Node x = temp;
        temp = temp -> next;
        free(x);
    }

    L -> front = NULL;
    L -> back = NULL;
    L -> cursor = NULL;
    L -> length = 0;
    L -> index = -1;
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
        ++L -> length;

    }

    else
    {
        L -> front = (newnode);
        L -> back = (newnode);
        ++L -> length;
    }
}

void insertBefore(List L, int data)
{
    if (L -> length > 0 && L -> index >= 0)
    {
        Node newnode = newNode(data);
        (newnode) -> data = data;
        (newnode) -> previous = L -> cursor -> previous;
        (newnode) -> next = L -> cursor;
        L -> cursor -> previous -> next = (newnode);
        L -> cursor -> previous = (newnode);
        ++L -> index;
        ++L -> length;
        // L -> length += 1
    }
}

void insertAfter(List L, int data)
{
    if (L -> length > 0 && L -> index >= 0)
    {
        Node newnode = newNode(data);
        (newnode) -> data = data;
        (newnode) -> next = L -> cursor -> next;
        (newnode) -> previous = L -> cursor;
        L -> cursor -> next = (newnode);
        ++L -> length;
    }
}

void deleteFront(List L)
{
    Node x = *&(L -> front);

    printf(" deleting %d", x -> data);
    fflush(stdout);

    if (L -> length > 1)
    {
        L -> front = L -> front -> next;
        freeNode(&x);
    }

    else
    {
        free(&(L -> front));
        L -> front = L -> back = NULL;
    }
    --L -> length;

    printf(" the new length is %d \n", L -> length);
    fflush(stdout);
}

void deleteBack(List L)
{
    Node x = *&(L -> back);

    if (L -> length > 1)
    {
        L -> back = L -> back -> previous;
        freeNode(&x);
    }
    else
    {
        free(&(L -> back));
        L -> front = L -> back = NULL;
    }

    --L -> length;
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
            Node temp = L -> cursor;
            L -> cursor -> next -> previous = L -> cursor -> previous;
            L -> cursor -> previous -> next = L -> cursor -> next;

            freeNode(&temp);

            L -> index = -1;
            L -> cursor = NULL;

            --L -> length;
        }
    }
}




// Other operations -----------------------------------------------------------

void printList(FILE *out, List L)
{
    Node temp = L -> front;


    if(out == NULL)
    {
        for (int i = 0; i < L -> length; i++)
        {
            printf(" %d ", temp -> data);
            temp = temp -> next;
        }
    }

    else
    {
        for (int i = 0; i < L -> length; i++)
        {
            fprintf(out," %d ", temp -> data);
            temp = temp -> next;
        }
    }
}

List copyList(List L)
{
    List temp = newList();
    Node tempNode = L -> front;

    while (tempNode -> next != NULL)
    {
        append(temp, tempNode -> data);
        tempNode = tempNode -> next;
    }

    append(temp, tempNode -> data);

    return temp;
}
