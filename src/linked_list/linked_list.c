
#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Initialize a new list
void ListNew(LinkedList *list) {
  list->last = NULL;
  list->first = NULL;
  list->length = 0;
}

// Dynamically allocate space for a new Node and save item in the Node
void ListAdd(LinkedList *ll, void *item) {
  Node *newNode = malloc(sizeof(Node));
  assert(newNode != NULL);
	// Create new node 
  newNode->data = item;
	newNode->prev = NULL;
	newNode->next = NULL;

	Node *current = ll->first;
	ll->first = newNode;

	(ll->first)->next = current;
	if (ll->length != 0){
		ll->first->next->prev = ll->first;
	}

	if (ll->length == 0) ll->last = ll->first;
	ll->length++;
}

// Return length of linked list
int ListLen(LinkedList * ll) {
	return ll->length;
}

// Print the contents of the node for debugging purpose
static void PrintList(LinkedList* ll) {
	Node *current = ll->first;
	printf("Values going forward: \n");
	while (current) {
		printf("%s ", ((char *)current->data));
		current = current->next;
	}
	printf("\n");
	current = ll->last;
	printf("Values going backward: \n");
	while (current) {
		printf("%s ", ((char *)current->data));
		current = current->prev;
	}
	printf("\n");
}

int main() {
  LinkedList ll;
  char *i = "sam";
  char *j = "david";
  char *k = "masllow";
  ListNew(&ll);
  ListAdd(&ll, i);
  ListAdd(&ll, j);
  ListAdd(&ll, k);
	PrintList(&ll);
	printf("length of list: %d\n", ListLen(&ll));
}
