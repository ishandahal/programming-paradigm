#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/* Linear search key in array. Returns index if found
 * else -1
 * only meant to work for int.
 */
int lsearch(int arr[], int key, int size) {
  for (int i = 0; i < size; i++) {
    if (key == arr[i])
      return i;
  }
  return -1;
}

/* Generic linear search
 * Returns starting address of match else returns null*/
void *generic_lsearch(void *key, void *base, int n, int elem_size,
                      int (*compare_func)(void *, void *)) {
  for (int i = 0; i < n; i++) {
    void * elem_address = (char *)base + (i * elem_size);
    if (compare_func(key, elem_address) == 0)
      return elem_address;
  }
  return NULL;
}

/* Compare twos character arrays. Arguments passed must be pointer to 
* character array. Calls strcmp library function internally
*/
int StrCmp(void *str1, void *str2) {
	char *left = *(char **)str1;
	char *right = *(char **)str2;
	return strcmp(left, right);
}

int compare_ints(void *left, void *right) {
	// Convert arguments to ints and check values
	int *ip1 = left;
	int *ip2 = right;
	return *ip1 - *ip2;
}

int main() {

  // int arr[5] = {1, 4, 5, 3, 6};
  // int key = 3;
	char *strings[] = { "ab", "bc", "cd", "de"};
	char *key = "ab";
	// int lock = 200;
	//
	// printf("%d\n", compare_ints(&key, &lock));

	// Must pass address of pointer (see StrCmp)
	char **result = generic_lsearch(&key, strings, 4, sizeof(char*), StrCmp);
	if (result != NULL)
		printf("Found %s\n", *result);
	else
		printf("Didn't find\n");

  // int i;
  // if ((i = lsearch(arr, key, 5)) != -1)
  //   printf("Found %d at index %d\n", key, i);
  // else
  //   printf("Didn't find %d\n", key);
}
