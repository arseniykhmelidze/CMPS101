//  File: FindPath.c
//  Class: CMPS 101
//  Assignment: PA4
//  Student: Arseniy Khmelidze (akhmelid)
//  Date created: 02/26/17
//
//  Copyright © 2017 Arseniy Khmelidze. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main (int argc, char* argv[])
{

    // check arguments
    if (argc != 3)
    {
        printf("Please provide exactly 2 files: input and output. \n");
        exit (1);
    }

    // read arguments
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

    // look for size.
    int vert;
    fscanf(in, "%d", &vert);
    Graph G = newGraph(vert);

    // read edges
    int first,second;
    while (fscanf(in, "%d %d", &first, &second) == 2)
    {
        if (first == 0 && second == 0)
        {
        	break;
        }

        addEdge(G,first,second);
    }

    //print graph
    printGraph(out, G);


    List L = newList();
    int source, dest;

    // read all the lines of the input file
    while (fscanf(in, "%d %d", &source, &dest))
    {
        if (source == 0 && dest == 0)
        {
            break;
        }

        BFS(G, source);
        getPath(L, G, dest);

        if (length(L) == 0)
        {
            fprintf(out, "\nThe distance from %d to %d is ∞. \n", source, dest);
            fprintf(out, "No %d-%d path exists\n", source, dest);
        }

        else
        {
            fprintf(out, "\nThe distance from %d to %d is %d \n", source, dest, getDist(G, dest));
            fprintf(out, "A shortest %d-%d path is: ", source, dest);
            printList(out, L);
            fprintf(out, "\n");
        }
        clear(L);
    }

    // Release everything from the memory to exclude memory leaks
    freeGraph(&G);
    freeList(&L);
    fclose(in);
    fclose(out);
}

