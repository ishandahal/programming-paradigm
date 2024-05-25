#include <assert.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int *root;
  int logicalLen;
  int allocLen;
  int (*cmpfn)(const void *, const void *);
  int elemSize;
} sortedset;

#define NodeSize(elemSize) (2 * sizeof(int) + (elemSize))

/*
 * Function: SetNew
 * Usage: SetNew(&stringSet, sizeof(char *), StringPtrCompare);
 * SetNew(&constellations, sizeof(pointT), DistanceCompare);
 * ----------------
 * SetNew allocates the requisite space needed to manage what
 * will initially be an empty sorted set. More specifically, the
 * routine allocates space to hold up to 'kInitialCapacity' (currently 4)
 * client elements.
 */
static const int kInitialCapacity = 4;
void SetNew(sortedset *set, int elemSize,
            int (*cmpfn)(const void *, const void *)) {
  assert(cmpfn != NULL);
  set->cmpfn = cmpfn; // Link the comparison function
  assert(elemSize > 0);
  // Allocate enough memory for odd intial int plus default capacity
  set->root = malloc(sizeof(int) + kInitialCapacity * NodeSize(elemSize));
  assert(set->root != NULL);
	*(set->root) = -1; // set is empty when initialized
	set->logicalLen = 0;
	set->allocLen = kInitialCapacity;
	set->elemSize = elemSize;
}

int dummy_cmpfunc(const void* left, const void* right) {
	return -1;
}

int main() {
	sortedset s;
	SetNew(&s, sizeof(s), dummy_cmpfunc);
}
