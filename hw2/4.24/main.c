#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int outer_count, inside_count;
void *monte_carlo(void *arg) {
  int n = *(int *)arg;
  for (int i = 0; i < n; i++) {
    double x = (double)rand() / RAND_MAX;
    double y = (double)rand() / RAND_MAX;
    if (x * x + y * y <= 1) {
      outer_count++;
    }
    inside_count++;
  }
  return NULL;
}
int main() {
  int n;
  printf("Enter number of points want to generate: ");
  scanf("%d", &n);
  pthread_t thread[10];
  n /= 10;
  int i;
  outer_count = inside_count = 0;
  for (i = 0; i < 10; i++) {
    pthread_create(&thread[i], NULL, monte_carlo, &n);
  }
  for (i = 0; i < 10; i++) {
    pthread_join(thread[i], NULL);
  }
  printf("Pi is approximately: %lf\n", 4.0 * outer_count / inside_count);
}
