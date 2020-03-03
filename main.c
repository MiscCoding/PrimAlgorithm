#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NODE_MAX 1001
#define EDGE_MAX 200001 //Bi directional egde line 100,000

typedef struct {
	int cost;
	int node;
} Edge;

void swap(Edge* a, Edge* b) 
{
	Edge temp;
	temp.cost = a->cost;
	temp.node = a->node;

	a->cost = b->cost;
	a->node = b->node;
	b->cost = temp.cost;
	b->node = temp.node;
}