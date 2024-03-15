#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int n = -1;
  if (sscanf(argv[1], "%d", &n) != 1 || n <= 0) {
    printf("Usage: %s <number>\n", argv[0]);
    return 1;
  }
  pid_t pid;
  pid = fork();
  if (pid == -1) {
    perror("fork");
    return 1;
  }
  if (pid == 0) {
    while (n != 1) {
      printf("%d ", n);
      if (n % 2 == 0) {
        n /= 2;
      } else {
        n = 3 * n + 1;
      }
    }
  } else {
    wait(NULL);
    puts("1"); // newline
  }
}
