#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double startAdd, endAdd, startSub, endSub, startMul, endMul, startDiv, endDiv;

void addOperation(double **a, double **b, double **result, const int SIZE) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void subOperation(double **a, double **b, double **result, const int SIZE) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = a[i][j] - b[i][j];
        }
    }
}

void mulOperation(double **a, double **b, double **result, const int SIZE) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = a[i][j] * b[i][j];
        }
    }
}

void divOperation(double **a, double **b, double **result, const int SIZE) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = b[i][j] != 0 ? a[i][j] / b[i][j] : 0;
        }
    }
}

int main(int argc, char *argv[]) {
    const int SIZE = atoi(argv[1]);
    const int LOOPS = atoi(argv[2]);

    double totalTimeAdd = 0.0, totalTimeSub = 0.0, totalTimeMul = 0.0, totalTimeDiv = 0.0;

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

    for (int k = 0; k < LOOPS; ++k) {
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                a[i][j] = i + j + 1;
                b[i][j] = i + j + 2;
            }
        }

        startAdd = omp_get_wtime();
        addOperation(a, b, result_add, SIZE);
        endAdd = omp_get_wtime();
        totalTimeAdd += endAdd - startAdd;

        startSub = omp_get_wtime();
        subOperation(a, b, result_sub, SIZE);
        endSub = omp_get_wtime();
        totalTimeSub += endSub - startSub;

        startMul = omp_get_wtime();
        mulOperation(a, b, result_mul, SIZE);
        endMul = omp_get_wtime();
        totalTimeMul += endMul - startMul;

        startDiv = omp_get_wtime();
        divOperation(a, b, result_div, SIZE);
        endDiv = omp_get_wtime();
        totalTimeDiv += endDiv - startDiv;
    }

    printf("Average time for addition: %f seconds\n", totalTimeAdd / LOOPS);
    printf("Average time for subtraction: %f seconds\n", totalTimeSub / LOOPS);
    printf("Average time for multiplication: %f seconds\n", totalTimeMul / LOOPS);
    printf("Average time for division: %f seconds\n", totalTimeDiv / LOOPS);

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