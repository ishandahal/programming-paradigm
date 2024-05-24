/**
 * Traverses a properly structured list, and returns the ordered
 * concatenation of all strings, including those in nested sublists.
 *
 * When applied to the two lists drawn above, the following strings
 * would be returned:
 *
 * ConcatAll(gameThree) would return "YankeesDiamondbacks"
 * ConcatAll(nestedNumbers) would return "onethreesix"
 */
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef enum { Integer, String, List, Nil } nodeType;

char *ConcatStr(const char *left, const char *right) {
	// Allocate enough memory for both strings + null character
	char * result = malloc(strlen(left) + strlen(right) + 1);
	if (result == NULL) // Abort if unable to allocate memory
		exit(1); 
	strcpy(result, left);
	strcat(result, right);
	return result;
}

char *ConcatAll(nodeType *list) {
	switch (*list) {
		case Integer:
		case Nil: return strdup("");
		case String: return strdup((char *) (list + 1));
	}
	// nodeType *left_node = (list + 1);
	// nodeType *right_node = (list + 2);
	// Recursively check for strings on both nodes
	char *left_str = ConcatAll(list + 1);
	char *right_str = ConcatAll(list + 2);
	char *str_combined = ConcatStr(left_str, right_str);
	free(left_str);
	free(right_str);

	// nodeType **lists = (nodeType **) (list + 1);
	// nodeType *front_node = lists[0];
	// nodeType *back_node = lists[1];
	return str_combined;
}

int main() {
}
