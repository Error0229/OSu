#include <pthread.h>
#include <stdio.h>
#include <time.h>

struct sort_params {
  int *arr;
  int start;
  int end;
};

void *sort(void *arg) { // we love 🫧 sort
  struct sort_params *params = (struct sort_params *)arg;
  for (int i = params->start; i < params->end; i++) {
    for (int j = i + 1; j < params->end; j++) {
      if (params->arr[i] > params->arr[j]) {
        int temp = params->arr[i];
        params->arr[i] = params->arr[j];
        params->arr[j] = temp;
      }
    }
  }
  return NULL;
}

void *merge_sort(void *arg) { // merge two sorted arrays, not the merge sort :/
  struct sort_params *params = (struct sort_params *)arg;
  int size = params->end - params->start;
  int mid = (params->start + params->end) / 2;
  struct sort_params left_params = {params->arr, params->start, mid};
  struct sort_params right_params = {params->arr, mid, params->end};
  pthread_t left_thread, right_thread;
  pthread_create(&left_thread, NULL, sort, &left_params);
  pthread_create(&right_thread, NULL, sort, &right_params);
  pthread_join(left_thread, NULL);
  pthread_join(right_thread, NULL);
  int left_index = params->start;
  int right_index = mid;
  int temp[size];
  for (int i = 0; i < size; i++) {
    if (left_index == mid) {
      temp[i] = params->arr[right_index];
      right_index++;
    } else if (right_index == params->end) {
      temp[i] = params->arr[left_index];
      left_index++;
    } else if (params->arr[left_index] < params->arr[right_index]) {
      temp[i] = params->arr[left_index];
      left_index++;
    } else {
      temp[i] = params->arr[right_index];
      right_index++;
    }
  }
  for (int i = 0; i < size; i++) {
    printf("%d ", temp[i]);
  }
  printf("\n");
  return NULL;
}

int main() {
  clock_t t;
  t = clock();
  int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 3, 5,  8,  9,  7, 9,
               3, 2, 3, 8, 4, 6, 2, 6, 4, 23, 12, 63, 20};
  int n = sizeof(arr) / sizeof(arr[0]);
  struct sort_params params = {arr, 0, n};
  pthread_t parent_thread;
  pthread_create(&parent_thread, NULL, merge_sort, &params);
  pthread_join(parent_thread, NULL);
  printf("Time: %f\n", (double)(clock() - t) / CLOCKS_PER_SEC);
  return 0;
}
