//  File: GraphTest.c
//  Class: CMPS 101
//  Assignment: PA5
//  Student: Arseniy Khmelidze (akhmelid)
//  Date created: 02/21/17
//
//  Copyright © 2017 Arseniy Khmelidze. All rights reserved.
//


#include<stdio.h>
#include "List.h"
#include "Graph.h"

int main(void)
{
    List L = newList();
    Graph G = newGraph(8);
    Graph Transpose;
    Graph Copy;

    printf("Graph order : %d\n",getOrder(G));
    printf("Graph size : %d\n",getSize(G));

    addArc(G,1,2);
    addArc(G,2,3);
    addArc(G,2,5);
    addArc(G,2,6);
    addArc(G,3,4);
    addArc(G,3,7);
    addArc(G,4,3);
    addArc(G,4,8);
    addArc(G,5,1);
    addArc(G,5,6);
    addArc(G,6,7);
    addArc(G,7,6);
    addArc(G,7,8);
    addArc(G,8,8);

    printf("\nAfter adding arcs..");


    printf("\n\nGraph order :  %d\n",getOrder(G));
    printf("Graph size :%d\n",getSize(G));
    printGraph(stdout,G);


    Transpose = transpose(G);
    printf("\n\nTranspose of G\n");
    printGraph(stdout, Transpose);


    Copy = copyGraph(G);
    printf("\n\nCopy of G\n");
    printGraph(stdout,Copy);


    int i;
    for(i = 1; i <= getOrder(G); i++)
    {
        append(L, i);
    }
    printf("\n\nList S\n");
    printList(stdout, L);


    DFS(G, L);
    printf("\n\nafter DFS\n");
    printf("List S\n");
    printList(stdout, L);


    i = back(L);
    printf("\nBack of List S: %d\n",i);


    i = front(L);
    printf("\nFront of List S: %d\n",i);


    advanceTo(L, length(L) - 1);
    i = get(L);
    printf("\nCurrent last element: %d\n",i);


    printf("\nDFS with Tranpose(G)\n");
    DFS(Transpose, L);
    printf("\nafter DFS\n");
    printf("\nList S\n");
    printList(stdout, L);

    return 0;
}
