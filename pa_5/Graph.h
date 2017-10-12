//  File: Graph.h
//  Class: CMPS 101
//  Assignment: PA5
//  Student: Arseniy Khmelidze (akhmelid)
//  Date created: 02/21/17
//  Date modified: 03/09/17
//
//  Copyright © 2017 Arseniy Khmelidze. All rights reserved.
//

#include <stdio.h>
#include "List.h"

#ifndef PA_5_LIST_H
#define PA_5_LIST_H
#define NIL -1
#define INF -2


typedef struct GraphObj * Graph;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n);
void freeGraph(Graph* pG);


// Access functions -----------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */


// Manipulation procedures ----------------------------------------------------
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void visit(Graph G, List S, int u, int *time);
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */


// Other operations -----------------------------------------------------------
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out , Graph G);

#endif
