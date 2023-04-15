#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "/root/openblas/pre_openblas/include/cblas.h"

#define iter 10

void fill_random(double *x, int n, int max) {
    for (int i = 0; i < n; i++) {
        x[i] = rand() % max;
    }
}

void test_dgemm(int m, int n, int k) {
    double alpha = 1.0, beta = 0.0;
    double *A = (double *) malloc(m * k * sizeof(double));
    double *B = (double *) malloc(k * n * sizeof(double));
    double *C = (double *) malloc(m * n * sizeof(double));

    fill_random(A, m*k, 1);
    fill_random(B, k*n, 1);
    fill_random(C, m*n, 1);

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, alpha, A, k, B, n, beta, C, n);
    }
    

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Matrix-matrix multiplication (dgemm) took %f seconds\n", time_elapsed);

    free(A);
    free(B);
    free(C);
}

void test_dtrsm(int m, int n) {
    double *A = (double *) malloc(m * n * sizeof(double));
    double *B = (double *) malloc(m * n * sizeof(double));
    double alpha = 1.0;
    int lda = m;
    int ldb = n;

    fill_random(A, m * n, 1);
    fill_random(B, m * n, 1);

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dtrsm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, m, n, alpha, A, lda, B, ldb);
    }

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Triangular matrix inversion (dtrsm) took %f seconds\n", time_elapsed);

    free(A);
    free(B);
}

void test_column_sum(int m, int n) {
    double *A = (double *) malloc(m * n * sizeof(double));
    double *x = (double *) malloc(n * sizeof(double));
    double *y = (double *) malloc(m * sizeof(double));

    fill_random(A, m * n, 1);
    fill_random(x, n, 1);
    fill_random(y, m, 1);

    double alpha = 1.0, beta = 0.0;
    int lda = m;
    int incx = 1;
    int incy = 1;

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dgemv(CblasRowMajor, CblasNoTrans, m, n, alpha, A, lda, x, incx, beta, y, incy);
    }
    
    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Matrix column sum (dgemv) took %f seconds\n", time_elapsed);

    free(A);
    free(x);
    free(y);
}

void test_dtrmm(int m, int n) {
    double *A = (double *) malloc(m * n * sizeof(double));
    double *B = (double *) malloc(m * n * sizeof(double));

    fill_random(A, m * n, 1);
    fill_random(B, m * n, 1);

    double alpha = 1.0;
    int lda = m;
    int ldb = n;

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, m, n, alpha, A, lda, B, ldb);
    }

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Triangular matrix-matrix multiplication (dtrmm) took %f seconds\n", time_elapsed);

    free(A);
    free(B);
}


void test_dsyrk(int n, int k) {
    double *A = (double *) malloc(n * k * sizeof(double));
    double *C = (double *) malloc(n * n * sizeof(double));

    fill_random(A, n * k, 1);
    fill_random(C, n * n, 1);

    double alpha = 1.0, beta = 0.0;
    int lda = n;
    int ldc = n;

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dsyrk(CblasRowMajor, CblasUpper, CblasNoTrans, n, k, alpha, A, lda, beta, C, ldc);
    }
   
    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Symmetric rank-k update (dsyrk) took %f seconds\n", time_elapsed);

    free(A);
    free(C);
}

void test_dsyr2k(int n, int k) {
    double *A = (double *) malloc(n * k * sizeof(double));
    double *B = (double *) malloc(n * k * sizeof(double));
    double *C = (double *) malloc(n * n * sizeof(double));

    fill_random(A, n * k, 1);
    fill_random(B, n * k, 1);
    fill_random(C, n * n, 1);

    double alpha = 1.0, beta = 0.0;
    int lda = k, ldb = k, ldc = n;

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dsyr2k(CblasRowMajor, CblasUpper, CblasNoTrans, n, k, alpha, A, lda, B, ldb, beta, C, ldc);
    }

    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Symmetric rank-2k update (dsyr2k) took %f seconds\n", time_elapsed);

    free(A);
    free(B);
    free(C);
}


void test_dsymm(int m, int n) {
    double *A = (double *) malloc(m * m * sizeof(double));
    double *B = (double *) malloc(m * n * sizeof(double));
    double *C = (double *) malloc(m * n * sizeof(double));

    fill_random(A, m * m, 1);
    fill_random(B, m * n, 1);
    fill_random(C, m * n, 1);

    double alpha = 1.0, beta = 0.0;
    int lda = m, ldb = m, ldc = m;

    clock_t start = clock();

    for (int i = 0; i < iter; i++) {
        cblas_dsymm(CblasRowMajor, CblasLeft, CblasUpper, m, n, alpha, A, lda, B, ldb, beta, C, ldc);
    }
    
    clock_t end = clock();

    double time_elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Symmetric matrix multiply (dsymm) took %f seconds\n", time_elapsed);

    free(A);
    free(B);
    free(C);
}


int main() {
    int n = 1000, m=1000, k=1000;

    test_dgemm(m, n, k);
    test_dtrsm(m, n);
    test_column_sum(m, n);
    test_dtrmm(m, n);
    test_dsyrk(n, k);
    test_dsyr2k(n, k);
    test_dsymm(m, n);
    
    return 0;
}

