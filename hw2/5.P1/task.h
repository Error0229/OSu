#ifndef TASK_H
#define TASK_H
#include <stdbool.h>
typedef struct task {
  char name[32];
  int priority;
  int burst;
  int tid;
  int flag;
} task;
#endif
