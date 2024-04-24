#include <pthread.h>
#include <stdio.h>
#include <string.h>
struct fab_params {
  int n;
  int *arr;
};
void *f(void *arg) {
  struct fab_params *params = (struct fab_params *)arg;
  int n = params->n;
  int *arr = params->arr;
  arr[0] = 0;
  arr[1] = 1;
  for (int i = 2; i < n; i++) {
    arr[i] = arr[i - 1] + arr[i - 2];
  }
  return NULL;
}
int main() {
  int array[1000];
  memset(array, 0, sizeof(array));
  int n;
  printf("Enter a number:");
  scanf("%d", &n);
  pthread_t thread;
  struct fab_params params = {n, array};
  pthread_create(&thread, NULL, f, &params);
  pthread_join(thread, NULL);
  for (int i = 0; i < n; i++) {
    printf("%d ", array[i]);
  }
  puts("");
}
