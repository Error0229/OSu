#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DISK_SIZE 5000
int FCFS(int requests[], int n, int head) {
  int seek_count = 0;
  int cur_track = head;
  for (int i = 0; i < n; i++) {
    seek_count += abs(cur_track - requests[i]);
    cur_track = requests[i];
  }
  return seek_count;
}
int SCAN(int arr[], int n, int head) {
  int requests[n];
  for (int i = 0; i < n; i++) {
    requests[i] = arr[i];
  }
  int seek_count = 0;
  int cur_track = head;
  int direction = 1;
  for (int i = 0; i < n; i++) {
    if (direction == 1) {
      // find the next track in the direction of the request
      int next_track = DISK_SIZE;
      int next_index = -1;
      for (int j = 0; j < n; j++) {
        if (requests[j] >= cur_track && requests[j] < next_track) {
          next_track = requests[j];
          next_index = j;
        }
      }
      if (next_index == -1) {
        direction = 0;
        seek_count += DISK_SIZE - 1 - cur_track;
        cur_track = DISK_SIZE - 1;
      } else {
        seek_count += next_track - cur_track;
        cur_track = next_track;
        requests[next_index] = -1;
      }
    } else {
      int next_track = -1;
      int next_index = -1;
      for (int j = 0; j < n; j++) {
        if (requests[j] <= cur_track && requests[j] > next_track) {
          next_track = requests[j];
          next_index = j;
        }
      }
      if (next_index == -1) {
        direction = 1;
        seek_count += cur_track;
        cur_track = 0;
      } else {
        seek_count += cur_track - next_track;
        cur_track = next_track;
        requests[next_index] = -1;
      }
    }
  }
  return seek_count;
}
int C_SCAN(int requests[], int n, int head) {
  int seek_count = 0;
  int cur_track = head;
  for (int i = 0; i < n; i++) {
    // find the next track in the direction of the request
    int next_track = DISK_SIZE;
    int next_index = -1;
    for (int j = 0; j < n; j++) {
      if (requests[j] >= cur_track && requests[j] < next_track) {
        next_track = requests[j];
        next_index = j;
      }
    }
    if (next_index == -1) {
      seek_count += DISK_SIZE - 1 - cur_track;
      cur_track = 0;
    } else {
      seek_count += next_track - cur_track;
      cur_track = next_track;
      requests[next_index] = -1;
    }
  }
  return seek_count;
}
int main(int argc, char *argv[]) {
  int head = atoi(argv[1]);
  int n = 1000;
  int arr[n];
  srand(time(NULL));
  for (int i = 0; i < n; i++) {
    arr[i] = rand() % DISK_SIZE;
  }
  printf("FCFS: %d\n", FCFS(arr, n, head));
  printf("SCAN: %d\n", SCAN(arr, n, head));
  printf("C_SCAN: %d\n", C_SCAN(arr, n, head));
  return 0;
}
