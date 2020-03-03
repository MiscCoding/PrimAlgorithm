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

typedef struct {
	Edge* heap[EDGE_MAX];
	int count;
} priorityQueue;

void push(priorityQueue* pq, Edge* edge) 
{
	if (pq->count >= EDGE_MAX) return;
	pq->heap[pq->count] = edge;
	int now = pq->count;
	int parent = (pq->count - 1)/2;
	//After adding a new element, construct a heap in acsending order
	while (now > 0 && pq->heap[now]->cost < pq->heap[parent]->cost) {
		swap(pq->heap[now], pq->heap[parent]);
		now = parent;
		parent = (parent - 1) / 2;
	}
	pq->count++;
}

Edge* pop(priorityQueue* pq) {
	if (pq->count <= 0) return NULL;
	Edge* res = pq->heap[0];
	pq->count--;
	pq->heap[0] = pq->heap[pq->count];
	int now = 0, leftChild = 1, rightChild = 2;
	int target = now;
	//After extracting a new element, construct a heap in desending order
	while(leftChild < pq->count)
	{
		if (pq->heap[target]->cost > pq->heap[leftChild]->cost) target = leftChild;
		if (pq->heap[target]->cost > pq->heap[rightChild]->cost&& rightChild < pq->count) target = rightChild;
		else 
		{
			swap(pq->heap[now], pq->heap[target]);
			now = target;
			leftChild = now * 2 + 1;
			rightChild = now * 2 + 2;
		}
    }
	return res;
}

typedef struct Node {
	Edge* data;
	struct Node* next;
}Node;

Node** adj;
int d[NODE_MAX];

void addNode(Node** target, int index, Edge* edge) 
{
	if (target[index] == NULL) {
		target[index] = (Node*)malloc(sizeof(Node));
		target[index]->data = edge;
		target[index]->next = NULL;
	}
	else {
		Node* node = (Node*)malloc(sizeof(Node));
		node->data = edge;
		node->next = target[index];
		target[index] = node;
	}

}