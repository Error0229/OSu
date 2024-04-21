#include "CPU.h"
#include <stdio.h>
void run(task *t) {
  printf("Running task = [name: %s, priority: %d, burst: %d, tid: %d]\n",
         t->name, t->priority, t->burst, t->tid);
}
