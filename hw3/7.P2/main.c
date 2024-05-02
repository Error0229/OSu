#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_STUDENTS 2000
int n, count = 0, student_next;
sem_t student_ta;
pthread_mutex_t office_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;
int ta_sleeping = 0;
int queue[MAX_STUDENTS];
int front = 0, rear = 0, size = 0;
void enqueue(int id) {
  pthread_mutex_lock(&queue_lock);
  queue[rear] = id;
  size += 1;
  rear = (rear + 1) % MAX_STUDENTS;
  pthread_mutex_unlock(&queue_lock);
}
int dequeue() {
  pthread_mutex_lock(&queue_lock);
  int id = queue[front];
  size -= 1;
  front = (front + 1) % MAX_STUDENTS;
  pthread_mutex_unlock(&queue_lock);
  return id;
}
int get_size() {
  pthread_mutex_lock(&queue_lock);
  int s = size;
  pthread_mutex_unlock(&queue_lock);
  return s;
}
void *student(void *arg) {
  int id = *(int *)arg;
  sleep(rand() % 20 + 1); // the student is wandering around
  while (1) {
    pthread_mutex_lock(&office_lock);
    if (ta_sleeping) {
      printf("Student %d wakes up TA\n", id);
      ta_sleeping = 0;
      student_next = id;
      pthread_mutex_unlock(&office_lock);
      sem_post(&student_ta);
      break;
    } else {
      pthread_mutex_unlock(&office_lock);
      if (get_size() == 3) {
        printf("Student %d comes but the hallway is full\n", id);
        sleep(rand() % 10 + 1);
        continue;
      }
      printf("Student %d comes and waits in the hallway\n", id);
      enqueue(id);
      while (student_next != id) // wait for the TA to call
        ;
      sem_wait(&student_ta);
      break;
    }
  }
  return NULL;
}

void *TA(void *arg) {
  while (count != n) {
    if (get_size() == 0) {
      pthread_mutex_lock(&office_lock);
      ta_sleeping = 1;
      printf("TA is sleeping\n");
      pthread_mutex_unlock(&office_lock);
      sem_wait(&student_ta);
    } else {
      student_next = dequeue();
      printf("TA calling the student %d\n", student_next);
      sem_post(&student_ta);
    }
    printf("TA is helping student %d\n", student_next);
    sleep(rand() % 3 + 1); // TA is so fast!
    count += 1;
  }
  return NULL;
}
int main() {
  printf("Input the number of students: ");
  scanf("%d", &n);
  if (n > MAX_STUDENTS) {
    printf("The number of students is too high\n");
    return 1;
  }
  pthread_t students[MAX_STUDENTS], ta_thread;
  sem_init(&student_ta, 0, 0);
  ta_sleeping = 1;
  pthread_create(&ta_thread, NULL, TA, NULL);
  int ids[MAX_STUDENTS];
  for (int i = 0; i < n; i++) {
    ids[i] = i;
  }
  for (int i = 0; i < n; i++) {
    pthread_create(&students[i], NULL, student, &ids[i]);
  }
  for (int i = 0; i < n; i++) {
    pthread_join(students[i], NULL);
  }
  pthread_join(ta_thread, NULL);
  return 0;
}
