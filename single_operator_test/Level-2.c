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


void test_dgemv(int m, int n) {
    double alpha = 1.0, beta = 0.0;
    double *A = (double *) malloc(m * n * sizeof(double));
    double *X = (double *) malloc(n * sizeof(double));
    double *Y = (double *) malloc(m * sizeof(double));

    fill_random(A, m*n, 1);
    fill_random(X, n, 1);
    fill_random(Y, m, 1);

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dgemv(CblasRowMajor, CblasNoTrans,
                m, n, alpha, A, n, X, 1, beta, Y, 1);
    }
    

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Matrix-vector multiplication (dgemv) took %f seconds\n", time_elapsed);

    free(A);
    free(X);
    free(Y);
}


void test_dsymv(int n) {
    double *A = (double *) malloc(n * n * sizeof(double));
    double *x = (double *) malloc(n * sizeof(double));
    double *y = (double *) malloc(n * sizeof(double));

    fill_random(A, n * n, 1);
    fill_random(x, n, 1);
    fill_random(y, n, 1);

    double alpha = 1.0, beta = 0.0;
    int lda = n;
    int incx = 1;
    int incy = 1;

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dsymv(CblasRowMajor, CblasUpper, n, alpha, A, lda, x, incx, beta, y, incy);
    }
    

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Symmetric matrix-vector multiplication (dsymv) took %f seconds\n", time_elapsed);

    free(A);
    free(x);
    free(y);
}


void test_dsyr(int n) {
    double *A = (double *) malloc(n * n * sizeof(double));
    double *x = (double *) malloc(n * sizeof(double));

    fill_random(A, n * n, 1);
    fill_random(x, n, 1);

    double alpha = 1.0;
    int lda = n;
    int incx = 1;

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dsyr(CblasRowMajor, CblasUpper, n, alpha, x, incx, A, lda);
    }
    

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Symmetric matrix rank-1 update (dsyr) took %f seconds\n", time_elapsed);

    free(A);
    free(x);
}


void test_dsyr2(int n) {
    double *A = (double *) malloc(n * n * sizeof(double));
    double *x = (double *) malloc(n * sizeof(double));
    double *y = (double *) malloc(n * sizeof(double));

    fill_random(A, n * n, 1);
    fill_random(x, n, 1);
    fill_random(y, n, 1);

    double alpha = 1.0;
    int lda = n;
    int incx = 1;
    int incy = 1;

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dsyr2(CblasRowMajor, CblasUpper, n, alpha, x, incx, y, incy, A, lda);
    }
    

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Symmetric matrix rank-2 update (dsyr2) took %f seconds\n", time_elapsed);

    free(A);
    free(x);
    free(y);
}


void test_dtbmv(int n, int k) {
    double *A = (double *) malloc(n * (k + 1) * sizeof(double));
    double *x = (double *) malloc(n * sizeof(double));

    fill_random(A, n * (k + 1), 1);
    fill_random(x, n, 1);

    int lda = k + 1;
    int incx = 1;

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dtbmv(CblasRowMajor, CblasUpper, CblasNoTrans, CblasNonUnit, n, k, A, lda, x, incx);
    }

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Triangular banded matrix-vector multiplication (dtbmv) took %f seconds\n", time_elapsed);

    free(A);
    free(x);
}


void test_dtbsv(int n, int k) {
    double *A = (double *) malloc(n * (k + 1) * sizeof(double));
    double *x = (double *) malloc(n * sizeof(double));

    fill_random(A, n * (k + 1), 1);
    fill_random(x, n, 1);

    int lda = k + 1;
    int incx = 1;

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dtbsv(CblasRowMajor, CblasUpper, CblasNoTrans, CblasNonUnit, n, k, A, lda, x, incx);
    }

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Triangular band matrix solve (dtbsv) took %f seconds\n", time_elapsed);

    free(A);
    free(x);
}


void test_dtpmv(int n) {
    double *A = (double *) malloc((n * (n + 1)) / 2 * sizeof(double));
    double *x = (double *) malloc(n * sizeof(double));

    fill_random(A, (n * (n + 1)) / 2, 1);
    fill_random(x, n, 1);

    int incx = 1;

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dtpmv(CblasRowMajor, CblasUpper, CblasNoTrans, CblasNonUnit, n, A, x, incx);
    }

    
    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Packed triangular matrix-vector multiplication (dtpmv) took %f seconds\n", time_elapsed);

    free(A);
    free(x);
}

void test_dtpsv(int n) {
    double *A = (double *) malloc((n * (n + 1)) / 2 * sizeof(double));
    double *x = (double *) malloc(n * sizeof(double));

    fill_random(A, (n * (n + 1)) / 2, 1);
    fill_random(x, n, 1);

    int incx = 1;

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dtpsv(CblasRowMajor, CblasUpper, CblasNoTrans, CblasNonUnit, n, A, x, incx);
    }

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Packed triangular matrix solve (dtpsv) took %f seconds\n", time_elapsed);

    free(A);
    free(x);
}

void test_dtrmv(int n) {
    double *A = (double *) malloc(n * n * sizeof(double));
    double *x = (double *) malloc(n * sizeof(double));

    fill_random(A, n * n, 1);
    fill_random(x, n, 1);

    int lda = n;
    int incx = 1;
    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dtrmv(CblasRowMajor, CblasUpper, CblasNoTrans, CblasNonUnit, n, A, lda, x, incx);
    }
    
    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Triangular matrix-vector multiplication (dtrmv) took %f seconds\n", time_elapsed);

    free(A);
    free(x);
}

void test_dtrsv(int n) {
    double *A = (double *) malloc(n * n * sizeof(double));
    double *x = (double *) malloc(n * sizeof(double));

    fill_random(A, n * n, 1);
    fill_random(x, n, 1);

    int lda = n;
    int incx = 1;

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dtrsv(CblasRowMajor, CblasUpper, CblasNoTrans, CblasNonUnit, n, A, lda, x, incx);
    }

    
    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Triangular matrix solve (dtrsv) took %f seconds\n", time_elapsed);

    free(A);
    free(x);
}


int main() {
    int n = 1000, m=1000;

    test_dgemv(n, m);
    test_dsymv(n);
    test_dsyr(n);
    test_dsyr2(n);
    test_dtbmv(n, m);
    test_dtbsv(n, m);
    test_dtpmv(n);
    test_dtpsv(n);
    test_dtrmv(n);
    test_dtrsv(n);
    
    return 0;
}