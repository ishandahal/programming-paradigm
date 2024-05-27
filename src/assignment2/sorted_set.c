#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  int *root;
  int logicalLen;
  int allocLen;
  int (*cmpfn)(const void *, const void *);
  int elemSize;
} sortedset;

typedef struct {
  char code[4];
  char *city;
} Airport;

#define NodeSize(elemSize) (2 * sizeof(int) + (elemSize))
#define DOUBLE 2

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

/**
 * Function: FindNode
 * Usage: ip = FindNode(set, elem);
 * if (*ip == -1) printf("ip points where this element belongs!");
 * ------------------
 * FindNode descends through the underlying binary search tree of the
 * specified set and returns the address of the offset into raw storage
 * where the specified element resides. If the specified element isn't
 * in the set, FindNode returns the address of the –1 that would be updated
 * to contain the index of the element being sought if it were the
 * element to be inserted——that is, the address of the –1 that ended
 * the search.
 */
static int *findNode(sortedset *set, const void *elem) {
  int *root = set->root;
  // if (*(set->root) == -1)
  // printf("At root: it's value is -1\n");
  // return current;           // Set is empty, return first slot
	int counter = 0;
  int match, *current;
  while (*root != -1) {
    // printf("Looping ...\n");
		// printf("value of *root: %d\n", *root);
    current =
        (int *)((char *)(set->root + 1) + (*root * NodeSize(set->elemSize)));
    match = set->cmpfn(current, elem);
		// printf("value of match: %d\n", match);
    if (match == 0)
      break;
    root = current + set->elemSize;
    if (match > 0)
      root++;
		if (counter == 1) break;
		counter++;
  }
  return root;
}

/*
 * Function: SetSearch
 * Usage: if (SetSearch(&staffSet, &lecturer) == NULL)
 * printf("musta been fired");
 * -------------------
 * SetSearch searches for the specified client element according
 * the whatever comparison function was provided at the time the
 * set was created. A pointer to the matching element is returned
 * for successful searches, and NULL is returned to denote failure.
 */
void *SetSearch(sortedset *set, const void *elemPtr) {
  int *found = findNode(set, elemPtr);
  // printf("running from setsearch: checking if found something\n");
  if (*found != -1) {
    // printf("running from setsearch: found something\n");
    return (int *)((char *)(set->root + 1) +
                   (*found * NodeSize(set->elemSize)));
  }
  return NULL;
}
/*
 * Function: SetAdd
 * Usage: if (!SetAdd(&friendsSet, &name)) free(name);
 * ----------------
 * Adds the specified element to the set if not already present. If
 * present, the client element is not copied into the set. true
 * is returned if and only if the element at address elemPtr
 * was copied into the set.
 */
bool SetAdd(sortedset *set, const void *elemPtr) {
  int *found = findNode(set, elemPtr);
  // If element is found no need to add it to the set
  if (*found != -1)
    return false;
  // If allocated space is full use doubling strategy to increaase space
  if (set->allocLen == set->logicalLen) {
    set->root =
        realloc(set->root, (NodeSize(set->elemSize) * set->allocLen * DOUBLE) +
                               sizeof(int));
    assert(set->root != NULL);
    set->allocLen *= DOUBLE;
  }
  // Update index where new element is going to be added and update logicalLen
  *found = set->logicalLen++;
  // Compute base address of destination
	printf("Item will be added at index: %d\n", *found);
  int *dest = (int *)((char *)(set->root + 1) + (*found * NodeSize(set->elemSize)));
  memcpy(dest, elemPtr, set->elemSize);
  // Initialize left and right indices of node wiht -1
  *(dest + set->elemSize) = -1;
  *(dest + set->elemSize + 1) = -1;
  return true;
}

int AirportCmp(const void *left, const void *right) {
  Airport *ap1 = (Airport *)left;
  Airport *ap2 = (Airport *)right;
	printf("Comparing: %s with %s\n", ap1->city, ap2->city);
  return strcmp(ap1->code, ap2->code);
}

int main() {
  sortedset s;
  Airport ewr = {.code = "EWR", .city = "newark"};
  Airport ktm = {.code = "KTM", .city = "kathmandu"};
  Airport jfk = {.code = "JFK", .city = "new york"};
  SetNew(&s, sizeof(s), AirportCmp);
  assert(SetSearch(&s, &ewr) == NULL);
  SetAdd(&s, &ewr);
  printf("Added ewr.\n");
  SetAdd(&s, &jfk);
  printf("Added jfk.\n");
	assert(SetSearch(&s, &jfk) != NULL);
  SetAdd(&s, &ktm);
  printf("Added ktm.\n");
  assert(SetSearch(&s, &ktm) != NULL);
  assert(SetSearch(&s, &ktm) != NULL);
  printf("All ran.\n");
}
