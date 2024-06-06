#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_PAGE 20000
int FIFO(int arr[], int frames) {
  int page_faults = 0;
  int frame[frames];
  for (int i = 0; i < frames; i++) {
    frame[i] = -1;
  }
  int frame_index = 0;
  for (int i = 0; i < MAX_PAGE; i++) {
    int flag = 0;
    for (int j = 0; j < frames; j++) {
      if (frame[j] == arr[i]) {
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      frame[frame_index] = arr[i];
      frame_index = (frame_index + 1) % frames;
      page_faults++;
    }
  }
  return page_faults;
}
int LRU(int arr[], int frames) {
  int page_faults = 0;
  int frame[frames];
  int reference[MAX_PAGE];
  int now = 0;
  for (int i = 0; i < frames; i++) {
    frame[i] = -1;
  }
  for (int i = 0; i < 15; i++) {
    reference[i] = -1;
  }
  for (int i = 0; i < MAX_PAGE; i++) {
    int flag = 0;
    for (int j = 0; j < frames; j++) {
      if (frame[j] == arr[i]) {
        flag = 1;
        reference[arr[i]] = now++;
        break;
      }
    }
    if (flag == 0) {
      int min = 0;
      for (int j = 0; j < frames; j++) {
        if (reference[j] < reference[min]) {
          min = j;
        }
      }
      frame[min] = arr[i];
      reference[min] = now++;
      page_faults++;
    }
  }
  return page_faults;
}
int OPT(int arr[], int frames) {
  int page_faults = 0;
  int frame[frames];
  for (int i = 0; i < frames; i++) {
    frame[i] = -1;
  }
  for (int i = 0; i < MAX_PAGE; i++) {
    // for (int j = 0; j < frames; j++) {
    //   printf("%d ", frame[j]);
    // }
    // printf("\n");
    int flag = 0;
    for (int j = 0; j < frames; j++) {
      if (frame[j] == arr[i]) {
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      int max = 0;
      int max_index = 0;
      for (int j = 0; j < frames; j++) {
        if (frame[j] == -1) {
          max_index = j;
          break;
        }
        int k = i + 1;
        while (k < MAX_PAGE) {
          if (frame[j] == arr[k]) {
            if (k > max) {
              max = k;
              max_index = j;
            }
            break;
          }
          k++;
        }
      }
      frame[max_index] = arr[i];
      page_faults++;
    }
  }
  return page_faults;
}
int main(int argc, char *argv[]) {
  srand(time(NULL));
  int pages[MAX_PAGE];
  for (int i = 0; i < MAX_PAGE; i++) {
    pages[i] = rand() % 10;
  }
  int frames = atoi(argv[1]);
  printf("FIFO: %d\n", FIFO(pages, frames));
  printf("LRU: %d\n", LRU(pages, frames));
  printf("OPT: %d\n", OPT(pages, frames));
  return 0;
}
