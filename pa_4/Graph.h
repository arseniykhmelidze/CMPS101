//  File: Graph.h
//  Class: CMPS 101
//  Assignment: PA4
//  Student: Arseniy Khmelidze (akhmelid)
//  Date created: 02/25/17
//
//  Copyright © 2017 Arseniy Khmelidze. All rights reserved.
//

#include <stdio.h>
#include "List.h"

#ifndef PA_4_LIST_H
#define PA_4_LIST_H
#define NIL -1
#define INF -2


typedef struct GraphObj * Graph;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n);
void freeGraph(Graph* pG);


// Access functions -----------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);


// Manipulation procedures ----------------------------------------------------
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);


// Other operations -----------------------------------------------------------
void printGraph(FILE* out, Graph G);

#endif
