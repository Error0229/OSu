/**
 * Implementation of thread pool.
 */

#include "threadpool.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 10
#define NUMBER_OF_THREADS 3

#define TRUE 1

sem_t full, empty;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// this represents work that has to be
// completed by a thread in the pool
typedef struct {
  void (*function)(void *p);
  void *data;
} task;

// the work queue
task tasks[QUEUE_SIZE];
int r, w;
// the worker bee
pthread_t bees[NUMBER_OF_THREADS];

// insert a task into the queue
// returns 0 if successful or 1 otherwise,
int enqueue(task t) {
  if (tasks[w].function != NULL) {
    return -1;
  }
  tasks[w] = t;
  w = (w + 1) % QUEUE_SIZE;
  return 0;
}

// remove a task from the queue
task dequeue() {
  if (tasks[r].function == NULL) {
    return tasks[r];
  }
  task t = tasks[r];
  tasks[r].function = NULL;
  r = (r + 1) % QUEUE_SIZE;
  return t;
}
// the worker thread in the thread pool
void *worker(void *param) {
  while (TRUE) {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    task work = dequeue();
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    if (work.function == NULL) {
      break;
    }
    execute(work.function, work.data);
  }
  return NULL;
}

/**
 * Executes the task provided to the thread pool
 */
void execute(void (*some_function)(void *p), void *p) { (*some_function)(p); }

/**
 * Submits work to the pool.
 */
int pool_submit(void (*some_function)(void *p), void *p) {
  sem_wait(&empty);
  pthread_mutex_lock(&mutex);
  task work;
  work.function = some_function;
  work.data = p;
  if (enqueue(work) == -1) {
    pthread_mutex_unlock(&mutex);
    return -1;
  }
  pthread_mutex_unlock(&mutex);
  sem_post(&full);
  return 0;
}

// initialize the thread pool
void pool_init(void) {
  sem_init(&full, 0, 0);
  sem_init(&empty, 0, QUEUE_SIZE);
  int i;
  for (i = 0; i < QUEUE_SIZE; i++) {
    tasks[i].function = NULL;
  }
  for (i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_create(&bees[i], NULL, worker, NULL);
  }
}
// shutdown the thread pool
void pool_shutdown(void) {
  int i;
  for (i = 0; i < NUMBER_OF_THREADS; i++) {
    pool_submit(NULL, NULL);
  }
  for (i = 0; i < NUMBER_OF_THREADS; i++) {
    pthread_join(bees[i], NULL);
  }
  sem_destroy(&full);
  sem_destroy(&empty);
}
