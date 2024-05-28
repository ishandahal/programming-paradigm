
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
  newNode->data = item;
	newNode->next = NULL;
  if (ll->length == 0) {
    ll->first = newNode;
    ll->last = newNode;
		ll->length++;
		return;
  }
	Node *current = ll->first;
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = newNode;
	ll->last = current->next;
	ll->length++;
}

// Print the contents of the node for debugging purpose
static void PrintList(LinkedList* ll) {
	Node *current = ll->first;
	while (current) {
		printf("Value at current node: %d\n", *((int *)current->data));
		current = current->next;
	}
}

int main() {
  LinkedList ll;
  int i = 23;
  ListNew(&ll);
  ListAdd(&ll, &i);
  ListAdd(&ll, &i);
  ListAdd(&ll, &i);
	PrintList(&ll);
	printf("length of list: %d\n", ll.length);
}
