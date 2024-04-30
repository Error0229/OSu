#include <pthread.h>
#include <stdio.h>
#include <string.h>
pthread_mutex_t mutex;
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
  pthread_mutex_unlock(&mutex);
  return NULL;
}
int main() {
  pthread_mutex_init(&mutex, NULL);
  int array[1000];
  memset(array, 0, sizeof(array));
  int n;
  printf("Enter a number:");
  scanf("%d", &n);
  pthread_t thread;
  struct fab_params params = {n, array};
  pthread_mutex_lock(&mutex);
  pthread_create(&thread, NULL, f, &params);
  pthread_mutex_lock(&mutex);
  for (int i = 0; i < n; i++) {
    printf("%d ", array[i]);
  }
  puts("");
}
