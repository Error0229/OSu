#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  int src_fd = open(argv[1], O_RDONLY);
  if (src_fd == -1) {
    perror("open");
    exit(1);
  }

  int dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (dst_fd == -1) {
    perror("open");
    exit(1);
  }

  char buf[BUFSIZ];
  ssize_t nread;
  while ((nread = read(src_fd, buf, BUFSIZ)) > 0) {
    if (write(dst_fd, buf, nread) != nread) {
      perror("write");
      exit(1);
    }
  }

  if (nread == -1) {
    perror("read");
    exit(1);
  }

  if (close(src_fd) == -1) {
    perror("close");
    exit(1);
  }

  if (close(dst_fd) == -1) {
    perror("close");
    exit(1);
  }

  return 0;
}
