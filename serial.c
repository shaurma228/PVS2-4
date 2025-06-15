#include <stdio.h>
#include <stdlib.h>

void performOperations(double *a, double *b, double *result_add, double *result_sub, double *result_mul, double *result_div, const int SIZE) {
    for (int i = 0; i < SIZE; i++) {
        result_add[i] = a[i] + b[i];
        result_sub[i] = a[i] - b[i];
        result_mul[i] = a[i] * b[i];
        result_div[i] = b[i] != 0 ? a[i] / b[i] : 0;
    }
}

int main(int argc, char *argv[]) {
    const int SIZE = atoi(argv[1]);

    double *a = malloc(SIZE * sizeof(double));
    double *b = malloc(SIZE * sizeof(double));
    double *result_add = malloc(SIZE * sizeof(double));
    double *result_sub = malloc(SIZE * sizeof(double));
    double *result_mul = malloc(SIZE * sizeof(double));
    double *result_div = malloc(SIZE * sizeof(double));

    if (!a || !b || !result_add || !result_sub || !result_mul || !result_div) {
        printf("Memory error.\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        a[i] = i + 1;
        b[i] = i + 2;
    }

    performOperations(a, b, result_add, result_sub, result_mul, result_div, SIZE);

    printf("Operations completed.\n");

    free(a);
    free(b);
    free(result_add);
    free(result_sub);
    free(result_mul);
    free(result_div);

    return 0;
}