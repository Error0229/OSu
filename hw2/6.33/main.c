#include <pthread.h>
#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
pthread_mutex_t mutex;
int decrease_count(int count) {
  pthread_mutex_lock(&mutex);
  if (available_resources < count) {
    pthread_mutex_unlock(&mutex);
    return -1;
  } else {
    available_resources -= count;
    pthread_mutex_unlock(&mutex);
    return 0;
  }
}
int increase_count(int count) {
  pthread_mutex_lock(&mutex);
  available_resources += count;
  pthread_mutex_unlock(&mutex);
  return 0;
}
