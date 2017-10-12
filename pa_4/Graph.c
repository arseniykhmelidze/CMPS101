//  File: Graph.c
//  Class: CMPS 101
//  Assignment: PA4
//  Student: Arseniy Khmelidze (akhmelid)
//  Date created: 02/25/17
//
//  Copyright © 2017 Arseniy Khmelidze. All rights reserved.
//

#include <stdlib.h>
#include "Graph.h"


// Defining graph object
typedef struct GraphObj
{
    int source;
    List* adj;
    int* distance;
    char* color;
    int* parent;
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
    G -> source = NIL;
    G -> adj = malloc((n+1) * sizeof(List));
    G -> distance = malloc((n+1) * sizeof(int));
    G -> color = malloc((n+1) * sizeof(int));
    G -> parent = malloc((n+1) * sizeof(int));
    G -> order = n;
    G -> size = 0;
    G -> adj[0] = NULL;

    for (int i = 1; i <= n; i++)
    {
        G -> adj[i] = newList();
        G -> parent[i] = NIL;
        G -> distance[i] = INF;
        G -> color[i] = 'w';
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
    free((*pG) -> distance);
    free((*pG) -> parent);

    (*pG) -> adj = NULL;
    (*pG) -> color = NULL;
    (*pG) -> parent = NULL;
    (*pG) -> distance = NULL;

    free(*pG);
    *pG = NULL;
}

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


// Determining the source of the graph
int getSource(Graph G)
{
    if(G == NULL)
    {
        printf("The graph is null, no source available. \n");
        exit(1);
    }

    return G -> source;
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
        printf("Invalid parameters, please try again [getParent()]. \n");
        exit(1);
    }

    return G -> parent[u];
}


// Getting distance from source to destination
int getDist(Graph G, int u)
{
    if(G == NULL)
    {
        printf("The graph is null, cannot determine distance. \n");
        exit(1);
    }

    if(G -> source == 0)
    {
        return -1;
    }

    return G -> distance[u];
}


// getting path for a specific vertex
void getPath(List L, Graph G, int u)
{
    if (getSource(G) == NIL)
    {
        printf("F-n getPath() was called before BFS(). Terminating program. \n");
        exit (1);
    }

    if (G -> source == u)
    {
        append(L, u);
    }

    else if (G -> parent[u] != NIL)
    {
        getPath(L, G, G -> parent[u]);
        append(L, u);
    }
}


// Nullifying graph
void makeNull(Graph G)
{
    if (G != NULL)
    {
        for (int i = 1; i <= getOrder(G); i++)
        {
            clear(G -> adj[i]);
        }

        G -> size = 0;
    }

    else
    {
        printf("makeNull() called on a NULL Graph pointer. \n");
        exit(1);
    }
}


// add edge passing two vertices into the passed graph
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


// BFS (Breadth First Search)
void BFS(Graph G, int s)
{
    for(int i = 0; i < (G -> order + 1); ++i)
    {
        G -> parent[i] = NIL;
        G -> distance[i] = INF;
        G -> color[i] = 'w';
    }

    G -> source = s;
    G -> distance[s] = 0;
    G -> color[s] = 'g';

    List Q = newList();
    prepend(Q, s);

    while(length(Q) > 0)
    {
        int temp = back(Q);
        deleteBack(Q);

        List adj = G -> adj[temp];
        moveFront(adj);

        while(index(adj) > -1)
        {
            int v = get(adj);

            if(G->color[v] == 'w')
            {
                G -> color[v] = 'g';
                G -> parent[v] = temp;
                G -> distance[v] = G -> distance[temp] + 1;
                prepend(Q, v);
            }
            moveNext(adj);
        }
    }

    freeList(&Q);
}




/*** Other operations ***/

// Printing the graph
void printGraph(FILE* out, Graph G)
{
    setbuf(out, NULL);

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
        fprintf(out, "%d:", i);
        printList(out,G -> adj[i]);
        fprintf(out, "\n");
    }
}
