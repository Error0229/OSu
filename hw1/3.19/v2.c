
#include <bits/types/struct_timeval.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <sys/wait.h>

#include <unistd.h>

int main() {
  int pipes[2];
  pid_t pid;
  struct timeval start, end;
  pipe(pipes);
  pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  // child process
  if (pid == 0) {
    close(pipes[0]);
    gettimeofday(&start, NULL);
    write(pipes[1], &start, sizeof(struct timeval));
    close(pipes[1]);
    execlp("ls", "ls", NULL);
    perror("execlp");
  } else {
    wait(NULL);
    close(pipes[1]);
    read(pipes[0], &start, sizeof(struct timeval));
    gettimeofday(&end, NULL);
    printf("Elapsed time: %ld us\n", (end.tv_sec - start.tv_sec) * 1000000 +
                                         (end.tv_usec - start.tv_usec));
    close(pipes[0]);
  }
  return 0;
}
