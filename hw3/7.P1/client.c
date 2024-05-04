/**
 * Example client program that uses thread pool.
 */

#include "threadpool.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct data {
  int a;
  int b;
};

void add(void *param) {
  struct data *temp;
  temp = (struct data *)param;
  sleep(rand() % 5 + 1);
  printf("I add two values %d and %d result = %d\n", temp->a, temp->b,
         temp->a + temp->b);
}

int main(void) {
  srand(time(NULL));
  // create some work to do
  struct data works[10];
  int i;
  for (i = 0; i < 10; i++) {
    works[i].a = i;
    works[i].b = i + 10;
  }
  // initialize the thread pool
  pool_init();

  // submit the work to the queue
  for (i = 0; i < 10; i++) {
    pool_submit(&add, &works[i]);
  }
  // may be helpful
  sleep(3);

  pool_shutdown();

  return 0;
}
