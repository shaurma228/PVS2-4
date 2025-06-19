#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double start;
double end;

void performOperations(double **a, double **b, double **result_add, double **result_sub, double **result_mul, double **result_div, const int SIZE, const int THREADS) {
    #pragma omp parallel for collapse(2) num_threads(THREADS)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result_add[i][j] = a[i][j] + b[i][j];
            result_sub[i][j] = a[i][j] - b[i][j];
            result_mul[i][j] = a[i][j] * b[i][j];
            result_div[i][j] = b[i][j] != 0 ? a[i][j] / b[i][j] : 0;
        }
    }
}

int main(int argc, char *argv[]) {
    const int SIZE = atoi(argv[1]);
    const int LOOPS = atoi(argv[2]);
    const int THREADS = atoi(argv[3]);

    double totalTime = 0;

    double **a = malloc(SIZE * sizeof(double *));
    double **b = malloc(SIZE * sizeof(double *));
    double **result_add = malloc(SIZE * sizeof(double *));
    double **result_sub = malloc(SIZE * sizeof(double *));
    double **result_mul = malloc(SIZE * sizeof(double *));
    double **result_div = malloc(SIZE * sizeof(double *));

    for (int i = 0; i < SIZE; i++) {
        a[i] = malloc(SIZE * sizeof(double));
        b[i] = malloc(SIZE * sizeof(double));
        result_add[i] = malloc(SIZE * sizeof(double));
        result_sub[i] = malloc(SIZE * sizeof(double));
        result_mul[i] = malloc(SIZE * sizeof(double));
        result_div[i] = malloc(SIZE * sizeof(double));
    }

    if (!a || !b || !result_add || !result_sub || !result_mul || !result_div) {
        printf("Memory error.\n");
        return 1;
    }

    omp_set_num_threads(THREADS);

    for (int k = 0; k < LOOPS; ++k) {
        start = omp_get_wtime();
        #pragma omp parallel for collapse(2) num_threads(THREADS)
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                a[i][j] = i + j + 1;
                b[i][j] = i + j + 2;
            }
        }

        performOperations(a, b, result_add, result_sub, result_mul, result_div, SIZE, THREADS);
        end = omp_get_wtime();

        totalTime += end - start;
    }

    printf("Time taken: %f seconds\n", totalTime / (LOOPS * 1.0));

    for (int i = 0; i < SIZE; i++) {
        free(a[i]);
        free(b[i]);
        free(result_add[i]);
        free(result_sub[i]);
        free(result_mul[i]);
        free(result_div[i]);
    }
    free(a);
    free(b);
    free(result_add);
    free(result_sub);
    free(result_mul);
    free(result_div);

    return 0;
}
