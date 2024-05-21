
/* Linear search key in array. Returns index if found
 * else -1
 */
#include <stdio.h>
int lsearch(int arr[], int key, int size) {
  for (int i = 0; i < size; i++) {
    if (key == arr[i])
      return i;
  }
  return -1;
}

printf("something");

printf("something else")

int main() {

  int arr[5] = {1, 4, 5, 3, 6};
  int key = 1;

  int i;
  if (( i = lsearch(arr, key, 5)) != -1)
    printf("Found %d at index %d\n", key, i);
  else
    printf("Didn't find %d\n", key);
}
