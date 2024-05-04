#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100
unsigned int begin, end;
typedef struct frag {
  char str[MAX_LEN];
  int begin, end;
  int exist;
  struct frag *next;
} frag_t;
frag_t *head, *tail;
enum FIT_STRATEGY { FIRST_FIT, BEST_FIT, WORST_FIT };
int allocate(int size, enum FIT_STRATEGY strategy, char *str) {
  int i, now, best = 1000000000, worst = -1;
  frag_t *cur = head, *next = head->next, *temp_next, *temp_cur;
  frag_t *new_frag = (frag_t *)malloc(sizeof(frag_t));
  switch (strategy) {
  case FIRST_FIT:
    while (next != NULL) {
      if (next->begin - cur->end >= size) {
        new_frag->begin = cur->end;
        new_frag->end = new_frag->begin + size;
        new_frag->exist = 1;
        strcpy(new_frag->str, str);
        new_frag->next = next;
        cur->next = new_frag;
        return 0;
      }
      cur = next;
      next = next->next;
    }
    break;
  case BEST_FIT:
    while (next != NULL) {
      if (next->begin - cur->end >= size) {
        if (next->begin - cur->end < best) {
          best = next->begin - cur->end;
          temp_next = next;
          temp_cur = cur;
        }
      }
      cur = next;
      next = next->next;
    }
    if (best == 0) {
      break;
    }
    new_frag->begin = temp_cur->end;
    new_frag->end = new_frag->begin + size;
    new_frag->exist = 1;
    strcpy(new_frag->str, str);
    new_frag->next = temp_next;
    temp_cur->next = new_frag;
    return 0;
    break;
  case WORST_FIT:
    while (next != NULL) {
      if (next->begin - cur->end >= size) {
        if (next->begin - cur->end > worst) {
          worst = next->begin - cur->end;
          temp_next = next;
          temp_cur = cur;
        }
      }
      cur = next;
      next = next->next;
    }
    if (worst == -1) {
      break;
    }
    new_frag->begin = temp_cur->end;
    new_frag->end = new_frag->begin + size;
    new_frag->exist = 1;
    strcpy(new_frag->str, str);
    new_frag->next = temp_next;
    temp_cur->next = new_frag;
    return 0;
    break;
  }
  free(new_frag);
  return -1;
}
int release(char *str) {
  frag_t *cur = head, *next = head->next;
  while (next != NULL) {
    if (strcmp(next->str, str) == 0) {
      cur->next = next->next;
      free(next);
      return 0;
    }
    cur = next;
    next = next->next;
  }
  return -1;
}
void print() {
  frag_t *cur, *next;
  cur = head;
  next = head->next;
  while (next != NULL) {
    // printf("cur->name: %s\n", cur->str);
    if (cur->end != next->begin) {
      printf("Address [%d:%d] Unused\n", cur->end, next->begin);
    }
    if (next->end - next->begin > 0)
      printf("Address [%d:%d] Process %s\n", next->begin, next->end - 1,
             next->str);

    cur = next;
    next = next->next;
  }
}
void compaction() {
  frag_t *cur, *next;
  cur = head;
  next = head->next;
  while (next != tail) {
    if (cur->end != next->begin) {
      next->end = next->end - (next->begin - cur->end);
      next->begin = cur->end;
    }
    cur = next;
    next = next->next;
  }
}
int main(int argc, char *argv[]) {
  unsigned int n;
  if (argc != 2) {
    printf("Usage: %s <n>\n", argv[0]);
    return 1;
  }
  sscanf(argv[1], "%u", &n);
  begin = 0, end = n;
  head = (frag_t *)malloc(sizeof(frag_t));
  head->begin = 0, head->end = 0, head->exist = 0;
  tail = (frag_t *)malloc(sizeof(frag_t));
  tail->begin = n, tail->end = n, tail->exist = 0;
  head->next = tail;
  char command[MAX_LEN];
  char *params[6];
  char *token;
  while (1) {
    printf("allocator> ");
    fgets(command, MAX_LEN, stdin);
    if (command[0] == '\n') {
      continue;
    }
    if (command[strlen(command) - 1] == '\n') {
      command[strlen(command) - 1] = '\0';
    }
    // commands are RQ, RL, STAT, C, Q
    token = strtok(command, " ");
    if (strcmp(token, "RQ") == 0) {
      params[0] = strtok(NULL, " ");
      params[1] = strtok(NULL, " ");
      params[2] = strtok(NULL, " ");
      if (params[0] == NULL || params[1] == NULL || params[2] == NULL) {
        printf("Invalid command\n");
        continue;
      }
      int size;
      sscanf(params[1], "%d", &size);
      if (size <= 0) {
        printf("Invalid command\n");
      }
      switch (params[2][0]) {
      case 'F':
        if (allocate(size, FIRST_FIT, params[0]) == -1) {
          printf("Fail to allocate memory\n");
        }
        break;
      case 'B':
        if (allocate(size, BEST_FIT, params[0]) == -1) {
          printf("Fail to allocate memory\n");
        }
        break;
      case 'W':
        if (allocate(size, WORST_FIT, params[0]) == -1) {
          printf("Fail to allocate memory\n");
        }
        break;
      default:
        printf("Invalid command\n");
        continue;
      }

    } else if (strcmp(token, "RL") == 0) {
      params[0] = strtok(NULL, " ");
      if (params[0] == NULL) {
        printf("Invalid command\n");
        continue;
      }
      if (release(params[0]) == -1) {
        printf("Fail to release memory\n");
      }

    } else if (strcmp(token, "STAT") == 0) {
      print();
    } else if (strcmp(token, "C") == 0) {
      compaction();
    } else if (strcmp(token, "Q") == 0) {
      break;
    } else {
      printf("Invalid command\n");
    }
  }
  return 0;
}
