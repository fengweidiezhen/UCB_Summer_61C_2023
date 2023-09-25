#include <omp.h>
#include <x86intrin.h>

#include "compute.h"

// Computes the dot product of vec1 and vec2, both of size n
int32_t dot(uint32_t n, int32_t *vec1, int32_t *vec2) {
  // TODO: implement dot product of vec1 and vec2, both of size n
  int32_t result = 0;

  __m256i const perm_mask = _mm256_setr_epi32(7,6,5,4,3,2,1,0);

  if (n >= 8) {

    __m256i sum = _mm256_setzero_si256();

    for (unsigned int i = 0; i < n / 8 * 8; i+=8) {
      __m256i a = _mm256_loadu_si256((__m256i *) (vec1 + i));

      // load ith last 8 elements of mat_B.
      __m256i b = _mm256_loadu_si256((__m256i *) (vec2 + n - i - 8));

      //reverse the order of b
      __m256i b_reverse = _mm256_permutevar8x32_epi32(b, perm_mask);

      __m256i tem = _mm256_mullo_epi32(a, b_reverse);

      sum = _mm256_add_epi32(sum, tem);
    }

    int32_t tem_arr[8];
    _mm256_storeu_si256((__m256i *) tem_arr, sum);
    
    result = result + tem_arr[0] + tem_arr[1] + tem_arr[2] + tem_arr[3] + tem_arr[4] + tem_arr[5] + tem_arr[6] + tem_arr[7]; 
    
  }
  
  for (int i = n / 8 * 8; i < n; i++) {
    result += vec1[i] * vec2[n-1 -i];
  }
  
  return result;
}

// Computes the convolution of two matrices
int convolve(matrix_t *a_matrix, matrix_t *b_matrix, matrix_t **output_matrix) {
  // TODO: convolve matrix a and matrix b, and store the resulting matrix in
  // output_matrix
  uint32_t a_col = a_matrix->cols;
  uint32_t a_row = a_matrix->rows;

  uint32_t b_col = b_matrix->cols;
  uint32_t b_row = b_matrix->rows;

  uint32_t output_row = a_row - b_row + 1;
  uint32_t output_col = a_col - b_col + 1;

  *output_matrix = (matrix_t *) calloc(1, sizeof(matrix_t));

  (*output_matrix)->rows = output_row;
  (*output_matrix)->cols = output_col;
  (*output_matrix)->data = calloc(output_col * output_row, sizeof(int32_t));

  #pragma omp parallel for collapse(2) 
  for (uint32_t row = 0; row < output_row; row++) {
    for (uint32_t col = 0; col < output_col; col++) {     
      int result = 0;
      #pragma for reduction(+ : result)
      for (uint32_t r = 0; r < b_row; r++) {
        result += dot(b_col, a_matrix->data + ((a_col * row) + col + (r * a_col)), b_matrix->data + ((b_row -1 -r) * b_col));
      }

      (*output_matrix)->data[(row * output_col) + col] = result;
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
