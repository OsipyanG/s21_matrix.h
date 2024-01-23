#include "s21_matrix.h"

int s21_is_empty_matrix(matrix_t *matrix) {
  if (matrix == NULL || matrix->matrix == NULL || matrix->columns <= 0 ||
      matrix->rows <= 0) {
    return SUCCESS;
  }
  return FAILURE;
}

int s21_safe_calloc(int columns, int rows, matrix_t *result) {
  result->matrix =
      malloc(columns * rows * sizeof(double) + rows * sizeof(double *));
  if (result->matrix == NULL) {
    return MALLOC_ERROR;
  }
  double *ptr = (double *)(result->matrix + rows);
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (ptr + columns * i);
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      result->matrix[i][j] = 0;
    }
  }
  return OK;
}
