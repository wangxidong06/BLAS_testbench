#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "/root/openblas/pre_openblas/include/cblas.h"

#define iter 1000

void fill_random(double *x, int n, int max) {
    for (int i = 0; i < n; i++) {
        x[i] = rand() % max;
    }
}

void test_daxpy(int n) {
    double alpha = 1.0;
    double *X = (double *) malloc(n * sizeof(double));
    double *Y = (double *) malloc(n * sizeof(double));

    fill_random(X, n, 1);
    fill_random(Y, n, 1);

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_daxpy(n, alpha, X, 1, Y, 1);
    }

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Vector addition (daxpy) took %f seconds\n", time_elapsed);

    free(X);
    free(Y);
}

void test_ddot(int n) {
    double *x = (double *) malloc(n * sizeof(double));
    double *y = (double *) malloc(n * sizeof(double));

    fill_random(x, n, 1);
    fill_random(y, n, 1);

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        double result = cblas_ddot(n, x, 1, y, 1);
    }
    

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Vector dot product (ddot) took %f seconds\n", time_elapsed);

    free(x);
    free(y);
}

void test_dscal(int n, double scaling_factor) {
    double *x = (double *) malloc(n * sizeof(double));

    fill_random(x, n, 1);

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dscal(n, scaling_factor, x, 1);
    }

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Vector scaling (dscal) took %f seconds\n", time_elapsed);

    free(x);
}

void test_dnrm2(int n) {
    double *x = (double *) malloc(n * sizeof(double));

    fill_random(x, n, 1);

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        double result = cblas_dnrm2(n, x, 1);
    }

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Vector norm (dnrm2) took %f seconds\n", time_elapsed);

    free(x);
}

void test_dzasum(int n) {
    double *x = (double *) malloc(n * sizeof(double));

    fill_random(x, n, 1);

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        double result = cblas_dzasum(n, x, 1);
    }

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Euclidean distance between vectors (dzasum) took %f seconds\n", time_elapsed);

    free(x);
}


void test_daxpby(int n) {
    double *x = (double *) malloc(n * sizeof(double));
    double *y = (double *) malloc(n * sizeof(double));
    double alpha = 1.5, beta = 2.0;

    fill_random(x, n, 1);
    fill_random(y, n, 1);

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_daxpby(n, alpha, x, 1, beta, y, 1);
    }

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Scaled vector addition (daxpby) took %f seconds\n", time_elapsed);

    free(x);
    free(y);
}


void test_dcopy(int n) {
    double *x = (double *) malloc(n * sizeof(double));
    double *y = (double *) malloc(n * sizeof(double));

    fill_random(x, n, 1);

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dcopy(n, x, 1, y, 1);
    }

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Vector copy (dcopy) took %f seconds\n", time_elapsed);

    free(x);
    free(y);
}

void test_dsbmv(int n) {
    double *A = (double *) malloc(n * n * sizeof(double));
    double *x = (double *) malloc(n * sizeof(double));
    double *y = (double *) malloc(n * sizeof(double));
    double alpha = 1.0, beta = 0.0;
    int lda = n;
    int k = n - 1;

    fill_random(A, n * n, 10);
    fill_random(x, n, 10);
    fill_random(y, n, 10);

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dsbmv(CblasRowMajor, CblasUpper, n, k, alpha, A, lda, x, 1, beta, y, 1);
    }

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Symmetric band matrix-vector multiplication (dsbmv) took %f seconds\n", time_elapsed);

    free(A);
    free(x);
    free(y);
}

void test_drotg(int n) {
    double a, b, c, s;

    fill_random(&a, 1, 10);
    fill_random(&b, 1, 10);

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_drotg(&a, &b, &c, &s);
    }
    

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Vector cross product (drotg) took %f seconds\n", time_elapsed);
}


void test_dger(int m, int n) {
    double *A = (double *) malloc(m * n * sizeof(double));
    double *x = (double *) malloc(m * sizeof(double));
    double *y = (double *) malloc(n * sizeof(double));

    fill_random(A, m * n, 10);
    fill_random(x, m, 10);
    fill_random(y, n, 10);

    double alpha = 1.0;
    int lda = m;
    int incx = 1;
    int incy = 1;

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dger(CblasRowMajor, m, n, alpha, x, incx, y, incy, A, lda);
    }

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Vector outer product (dger) took %f seconds\n", time_elapsed);

    free(A);
    free(x);
    free(y);
}


int main() {
    int n = 1000;
    int m = 1000;
    double scaling_factor=0.1;

    test_daxpy(n);
    test_ddot(n);
    test_dnrm2(n);
    test_dzasum(n);
    test_daxpby(n);
    test_dcopy(n);
    test_dsbmv(n);
    test_drotg(n);
    test_dger(m, n);
    test_dscal(n, scaling_factor);
    
    return 0;
}




