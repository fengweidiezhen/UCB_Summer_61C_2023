#include "compute.h"

// Computes the dot product of vec1 and vec2, both of size n
int32_t dot(uint32_t n, int32_t *vec1, int32_t *vec2) {
  // TODO: implement dot product of vec1 and vec2, both of size n
  int32_t result = 0;

  for (uint32_t i = 0; i < n; i++) {
      result += vec1[i] * vec2[i];
  }

  return result;
}

// Computes the convolution of two matrices
int convolve(matrix_t *a_matrix, matrix_t *b_matrix, matrix_t **output_matrix) {
  // TODO: convolve matrix a and matrix b, and store the resulting matrix in
  // output_matrix
  if (a_matrix == NULL || b_matrix == NULL || output_matrix == NULL) {
        return -1;  // Invalid input
  }

  uint32_t a_cols = a_matrix->cols;
  uint32_t a_rows = a_matrix->rows;

  uint32_t b_cols = b_matrix->cols;
  uint32_t b_rows = b_matrix->rows;

  uint32_t output_rows = a_rows - b_rows + 1;
  uint32_t output_cols = a_cols - b_cols + 1;

  *output_matrix = (matrix_t *) calloc(1, sizeof(matrix_t));

  (*output_matrix)->rows = output_rows;
  (*output_matrix)->cols = output_cols;
  (*output_matrix)->data = calloc(output_cols * output_rows, sizeof(int32_t));

  for (uint32_t row = 0; row < output_rows; row++) {
    for (uint32_t col = 0; col < output_cols; col++) {
      
      int32_t result = 0;
      uint32_t a_output_offset = (a_cols * row) + col;

      for (uint32_t r = 0; r < b_rows; r++) {
        for (uint32_t c = 0; c < b_cols; c++) {
          uint32_t index_b = (b_rows - r - 1) * b_cols + (b_cols - c - 1);
          uint32_t index_a = a_output_offset + (r * a_cols) + c;
          result += a_matrix->data[index_a] * b_matrix->data[index_b];
        }
      }

      uint32_t output_index = (row * output_cols) + col;

      (*output_matrix)->data[output_index] = result;
    } 
  }
  return 0;

}

// Executes a task
int execute_task(task_t *task) {
  matrix_t *a_matrix, *b_matrix, *output_matrix;

  if (read_matrix(get_a_matrix_path(task), &a_matrix))
    return -1;
  if (read_matrix(get_b_matrix_path(task), &b_matrix))
    return -1;

  if (convolve(a_matrix, b_matrix, &output_matrix))
    return -1;

  if (write_matrix(get_output_matrix_path(task), output_matrix))
    return -1;

  free(a_matrix->data);
  free(b_matrix->data);
  free(output_matrix->data);
  free(a_matrix);
  free(b_matrix);
  free(output_matrix);
  return 0;
}
