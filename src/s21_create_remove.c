#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0) {
    return INVALID_MATRIX;
  }
  int err = s21_safe_calloc(columns, rows, result);
  if (err == MALLOC_ERROR) {
    return err;
  }
  result->columns = columns;
  result->rows = rows;
  return OK;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}
