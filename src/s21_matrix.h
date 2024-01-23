#ifndef S21_MATRIX
#define S21_MATRIX

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define INVALID_MATRIX 1
#define CALCULATION_ERROR 2
#define MALLOC_ERROR 3
#define TRUE 1
#define FALSE 0

#define EPS 1e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Create-Remove
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

// Comparators
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Arithmetic
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Other
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// Helpers
int s21_is_empty_matrix(matrix_t *matrix);
int s21_safe_calloc(int columns, int rows, matrix_t *result);
int s21_get_minor_matrix(matrix_t A, int delete_i, int delete_j,
                         matrix_t *minor_matrix);
int s21_calc_minor(matrix_t minor_matrix, double *result);

#endif  // S21_MATRIX
