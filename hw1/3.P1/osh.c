#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 80

int main(void) {
  char *args[MAX_LINE / 2 + 1];
  char *history[MAX_LINE / 2 + 1];
  int id = 0;
  for (id = 0; id < MAX_LINE / 2 + 1; id++) {
    args[id] = (char *)malloc(MAX_LINE * sizeof(char));
    history[id] = NULL;
  }
  int should_run = 1;
  while (should_run) {
    printf("osh> ");
    fflush(stdout);
    char *input = (char *)malloc(MAX_LINE * sizeof(char));
    fgets(input, MAX_LINE, stdin);
    if (input[strlen(input) - 1] == '\n') {
      input[strlen(input) - 1] = '\0';
    }
    int i = 0;
    char *token = strtok(input, " ");
    while (token != NULL) {
      if (args[i] == NULL) {
        args[i] = (char *)malloc(MAX_LINE * sizeof(char));
      }
      strncpy(args[i], token, strlen(token) + 1);
      token = strtok(NULL, " ");
      i++;
    }
    free(args[i]);
    args[i] = NULL;
    if (strncmp(args[0], "exit", 4) == 0) {
      should_run = 0;
      free(input);
      break;
    }
    if (strncmp(args[0], "!!", 2) == 0) {
      if (history[0] == NULL) {
        printf("No commands in history\n");
        continue;
      }
      int j = 0;
      while (history[j] != NULL) {
        if (args[j] == NULL) {
          args[j] = (char *)malloc(MAX_LINE * sizeof(char));
        }
        strncpy(args[j], history[j], strlen(history[j]) + 1);
        j++;
      }
      free(args[j]);
      args[j] = NULL;
    }
    int j = 0;
    while (args[j] != NULL) {
      if (history[j] == NULL)
        history[j] = (char *)malloc(MAX_LINE * sizeof(char));
      strncpy(history[j], args[j], strlen(args[j]) + 1);
      j++;
    }
    free(history[j]);
    history[j] = NULL;
    pid_t pid = fork();
    if (pid < 0) {
      return 1;
    } else if (pid == 0) {
      if (j >= 2) {
        int pos = 0, k = 0, fd;
        enum { NONE, REDIRECT_IN, REDIRECT_OUT, PIPE } op = NONE;
        for (k = 0; k < j; k++) {
          if (strcmp(args[k], ">") == 0) {
            op = REDIRECT_OUT;
            pos = k;
          } else if (strcmp(args[k], "<") == 0) {
            op = REDIRECT_IN;
            pos = k;
          } else if (strcmp(args[k], "|") == 0) {
            op = PIPE;
            pos = k;
          }
        }
        switch (op) {
        case REDIRECT_IN:
          args[pos] = NULL;
          fd = open(args[pos + 1], O_RDONLY);
          dup2(fd, STDIN_FILENO);
          close(fd);
          break;
        case REDIRECT_OUT:
          args[pos] = NULL;
          fd = open(args[pos + 1], O_CREAT | O_WRONLY, 0644);
          dup2(fd, STDOUT_FILENO);
          close(fd);
          break;
        case PIPE:
          args[pos] = NULL;
          char *args1[MAX_LINE / 2 + 1];
          args1[pos] = NULL;
          int k = 0;
          for (k = 0; k < pos; k++) {
            args1[k] = args[k];
          }
          int fds[2];
          pipe(fds);
          pid_t pid2 = fork();
          if (pid2 < 0) {
            return 1;
          } else if (pid2 == 0) {
            close(fds[0]);
            dup2(fds[1], STDOUT_FILENO);
            close(fds[1]);
            execvp(args[0], args1);
          } else {
            wait(NULL);
            close(fds[1]);
            dup2(fds[0], STDIN_FILENO);
            close(fds[0]);
            execvp(args[pos + 1], args + pos + 1);
          }
          break;
        default:
          break;
        }
      }
      execvp(args[0], args);
    } else {
      wait(NULL);
    }
    free(input);
  }
  for (id = 0; id < MAX_LINE / 2 + 1; id++) {
    free(args[id]);
    free(history[id]);
  }
}
