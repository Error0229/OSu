#include <pthread.h>
#include <stdio.h>
#include <time.h>
enum error_type { ROW, COL, SUBGRID, NONE };
struct sudoku_validator {
  int sudoku[9][9];
  int check_index;
  enum error_type error;
};

void *check_row(void *arg) {
  struct sudoku_validator *validator = (struct sudoku_validator *)arg;
  int row = validator->check_index;
  int check[10] = {0};
  for (int i = 0; i < 9; i++) {
    int num = validator->sudoku[row][i];
    if (check[num] == 1) {
      validator->error = ROW;
      return NULL;
    }
    check[num] = 1;
  }
  return NULL;
}
void *check_col(void *arg) {
  struct sudoku_validator *validator = (struct sudoku_validator *)arg;
  int col = validator->check_index;
  int check[10] = {0};
  for (int i = 0; i < 9; i++) {
    int num = validator->sudoku[i][col];
    if (check[num] == 1) {
      validator->error = COL;
      return NULL;
    }
    check[num] = 1;
  }
  return NULL;
}

void *check_subgrid(void *arg) {
  struct sudoku_validator *validator = (struct sudoku_validator *)arg;
  int row = (validator->check_index / 3) * 3;
  int col = (validator->check_index % 3) * 3;
  int check[10] = {0};
  for (int i = row; i < row + 3; i++) {
    for (int j = col; j < col + 3; j++) {
      int num = validator->sudoku[i][j];
      if (check[num] == 1) {
        validator->error = SUBGRID;
        return NULL;
      }
      check[num] = 1;
    }
  }
  return NULL;
}

int main() {
  clock_t t;

  struct sudoku_validator validator;
  pthread_t threads[27];
  int s[9][9] = {
      {5, 3, 4, 6, 7, 8, 9, 1, 2}, {6, 7, 2, 1, 9, 5, 3, 4, 8},
      {1, 9, 8, 3, 4, 2, 5, 6, 7}, {8, 5, 9, 7, 6, 1, 4, 2, 3},
      {4, 2, 6, 8, 5, 3, 7, 9, 1}, {7, 1, 3, 9, 2, 4, 8, 5, 6},
      {9, 6, 1, 5, 3, 7, 2, 8, 4}, {2, 8, 7, 4, 1, 9, 6, 3, 5},
      {3, 4, 5, 2, 8, 6, 1, 7, 9},
  };
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      validator.sudoku[i][j] = s[i][j];
    }
  }
  t = clock();
  validator.error = NONE;
  for (int i = 0; i < 9; i++) {
    validator.check_index = i;
    pthread_create(&threads[i], NULL, check_row, &validator);
  }
  for (int i = 0; i < 9; i++) {
    validator.check_index = i;
    pthread_create(&threads[i + 9], NULL, check_col, &validator);
  }
  for (int i = 0; i < 9; i++) {
    validator.check_index = i;
    pthread_create(&threads[i + 18], NULL, check_subgrid, &validator);
  }
  for (int i = 0; i < 27; i++) {
    pthread_join(threads[i], NULL);
  }

  switch (validator.error) {
  case ROW:
    printf("Invalid on row %d\n", validator.check_index);
    break;
  case COL:
    printf("Invalid on col %d\n", validator.check_index);
    break;
  case SUBGRID:
    printf("Invalid on subgrid %d\n", validator.check_index);
    break;
  case NONE:
    printf("Valid\n");
    break;
  }
  t = clock() - t;
  printf("Time taken: %f\n", (double)t / CLOCKS_PER_SEC);
  return 0;
}
