#include <bits/types/struct_timeval.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  pid_t pid;
  int shmid;
  char *shmaddr;
  if (argc <= 1) {
    printf("Usage: %s <command>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  // child process
  if (pid == 0) {
    // read and write
    shmid = shmget((key_t)2077, sizeof(struct timeval), IPC_CREAT | 0666);
    if (shmid == -1) {
      perror("shmget");
      exit(EXIT_FAILURE);
    }
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1) {
      perror("shmat");
      exit(EXIT_FAILURE);
    }
    struct timeval *tv = (struct timeval *)shmaddr;
    gettimeofday(tv, NULL);
    if (shmdt(shmaddr) == -1) {
      perror("shmdt");
      exit(EXIT_FAILURE);
    }
    execvp(argv[1], argv + 1);
    perror("execlp");
  } else {
    wait(NULL);
    shmid = shmget((key_t)2077, sizeof(struct timeval), 0666);
    if (shmid == -1) {
      perror("shmget");
      exit(EXIT_FAILURE);
    }
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1) {
      perror("shmat");
      exit(EXIT_FAILURE);
    }
    struct timeval *tv = (struct timeval *)shmaddr;
    struct timeval now;
    gettimeofday(&now, NULL);
    printf("Elapsed time: %ld us\n",
           (now.tv_sec - tv->tv_sec) * 1000000 + (now.tv_usec - tv->tv_usec));
    if (shmdt(shmaddr) == -1) {
      perror("shmdt");
      exit(EXIT_FAILURE);
    }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
      perror("shmctl");
      exit(EXIT_FAILURE);
    }
  }
  return 0;
}
