#include "stack.h"
#include <stdlib.h>

#define START_SIZE 4

/* Initialize stack with allocation from the heap for START_SIZE integers. */
void StackNew(Stack *container) {
	container->elems = malloc(START_SIZE * sizeof(int));
	container->logicalLen = 0;
	container->allocLen = START_SIZE;
}

int main() {
	Stack stack;

}
