#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (s21_is_empty_matrix(A) || s21_is_empty_matrix(B)) {
    return INVALID_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    return CALCULATION_ERROR;
  }
  int err = s21_create_matrix(A->rows, A->columns, result);
  if (err) {
    return err;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }
  return OK;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (s21_is_empty_matrix(A) || s21_is_empty_matrix(B)) {
    return INVALID_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    return CALCULATION_ERROR;
  }
  int err = s21_create_matrix(A->rows, A->columns, result);
  if (err) {
    return err;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return OK;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (s21_is_empty_matrix(A)) {
    return INVALID_MATRIX;
  }
  int err = s21_create_matrix(A->rows, A->columns, result);
  if (err) {
    return err;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = number * A->matrix[i][j];
    }
  }
  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (s21_is_empty_matrix(A) || s21_is_empty_matrix(B)) {
    return INVALID_MATRIX;
  } else if (A->columns != B->rows) {
    return CALCULATION_ERROR;
  }
  int err = s21_create_matrix(A->rows, B->columns, result);
  if (err) {
    return err;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return OK;
}
