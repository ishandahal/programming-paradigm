typedef struct{
	int *root;
	int logicalLen;
	int allocLen;
	int (*cmpfn) (void *, void *);
	int elemSize;
} sortedset;

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
 int (*cmpfn)(const void *, const void *));
