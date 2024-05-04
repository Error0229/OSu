#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 5
int dishes;
enum { THINKING, HUNGRY, EATING } state[NUM_PHILOSOPHERS];
pthread_cond_t self[NUM_PHILOSOPHERS];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void test(int philosopher_number) {
  if (state[philosopher_number] == HUNGRY &&
      state[(philosopher_number + 1) % NUM_PHILOSOPHERS] != EATING &&
      state[(philosopher_number + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS] !=
          EATING) {
    state[philosopher_number] = EATING;
    pthread_cond_signal(&self[philosopher_number]);
  }
}
void pickup_forks(int philosopher_number) {
  pthread_mutex_lock(&mutex);
  state[philosopher_number] = HUNGRY;
  test(philosopher_number);
  while (state[philosopher_number] != EATING) {
    pthread_cond_wait(&self[philosopher_number], &mutex);
  }
  pthread_mutex_unlock(&mutex);
}

void return_forks(int philosopher_number) {
  pthread_mutex_lock(&mutex);
  state[philosopher_number] = THINKING;
  test((philosopher_number + 1) % NUM_PHILOSOPHERS);
  test((philosopher_number + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS);
  pthread_mutex_unlock(&mutex);
}
void *philosopher(void *arg) {
  int philosopher_number = *(int *)arg;
  int d = 0;
  while (d < dishes) {
    printf("Philosopher %d is thinking\n", philosopher_number + 1);
    sleep(rand() % 5 + 1); // 🤔 for a while
    pickup_forks(philosopher_number);
    printf("Philosopher %d is eating\n", philosopher_number + 1);
    sleep(rand() % 5 + 1); // 🍽️ for a while
    return_forks(philosopher_number);
    d++;
  }
  pthread_exit(NULL);
}

int main() {
  srand(time(NULL));
  pthread_t philosophers[NUM_PHILOSOPHERS];
  int philosopher_number[NUM_PHILOSOPHERS];
  printf("Enter the number of dishes: ");
  scanf("%d", &dishes);
  int i;
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    philosopher_number[i] = i;
    state[i] = THINKING;
    pthread_cond_init(&self[i], NULL);
  }
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_create(&philosophers[i], NULL, philosopher, &philosopher_number[i]);
  }
  for (i = 0; i < NUM_PHILOSOPHERS; i++) {
    pthread_join(philosophers[i], NULL);
  }
  return 0;
}
