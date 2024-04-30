#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
pthread_mutex_t 🔐 =
    PTHREAD_MUTEX_INITIALIZER; // normal mutex for north farmers
pthread_mutex_t 🔏 =
    PTHREAD_MUTEX_INITIALIZER; // normal mutex for south farmers
pthread_mutex_t 🌉 = PTHREAD_MUTEX_INITIALIZER; // mutex for the bridge lock

int N = 0; // the count of North farmers on the bridge
int S = 0; // the count of South farmers on the bridge

void *north_to_south(void *arg) {
  pthread_mutex_lock(&🔐);
  N++;
  // First farmer ought to lock the bridge
  if (N == 1)
    pthread_mutex_lock(&🌉);
  pthread_mutex_unlock(&🔐);

  // Farmer crossing the bridge
  printf("A North farmer crossing the bridge.\n");
  sleep(rand() % 5); // simulate the time taken to cross the bridge
  pthread_mutex_lock(&🔐);
  N--;
  // Last farmer ought to release the bridge's lock
  if (N == 0)
    pthread_mutex_unlock(&🌉);
  pthread_mutex_unlock(&🔐);

  return NULL;
}

void *south_to_north(void *arg) {
  pthread_mutex_lock(&🔏);
  S++;
  // First farmer ought to lock the bridge
  if (S == 1)
    pthread_mutex_lock(&🌉);
  pthread_mutex_unlock(&🔏);

  // Farmer crossing the bridge
  printf("A South farmer crossing the bridge.\n");
  sleep(rand() %
        5); // simulate the time taken to cross the bridge (up to 3 seconds

  pthread_mutex_lock(&🔏);
  S--;
  // Last farmer ought to release the bridge's lock
  if (S == 0)
    pthread_mutex_unlock(&🌉);
  pthread_mutex_unlock(&🔏);

  return NULL;
}

int main() {
  int n;
  printf("Enter the number of farmers: ");
  scanf("%d", &n);
  pthread_t threads[1000];
  if (n > 1000) {
    printf("Too many farmers! Exiting...\n");
    return 1;
  }
  int i;
  for (i = 0; i < n; i++) {
    if (rand() % 2 == 0) {
      pthread_create(&threads[i], NULL, north_to_south, NULL);
    } else {
      pthread_create(&threads[i], NULL, south_to_north, NULL);
    }
  }

  for (i = 0; i < n; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
