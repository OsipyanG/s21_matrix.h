#include <math.h>

#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (s21_is_empty_matrix(A)) {
    return INVALID_MATRIX;
  }
  int err = s21_create_matrix(A->columns, A->rows, result);
  if (err) {
    return err;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return OK;
}

int s21_determinant(matrix_t *A, double *result) {
  int size = 0;
  double d = 0;
  int k = 1;
  matrix_t result_matrix = {0};
  if (A->columns != A->rows) {
    return CALCULATION_ERROR;
  } else {
    size = A->rows;
  }
  int err = s21_create_matrix(A->rows, A->columns, &result_matrix);
  if (err) {
    return err;
  }
  if (size == 1)
    *result = A->matrix[0][0];
  else if (size == 2)
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  else if (size > 2) {
    for (int i = 0; i < size; i++) {
      matrix_t minor_matrix;
      s21_get_minor_matrix(*A, i, 0, &minor_matrix);
      double temp;
      s21_determinant(&minor_matrix, &temp);
      d += k * A->matrix[i][0] * temp;
      k = -k;
      s21_remove_matrix(&minor_matrix);
    }
    *result = d;
  }
  s21_remove_matrix(&result_matrix);
  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err;
  err = s21_create_matrix(A->rows, A->columns, result);
  if (err) {
    s21_remove_matrix(result);
    return err;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t minor_matrix;
      double minor;
      err = s21_get_minor_matrix(*A, i, j, &minor_matrix);
      if (err) {
        s21_remove_matrix(result);
        return err;
      }
      s21_calc_minor(minor_matrix, &minor);
      result->matrix[i][j] = minor * pow(-1, i + j);
      s21_remove_matrix(&minor_matrix);
    }
  }
  return OK;
}

int s21_get_minor_matrix(matrix_t A, int delete_i, int delete_j,
                         matrix_t *minor_matrix) {
  if (A.rows != A.columns || A.rows <= 1 || A.columns <= 1) {
    return CALCULATION_ERROR;
  }
  int err;
  int minor_i = 0;
  int minor_j = 0;
  err = s21_create_matrix(A.rows - 1, A.columns - 1, minor_matrix);
  if (err) {
    return err;
  }
  for (int i = 0; i < A.rows; ++i) {
    if (i == delete_i) {
      continue;
    }
    for (int j = 0; j < A.columns; ++j) {
      if (j == delete_j) {
        continue;
      }
      minor_matrix->matrix[minor_i][minor_j] = A.matrix[i][j];
      minor_j++;
    }
    minor_i++;
    minor_j = 0;
  }
  return OK;
}

int s21_calc_minor(matrix_t minor_matrix, double *result) {
  int err;
  err = s21_determinant(&minor_matrix, result);
  if (err) {
    return err;
  }
  return OK;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err = 0;
  double det = 0;
  matrix_t complemets_matrix = {0};
  matrix_t transpose_complemets_matrix = {0};

  err = s21_determinant(A, &det);
  if (err) {
    return err;
  }
  if (det == 0) {
    return CALCULATION_ERROR;
  }
  err = s21_calc_complements(A, &complemets_matrix);
  if (err) {
    s21_remove_matrix(&complemets_matrix);
    return err;
  }
  err = s21_transpose(&complemets_matrix, &transpose_complemets_matrix);
  if (err) {
    s21_remove_matrix(&complemets_matrix);
    s21_remove_matrix(&transpose_complemets_matrix);
    return err;
  }
  err = s21_mult_number(&transpose_complemets_matrix, 1 / det, result);
  if (err) {
    s21_remove_matrix(&complemets_matrix);
    s21_remove_matrix(&transpose_complemets_matrix);
    return err;
  }
  s21_remove_matrix(&complemets_matrix);
  s21_remove_matrix(&transpose_complemets_matrix);
  return OK;
}
