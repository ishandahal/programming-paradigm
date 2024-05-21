
typedef struct {
	int *elems;
	int logicalLen;
	int allocLen;
} Stack;

void StackNew(Stack *);
void StackDispose(Stack *);
void StackPush(Stack *, int);
int StackPop(Stack *);
