#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define RESOURCES 4
#define MAX_CUSTOMER 5
int available[RESOURCES];
pthread_mutex_t bank_lock = PTHREAD_MUTEX_INITIALIZER;
typedef struct customer {
  int max[RESOURCES];
  int allocation[RESOURCES];
  int need[RESOURCES]; // not necessary needed
} customer_t;
customer_t customers[MAX_CUSTOMER];
int safe_algorithm() {
  int work[RESOURCES];
  for (int i = 0; i < RESOURCES; i++) {
    work[i] = available[i];
  }
  bool finish[MAX_CUSTOMER];
  for (int i = 0; i < MAX_CUSTOMER; i++) {
    finish[i] = false;
  }
  int count = 0;
  while (count < MAX_CUSTOMER) {
    bool found = false;
    for (int i = 0; i < MAX_CUSTOMER; i++) {
      if (finish[i] == false) {
        bool need = true;
        for (int j = 0; j < RESOURCES; j++) {
          if (customers[i].need[j] > work[j]) {
            need = false;
            break;
          }
        }
        if (need) {
          for (int j = 0; j < RESOURCES; j++) {
            work[j] += customers[i].allocation[j];
          }
          count++;
          finish[i] = true;
          found = true;
        }
      }
    }

    if (!found) {
      return -1;
    }
  }
  return 0;
}
int request_resources(int customer_id, int request[]) {
  pthread_mutex_lock(&bank_lock);
  for (int i = 0; i < RESOURCES; i++) {
    if (request[i] > customers[customer_id].need[i] ||
        request[i] > available[i]) {
      pthread_mutex_unlock(&bank_lock);
      return -1;
    }
  }
  for (int i = 0; i < RESOURCES; i++) {
    available[i] -= request[i];
    customers[customer_id].allocation[i] += request[i];
    customers[customer_id].need[i] -= request[i];
  }

  if (safe_algorithm() == -1) {
    for (int i = 0; i < RESOURCES; i++) {
      available[i] += request[i];
      customers[customer_id].allocation[i] -= request[i];
      customers[customer_id].need[i] += request[i];
    }
    pthread_mutex_unlock(&bank_lock);
    return -1;
  }
  pthread_mutex_unlock(&bank_lock);
  return 0;
}
void release_resources(int customer_id) {
  pthread_mutex_lock(&bank_lock);
  for (int i = 0; i < RESOURCES; i++) {
    available[i] += customers[customer_id].allocation[i];
    customers[customer_id].allocation[i] = 0;
  }
  pthread_mutex_unlock(&bank_lock);
}
void *customer_thread(void *arg) {
  int customer_id = *(int *)arg;
  int request[RESOURCES];
  while (true) {
    for (int i = 0; i < RESOURCES; i++) {
      request[i] = rand() % (customers[customer_id].need[i] + 1);
    }
    printf("Customer %d request resources\n", customer_id);
    for (int i = 0; i < RESOURCES; i++) {
      printf("resource %d: request %d, allocation %d, need %d\n", i, request[i],
             customers[customer_id].allocation[i],
             customers[customer_id].need[i]);
    }
    if (request_resources(customer_id, request) == 0) {
      puts("request granted");
      bool flag = true;
      for (int i = 0; i < RESOURCES; i++) {
        if (customers[customer_id].need[i] != 0) {
          flag = false;
          break;
        }
      }
      if (flag) {
        release_resources(customer_id);
        pthread_exit(NULL);
      }
      sleep(rand() % 3 + 1);
    } else {
      puts("request denied");
      sleep(rand() % 3 + 1);
    }
  }
}
int main(int argc, char *argv[]) {
  for (int i = 0; i < RESOURCES; i++) {
    available[i] = atoi(argv[i + 1]);
  }
  for (int i = 0; i < MAX_CUSTOMER; i++) {
    for (int j = 0; j < RESOURCES; j++) {
      customers[i].max[j] = rand() % (available[j] - 3);
      customers[i].allocation[j] = 0;
      customers[i].need[j] = customers[i].max[j];
    }
  }
  pthread_t threads[MAX_CUSTOMER];
  for (int i = 0; i < MAX_CUSTOMER; i++) {
    int *arg = malloc(sizeof(*arg));
    *arg = i;
    pthread_create(&threads[i], NULL, customer_thread, arg);
  }
  for (int i = 0; i < MAX_CUSTOMER; i++) {
    pthread_join(threads[i], NULL);
  }
}
