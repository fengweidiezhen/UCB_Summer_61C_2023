#include "ex1.h"

void v_add_naive(double* x, double* y, double* z) {
    #pragma omp parallel
    {
        for(int i=0; i<ARRAY_SIZE; i++)
            z[i] = x[i] + y[i];
    }
}

// Adjacent Method
void v_add_optimized_adjacent(double* x, double* y, double* z) {
    // TODO: Implement this function
    // Do NOT use the `for` directive here!
    #pragma omp parallel
    {
        int total_thread = omp_get_num_threads();
        int current_thread = omp_get_thread_num();

        for (int i = current_thread; i < ARRAY_SIZE; i += total_thread) {
            z[i] = x[i] + y[i];
        }
    }
}

// Chunks Method
void v_add_optimized_chunks(double* x, double* y, double* z) {
    // TODO: Implement this function
    // Do NOT use the `for` directive here!
    #pragma omp parallel
    {
        int total_thread = omp_get_num_threads();
        int current_thread = omp_get_thread_num();
        int chunk_size = (ARRAY_SIZE + total_thread - 1) / total_thread;

        int start = current_thread * chunk_size;
        int end = (current_thread + 1) * chunk_size;
        if (end > ARRAY_SIZE) {
            end = ARRAY_SIZE;
        }

        for (int i = start; i < end; i++) {
            z[i] = x[i] + y[i];
        }
    }
}
