#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <source> <destination>\n", argv[0]);
    exit(1);
  }
  // make sure the source doesn't equal to the destination
  if (strcmp(argv[1], argv[2]) == 0) {
    printf("Error: source and destination are the same\n");
    exit(1);
  }
  int pipes[2];
  pipe(pipes);
  pid_t pid;
  pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  // paretn process
  if (pid > 0) {
    close(pipes[0]);
    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1) {
      perror("open");
      exit(1);
    }
    char buf[BUFSIZ];
    ssize_t nread;
    while ((nread = read(src_fd, buf, BUFSIZ)) > 0) {
      if (write(pipes[1], buf, nread) != nread) {
        perror("write");
        exit(1);
      }
    }
    if (nread == -1) {
      perror("read");
      exit(1);
    }
    close(src_fd);
    close(pipes[1]);
  } else {
    close(pipes[1]);
    int dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
      perror("open");
      exit(1);
    }
    char buf[BUFSIZ];
    ssize_t nread;
    while ((nread = read(pipes[0], buf, BUFSIZ)) > 0) {
      if (write(dst_fd, buf, nread) != nread) {
        perror("write");
        exit(1);
      }
    }
    if (nread == -1) {
      perror("read");
      exit(1);
    }
    close(dst_fd);
    close(pipes[0]);
  }
  return 0;
}
