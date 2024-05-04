#include "buffer.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
buffer_item buffer[BUFFER_SIZE];
sem_t empty, full;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int r, w;
int insert_item() {
  if (buffer[w] != -1) {
    return -1;
  }
  buffer[w] = rand() % 100;
  w = (w + 1) % BUFFER_SIZE;
  return 0;
}
int remove_item() {
  if (buffer[r] == -1) {
    return -1;
  }
  buffer[r] = -1;
  r = (r + 1) % BUFFER_SIZE;
  return 0;
}

void *producer(void *arg) {
  while (1) {
    sleep(rand() % 5 + 1);
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    if (insert_item() == -1) {
      printf("Error\n");
      exit(1);
    }
    printf("Producer produced an item\n");
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
  }
}

void *consumer(void *arg) {
  while (1) {
    sleep(rand() % 5 + 1);
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    if (remove_item() == -1) {
      printf("Error\n");
      exit(1);
    }
    printf("Consumer consumed an item\n");
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
  }
}
int main(int argc, char *argv[]) {
  int sleep_time = atoi(argv[1]);
  int producer_count = atoi(argv[2]);
  int consumer_count = atoi(argv[3]);
  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);
  for (int i = 0; i < BUFFER_SIZE; i++) {
    buffer[i] = -1;
  }
  r = w = 0;
  pthread_t producers[producer_count], consumers[consumer_count];
  for (int i = 0; i < producer_count; i++) {
    pthread_create(&producers[i], NULL, producer, NULL);
  }
  for (int i = 0; i < consumer_count; i++) {
    pthread_create(&consumers[i], NULL, consumer, NULL);
  }
  sleep(sleep_time);
  return 0;
}
