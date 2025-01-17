//  File: FindComponents.c
//  Class: CMPS 101
//  Assignment: PA4
//  Student: Arseniy Khmelidze (akhmelid)
//  Date created: 02/21/17
//
//  Copyright © 2017 Arseniy Khmelidze. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Please provide exactly 2 files: input and output. \n");
        exit (1);
    }

    // Opening read/write files
    FILE *in, *out;
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if (in == NULL)
    {
        printf("Unable to open read file(s). \n", argv[1]);
        exit(1);
    }

    if (out == NULL)
    {
        printf("Unable to open write file(s). \n", argv[2]);
        exit(1);
    }

    // Graph size determination
    int size;
    fscanf(in, "%d", &size);
    Graph G = newGraph(size);


    // Edge determination
    int first_edge;
    int second_edge;
    while (fscanf(in, "%d %d", &first_edge, &second_edge) == 2)
    {
        if (first_edge == 0 && second_edge == 0)
        {
        	break;
        }

        addArc(G, first_edge, second_edge);
    }

    // Printing the list representation of graph
    fprintf(out, "Adjacency list representation of G: \n");
    printGraph(out, G);

    List L = newList();

    for (int i = 1; i <= getOrder(G); i++)
    {
        append(L, i);
    }

    DFS(G, L);

    Graph T = transpose(G);

    DFS(T, L);

    // Strongly connected components determination
    int count = 0;

    for (int i = 1; i <= getOrder(G); i++)
    {
        if(getParent(T, i) == NIL)
        {
            count++;
        }
    }

    // Reversing components
    fprintf(out, "\nG contains %d strongly connected components:\n", count);

	List stack = newList();

	for (int i = 1; i<= count; i++)
	{
		fprintf(out, "Component %d: ", i);

		while(getParent(T, back(L)) != NIL)
		{
			prepend(stack, back(L));
			deleteBack(L);
		}

		prepend(stack, back(L));
		deleteBack(L);

		printList(out, stack);
		fprintf(out, "\n");

		clear(stack);
	}

    // Releasing the memory
    freeGraph(&G);
    freeGraph(&T);

    freeList(&L);
    freeList(&stack);

    fclose(in);
    fclose(out);
}
