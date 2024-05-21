#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define START_SIZE 4
#define DOUBLE 2

/* Initialize stack with allocation from the heap for START_SIZE integers. */
void StackNew(Stack *container) {
  container->elems = malloc(START_SIZE * sizeof(int));
  assert(container->elems != NULL); // Check if memory allocation succeded
  container->logicalLen = 0;
  container->allocLen = START_SIZE;
}

/* Free allocated memory for the stack and reset logical and allocated lengths
 * to 0 */
void StackDispose(Stack *container) {
  free(container->elems);
  container->allocLen = 0;
  container->logicalLen = 0;
}

/* Push ints on the stack. Increase memory by doubling strategy if no space is
 * available.*/
void StackPush(Stack *container, int num) {
  // Need to allocate more memory. Let's use doubling strategy
  if (container->logicalLen >= container->allocLen) {
    container->elems = realloc(container->elems, container->allocLen * DOUBLE);
    container->allocLen *= DOUBLE;
  }
  *(container->elems + container->logicalLen) = num;
  container->logicalLen++;
}

/* Return number of elements on the stack */
int StackLen(Stack *container) { return container->logicalLen; }

int StackPop(Stack *container) {
  // Array indexing start at 0 but logicalLen is 1 ahead
  int res = *(container->elems + container->logicalLen - 1);
  container->logicalLen--;
  return res;
}

int main() {
  Stack stack;
  StackNew(&stack);
  printf("Allocated memory to stack\n");
  // Add 5 items to stack
  for (int i = 0; i < 10; i++) {
    StackPush(&stack, i + 5);
  }
  printf("Length of stack after fill: %d\n", StackLen(&stack));

  printf("Popping off: \n");
  for (int i = 0; i < 5; i++) {
    printf("Popped: %d\n", StackPop(&stack));
    printf("Length of stack: %d\n", StackLen(&stack));
  }
  StackDispose(&stack);
  printf("Disposed stack\n");
  printf("Length of stack after disposal: %d\n", StackLen(&stack));
}
