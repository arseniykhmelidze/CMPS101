//  File: Graph.c
//  Class: CMPS 101
//  Assignment: PA5
//  Student: Arseniy Khmelidze (akhmelid)
//  Date created: 02/21/17
//  Date modified: 03/09/17
//
//  Copyright © 2017 Arseniy Khmelidze. All rights reserved.
//

#include <stdlib.h>
#include "Graph.h"


// Constructors-Destructors ---------------------------------------------------

// Defining graph object
typedef struct GraphObj
{
    List* adj;
    int* color;
    int* parent;
    int* discover;
    int* finish;
    int order;
    int size;
} GraphObj;


// Graph Constructor
Graph newGraph(int n)
{
    if (n < 1)
    {
        printf("Invalid order in newGraph(). Please inspect your input file. \n");
        exit (1);
    }

    Graph G = malloc(sizeof(GraphObj));
    G -> adj = malloc((n+1) * sizeof(List));
    G -> color = malloc((n+1) * sizeof(int));
    G -> parent = malloc((n+1) * sizeof(int));
    G -> discover = malloc((n+1) * sizeof(int));
    G -> finish = malloc((n+1) * sizeof(int));
    G -> order = n;
    G -> size = 0;
    G -> adj[0] = NULL;

    for (int i = 1; i <= n; i++)
    {
        G -> adj[i] = newList();
        G -> parent[i] = NIL;
        G -> discover[i] = INF;
        G -> color[i] = 'w';
        G -> finish[i] = INF;
    }
    return G;

}


// Graph Destructor
void freeGraph(Graph* pG)
{
    for (int i = 1; i <= getOrder(*pG); i++)
    {
        freeList(&(*pG) -> adj[i]);
        free((*pG) -> adj[i]);
    }

    free((*pG) -> adj);
    free((*pG) -> color);
    free((*pG) -> discover);
    free((*pG) -> parent);

    (*pG) -> adj = NULL;
    (*pG) -> color = NULL;
    (*pG) -> parent = NULL;
    (*pG) -> discover = NULL;
    (*pG) -> finish = NULL;

    free(*pG);
    *pG = NULL;
}



// Access functions -----------------------------------------------------------

// Determining the execution order
int getOrder(Graph G)
{
    if(G == NULL)
    {
        printf("The graph is null, cannot order null graphs. \n");
        exit(1);
    }

    return G -> order;
}


// Determining the size of the graph
int getSize(Graph G)
{
    if(G == NULL)
    {
        printf("The graph is null, cannot get size of null graphs. \n");
        exit(1);
    }

    return G -> size;
}


// Getting parent of a specific node
int getParent(Graph G, int u)
{
    if(G == NULL)
    {
        printf("The graph is null, no parents available. \n");
        exit(1);
    }

    if(u < 1 || u > G -> order)
    {
        printf("Invalid parameters, please try again [via getParent()]. \n");
        exit(1);
    }

    return G -> parent[u];
}


// Discover edge
int getDiscover(Graph G, int u)
{
    if(G == NULL)
    {
        printf("Null graph, cannot get parents. \n");
        exit(1);
    }

    if(u < 1 || u > G -> order)
    {
        printf("Invalid parameters, please try again [via getDiscover()]. \n");
        exit(1);
    }

    return G -> discover[u];
}


// Finish edge discovery
int getFinish(Graph G, int u)
{
    if(G == NULL)
    {
        printf("Null graph, cannot get parents. \n");
        exit(1);
    }

    if(u < 1 || u > G -> order)
    {
        printf("Invalid parameters, please try again [via getFinish()]. \n");
        exit(1);
    }

    return G -> finish[u];
}


// Adding edges
void addEdge(Graph G, int u, int v)
{
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G))
    {
        printf("Graph vertices are out of bounds. \n");
        exit(1);
    }

    addArc(G, u, v);
    addArc(G, v, u);

    G -> size--;
}


// Adding an arc for graph G passing 2 vertices
void addArc(Graph G, int u, int v)
{
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G))
    {
        printf("Graph vertices are out of bounds. \n");
        exit(1);
    }

    List S = G -> adj[u];

    moveFront(S);

    while(index(S) > -1 && v > get(S))
    {
        moveNext(S);
    }

    if(index(S) == -1)
    {
        append(S, v);
    }

    else
    {
        insertBefore(S, v);
    }

    G -> size++;
}


// Visit
void visit(Graph G, List S, int u, int *time)
{
    if (S == NULL || time == NULL)
    {
        printf("Null graph/list passed to visit(). \n");
        exit (1);
    }

    G -> discover[u] = ++(*time);
    G -> color[u] = 'g';

    List adj = G -> adj[u];

    for (advanceTo(adj, 0); index(adj) != -1; moveNext(adj))
    {
        int v = get(adj);

        if (G -> color[v] == 'w')
        {
            G -> parent[v] = u;

            visit(G, S, v, time);
        }
    }

    G -> finish[u] = ++(*time);
    G -> color[u] = 'b';

    prepend(S, u);
}


// DFS function (main algorithm)
void DFS(Graph G, List S)
{
    if (G == NULL)
    {
        printf("Error: Null graph passed. \n");
        exit(1);
    }

    else if (S == NULL)
    {
        printf("Error: Null list passed. \n");
        exit(1);
    }

    else if (length(S) != getOrder(G))
    {
        printf("Error: Invalid list passed. \n");
        exit(1);
    }

    for (int i = 1; i <= getOrder(G); i++)
    {
        G -> color[i] = 'w';
        G -> discover[i] = INF;
        G -> finish[i] = INF;
        G -> parent[i] = NIL;
    }

    int time = 0;
    List T = copyList(S);

    clear(S);

    for (advanceTo(T, 0); index(T) != -1; moveNext(T))
    {
        int u = get(T);

        if (G -> color[u] == 'w')
        {
            visit(G, S, u, &time);
        }
    }

    freeList(&T);
}




/*** Other operations ***/

// Transposing graph G
Graph transpose(Graph G)
{
    if (G == NULL)
    {
        printf("Passed null graph to Transpose. \n");
    }

    Graph T = newGraph(getOrder(G));

    for (int i = 1; i <= getOrder(T); i++)
    {
        List I = G -> adj[i];
        for (advanceTo(I, 0); index(I) != -1; moveNext(I))
        {
            int x = get(I);

            addArc(T, x, i);
        }
    }

    return (T);
}


// Create a copy of graph G
Graph copyGraph(Graph G)
{
    if (G == NULL)
    {
        printf("Null graph passed to CopyGraph(). \n");
    }

    Graph T = newGraph(getOrder(G));

    for (int i = 1; i <= getOrder(G); i++)
    {
        List I = G -> adj[i];

        for (advanceTo(I, 0); index(I) != -1; moveNext(I))
        {
            int x = get(I);

            addArc(T, i, x);
        }
    }

    return (T);
}


// Printing the graph
void printGraph(FILE* out, Graph G)
{
    if (out == NULL)
    {
        exit(1);
    }

    else if (G == NULL)
    {
        exit(1);
    }

    for (int i = 1; i <= getOrder(G); i++)
    {
        fprintf(out, "%d: ", i);
        printList(out,G -> adj[i]);
        fprintf(out, "\n");
    }
}
