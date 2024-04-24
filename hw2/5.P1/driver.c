#include "CPU.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TASKS 100
#define min(a, b) ((a) < (b) ? (a) : (b))
int start_times[MAX_TASKS], waiting_times[MAX_TASKS];
int start, turn_around_time, waiting_time, response_time, now;

typedef struct node {
  task *task;
  struct node *next, *prev;
} node;
node *head, *tail, *current, *ran, *last_ran;
void print_list() {
  node *cur = head->next;
  puts("*********************************");
  while (cur != NULL) {
    printf("Task = [name: %s, priority: %d, burst: %d, flag: %d]\n",
           cur->task->name, cur->task->priority, cur->task->burst,
           cur->task->flag);
    cur = cur->next;
  }
  puts("*********************************");
}
void push_back(task *t) {
  node *n = (node *)malloc(sizeof(node));
  n->task = t;
  if (head->next == tail) {
    head->next = n;
    n->next = tail;
    n->prev = head;
    tail->prev = n;
  } else {
    tail->prev->next = n;
    n->prev = tail->prev;
    n->next = tail;
    tail->prev = n;
  }
}
void erase(node *n) {
  if (n == head || n == tail) {
    return; // keep the head and tail
  } else {
    n->prev->next = n->next;
    n->next->prev = n->prev;
  }
  free(n->task);
  free(n);
}
typedef struct Algorithm {
  void (*schedule)(void);
  task *(*pickNextTask)(void);
} Algorithm;
Algorithm *algo;
void schedule() { algo->schedule(); }

void pickNextTask() { algo->pickNextTask(); }
task *fcfs_pickNextTask(void) {
  if (head->next == tail)
    return NULL;
  return head->next->task;
}
void fcfs_schedule(void) {
  task *cur;
  int id = 0;
  while ((cur = fcfs_pickNextTask())) {
    __sync_fetch_and_add(&id, 1);
    cur->tid = id;
    start_times[cur->tid] = now;
    response_time += now - start;
    run(cur);
    printf("Task %s ran for %d units. Remaining burst = 0 units.\n", cur->name,
           cur->burst);
    printf("Task %s finished.\n", cur->name);
    now += cur->burst;
    turn_around_time += now - start; // all tasks are assumed to arrive at time
                                     // 0, so turn around time is the same as
                                     // the completion time
    cur->burst = 0;
    erase(head->next);
  }
}
task *roundRobin_pickNextTask(void) {
  if (head->next == tail) {
    if (tail->next == ran) {
      return NULL;
    } else {
      // put ran parts back to the head
      head->next = tail->next;
      tail->next->prev = head;

      ran->prev->next = tail;
      tail->prev = ran->prev;

      tail->next = ran;
      ran->prev = tail;
    }
  }

  // move the head to the next
  node *cur = head->next;
  head->next = cur->next;
  cur->next->prev = head;

  // put the current task to the tail
  if (tail->next == ran) {
    tail->next = cur;
    cur->prev = tail;
    cur->next = ran;
    ran->prev = cur;
  } else {
    ran->prev->next = cur;
    cur->prev = ran->prev;
    cur->next = ran;
    ran->prev = cur;
  }
  last_ran = cur;
  return cur->task;
}
void roundRobin_schedule(void) {
  task *cur;
  ran = (node *)malloc(sizeof(node));
  ran->task = (task *)malloc(sizeof(task));
  ran->next = NULL;
  int id = 0;
  tail->next = ran;
  while ((cur = roundRobin_pickNextTask())) {
    if (cur->tid == -1) {
      __sync_fetch_and_add(&id, 1);
      cur->tid = id;
      response_time += now - start;
    } else {
      waiting_time += now - waiting_times[cur->tid];
    }
    run(cur);
    int run_for = min(10, cur->burst);
    now += run_for;
    cur->burst -= run_for;
    printf("Task %s ran for %d units. Remaining burst = %d units.\n", cur->name,
           run_for, cur->burst);
    if (cur->burst == 0) {
      turn_around_time += now - start;
      printf("Task %s finished.\n", cur->name);
      erase(last_ran);
    } else {
      waiting_times[cur->tid] = now;
    }
  }
}
task *sjf_pickNextTask(void) {
  if (head->next == tail)
    return NULL;
  node *cur = head->next;
  node *min = head->next;
  while (cur != tail) {
    if (cur->task->burst < min->task->burst) {
      min = cur;
    }
    cur = cur->next;
  }
  last_ran = min;
  return min->task;
}
void sjf_schedule(void) {
  task *cur;
  int id = 0;
  while ((cur = sjf_pickNextTask())) {
    __sync_fetch_and_add(&id, 1);
    cur->tid = id;
    response_time += now - start;
    run(cur);
    printf("Task %s ran for %d units. Remaining burst = 0 units.\n", cur->name,
           cur->burst);
    printf("Task %s finished.\n", cur->name);
    now += cur->burst;
    turn_around_time += now - start; // all tasks are assumed to arrive at time
                                     // 0, so turn around time is the same as
                                     // the completion time
    // no waiting time
    cur->burst = 0;
    erase(last_ran);
  }
}
task *priority_pickNextTask(void) {
  if (head->next == tail)
    return NULL;
  node *cur = head->next->next;
  node *max = head->next;
  while (cur != tail) {
    if (cur->task->priority > max->task->priority) {
      max = cur;
    }
    cur = cur->next;
  }
  last_ran = max;
  return max->task;
}
void priority_schedule(void) {
  task *cur;
  int id = 0;
  while ((cur = priority_pickNextTask())) {
    __sync_fetch_and_add(&id, 1);
    cur->tid = id;
    start_times[cur->tid] = now;
    response_time += now - start;
    run(cur);
    printf("Task %s ran for %d units. Remaining burst = 0 units.\n", cur->name,
           cur->burst);
    printf("Task %s finished.\n", cur->name);
    now += cur->burst;
    turn_around_time += now - start; // all tasks are assumed to arrive at time
                                     // 0, so turn around time is the same as
                                     // the completion time
    // no waiting time
    cur->burst = 0;
    erase(last_ran);
  }
}
task *priority_rr_pickNextTask(void) {
  int current_max = 0;
  int max_count = 1;
  if (head->next == tail) {
    return NULL;
  }
  node *cur = head->next->next;
  node *max = head->next;
  // find max priority and count the number of tasks with the same priority
  while (cur != tail) {
    if (cur->task->priority > max->task->priority) {
      max = cur;
      current_max = cur->task->priority;
      max_count = 1;
    } else if (cur->task->priority == max->task->priority) {
      max_count++;
    }
    cur = cur->next;
  }
  // if there is only one task with the max priority, run it
  if (max_count == 1) {
    if (max->task->flag == -1) {
      last_ran = max;
      max->task->flag = 2; // the task can run till end
      return max->task;
    }
  }
  // else find the task that has max priority and not been run yet
  cur = head->next;
  while (cur != tail) {
    if (cur->task->priority == current_max) {
      if (cur->task->flag == -1) {
        last_ran = cur;
        cur->task->flag = 1; // the task can run for 10 units
        return cur->task;
      }
    }
    cur = cur->next;
  }
  // if all tasks have highest priority and have been run, reset the ran_tasks
  node *reset = head->next;
  while (reset != tail) {
    reset->task->flag = -1;
    reset = reset->next;
  }
  return priority_rr_pickNextTask();
}
void priority_rr_schedule(void) {
  task *cur;
  int id = 0;
  while ((cur = priority_rr_pickNextTask())) {
    if (cur->tid == -1) {
      __sync_fetch_and_add(&id, 1);
      cur->tid = id;
      response_time += now - start;
    } else {
      waiting_time += now - waiting_times[cur->tid];
    }
    run(cur);
    int run_for = min(10, cur->burst);
    if (cur->flag == 2) {
      run_for = cur->burst;
    }
    now += run_for;
    cur->burst -= run_for;
    printf("Task %s ran for %d units. Remaining burst = %d units.\n", cur->name,
           run_for, cur->burst);
    if (cur->burst == 0) {
      turn_around_time += now - start;
      printf("Task %s finished.\n", cur->name);
      erase(last_ran);
    } else {
      waiting_times[cur->tid] = now;
    }
  }
}
Algorithm fcfs = {fcfs_schedule, fcfs_pickNextTask};
Algorithm roundRobin = {roundRobin_schedule, roundRobin_pickNextTask};
Algorithm sjf = {sjf_schedule, sjf_pickNextTask};
Algorithm priority = {priority_schedule, priority_pickNextTask};
Algorithm priority_rr = {priority_rr_schedule, priority_rr_pickNextTask};

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./{algo_name} schedule.txt\n");
    return -1;
  }
  // open the file and read the tasks
  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Error: Unable to open file\n");
    return -1;
  }
  head = (node *)malloc(sizeof(node));
  tail = (node *)malloc(sizeof(node));
  head->next = tail;
  tail->prev = head;
  tail->next = NULL;
  tail->task = (task *)malloc(sizeof(task));
  int total = 0;
  while (!feof(file)) {
    task *t = (task *)malloc(sizeof(task));
    memset(t->name, 0, 32);
    if (fscanf(file, "%s %d %d", t->name, &t->priority, &t->burst) == EOF) {
      free(t);
      break;
    }
    total++;
    t->tid = -1;
    t->flag = -1;
    push_back(t);
  }
  fclose(file);

  start = turn_around_time = waiting_time = response_time = now = 0;
  current = NULL;
  for (int i = 0; i < MAX_TASKS; i++) {
    start_times[i] = waiting_times[i] = -1;
  }
#ifdef FCFS
  algo = &fcfs;
#elif ROUND_ROBIN
  algo = &roundRobin;
#elif SJF
  algo = &sjf;
#elif PRIORITY
  algo = &priority;
#elif PRIORITY_RR
  algo = &priority_rr;
#endif
  algo->schedule();
  puts("All tasks done 😸");
  printf("Average turnaround time = %.2f\n",
         (double)turn_around_time / (double)total);
  printf("Average waiting time = %.2f\n",
         (double)(waiting_time + response_time) / (double)total);
  printf("Average response time = %.2f\n",
         (double)response_time / (double)total);
  return 0;
}
