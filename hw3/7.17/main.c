#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int inside_count;
pthread_mutex_t mutex;
void *monte_carlo(void *arg) {
  int n = *(int *)arg;
  for (int i = 0; i < n; i++) {
    double x = (double)rand() / RAND_MAX;
    double y = (double)rand() / RAND_MAX;
    if (x * x + y * y <= 1) {
      pthread_mutex_lock(&mutex);
      inside_count++;
      pthread_mutex_unlock(&mutex);
    }
  }
  return NULL;
}
int main() {
  int n;
  printf("Enter number of points want to generate: ");
  scanf("%d", &n);
  pthread_mutex_init(&mutex, NULL);
  pthread_t thread[10];
  int i;
  int arg = n / 10;
  inside_count = 0;
  for (i = 0; i < 10; i++) {
    pthread_create(&thread[i], NULL, monte_carlo, &arg);
  }
  for (i = 0; i < 10; i++) {
    pthread_join(thread[i], NULL);
  }
  printf("Pi is approximately: %lf\n", 4. * inside_count / n);
}
