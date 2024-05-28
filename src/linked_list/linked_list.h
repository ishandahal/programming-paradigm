/*
* Implementation of generic doubly linked list
*/

#ifndef LINKED_LIST
#define LINKED_LIST
typedef struct Node {
	void *data;
	struct Node *next;
} Node;

typedef struct {
	Node *first;
	Node *last;
	int length;
} LinkedList;

void ListNew(LinkedList *);
void ListAdd(LinkedList *, void *item);
#endif
