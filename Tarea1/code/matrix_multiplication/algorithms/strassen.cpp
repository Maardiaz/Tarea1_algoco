// Tarea 1: Algoritmos y Complejidad (INF-221) Semestre 2026-2
// Autor: Martín Angelo Araya Díaz
// Rol: 202473646-9
// Algoritmo de Strassen adaptado de:
// https://github.com/psakoglou/Strassen-Algorithm-Simulation-and-Asymptotic-Efficiency-CPP



// Lo que hace strassen es dividir ambas matrices en cuadrantes, utiliza 7 recursiones ingenuamente se podría pensar que se necesitan
// 8, pero con 7 puede reconstruir el resultado del cuadrante que falta. Por lo tanto, primero crea 8 submatrices, que son cada cuadrante
// de las matrices a multiplicar, luego se hacen 10 operaciones de suma/resta, luego se obtienen 7 productos usando llamadas recursivas a strassen
// donde el caso base es una matriz de N = 1, los cuadrantes se calculan con sumas y restas de de los resultados de los 7 productos recursivos.

// Complejidad Temporal: O(n^(2,81))
// Complejidad Espacial: O(n^2)

#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long lld;
using Matrix = lld**;
Matrix createMatrix(size_t N) {
    Matrix M = new lld*[N];
    for (size_t i = 0; i < N; i++) {
        M[i] = new lld[N]();
    }
    return M;
}
void deleteMatrix(Matrix M, size_t N) {
    for (size_t i = 0; i < N; i++) {
        delete[] M[i];
    }
    delete[] M;
}
Matrix add(Matrix A, Matrix B, size_t N) {
    Matrix C = createMatrix(N);
    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}
Matrix subtract(Matrix A, Matrix B, size_t N) {
    Matrix C = createMatrix(N);
    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}
Matrix sq_matrix_multiply(Matrix A, Matrix B, size_t N) {
    Matrix C = createMatrix(N);
    lld sum = 0;
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 0; j < N; j++) {
            for (size_t k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
            sum = 0;
        }
    }
    return C;
}
Matrix strassen(Matrix A, Matrix B, size_t N) {
    if (N == 1) {
        return sq_matrix_multiply(A, B, N);
    }
    Matrix C = createMatrix(N);
    size_t K = N / 2;
    Matrix A11 = createMatrix(K);
    Matrix A12 = createMatrix(K);
    Matrix A21 = createMatrix(K);
    Matrix A22 = createMatrix(K);
    Matrix B11 = createMatrix(K);
    Matrix B12 = createMatrix(K);
    Matrix B21 = createMatrix(K);
    Matrix B22 = createMatrix(K);
    for (unsigned int i = 0; i < K; i++) {
        for (unsigned j = 0; j < K; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][K + j];
            A21[i][j] = A[K + i][j];
            A22[i][j] = A[K + i][K + j];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][K + j];
            B21[i][j] = B[K + i][j];
            B22[i][j] = B[K + i][K + j];
        }
    }
    Matrix S1 = subtract(B12, B22, K);
    Matrix S2 = add(A11, A12, K);
    Matrix S3 = add(A21, A22, K);
    Matrix S4 = subtract(B21, B11, K);
    Matrix S5 = add(A11, A22, K);
    Matrix S6 = add(B11, B22, K);
    Matrix S7 = subtract(A12, A22, K);
    Matrix S8 = add(B21, B22, K);
    Matrix S9 = subtract(A11, A21, K);
    Matrix S10 = add(B11, B12, K);
    
    // Estas son las 7 recursiones
    Matrix P1 = strassen(A11, S1, K);
    Matrix P2 = strassen(S2, B22, K);
    Matrix P3 = strassen(S3, B11, K);
    Matrix P4 = strassen(A22, S4, K);
    Matrix P5 = strassen(S5, S6, K);
    Matrix P6 = strassen(S7, S8, K);
    Matrix P7 = strassen(S9, S10, K);

    Matrix temp1 = add(P5, P4, K);
    Matrix temp2 = add(temp1, P6, K);
    Matrix C11 = subtract(temp2, P2, K);
    deleteMatrix(temp1, K);
    deleteMatrix(temp2, K);
    Matrix C12 = add(P1, P2, K);
    Matrix C21 = add(P3, P4, K);
    Matrix temp3 = add(P5, P1, K);
    Matrix temp4 = subtract(temp3, P3, K);
    Matrix C22 = subtract(temp4, P7, K);
    deleteMatrix(temp3, K);
    deleteMatrix(temp4, K);
    for (unsigned int i = 0; i < K; i++) {
        for (unsigned int j = 0; j < K; j++) {
            C[i][j] = C11[i][j];
            C[i][j + K] = C12[i][j];
            C[K + i][j] = C21[i][j];
            C[K + i][K + j] = C22[i][j];
        }
    }
    deleteMatrix(A11, K); deleteMatrix(A12, K);
    deleteMatrix(A21, K); deleteMatrix(A22, K);
    deleteMatrix(B11, K); deleteMatrix(B12, K);
    deleteMatrix(B21, K); deleteMatrix(B22, K);
    deleteMatrix(S1, K);  deleteMatrix(S2, K);
    deleteMatrix(S3, K);  deleteMatrix(S4, K);
    deleteMatrix(S5, K);  deleteMatrix(S6, K);
    deleteMatrix(S7, K);  deleteMatrix(S8, K);
    deleteMatrix(S9, K);  deleteMatrix(S10, K);
    deleteMatrix(P1, K);  deleteMatrix(P2, K);
    deleteMatrix(P3, K);  deleteMatrix(P4, K);
    deleteMatrix(P5, K);  deleteMatrix(P6, K);
    deleteMatrix(P7, K);
    deleteMatrix(C11, K); deleteMatrix(C12, K);
    deleteMatrix(C21, K); deleteMatrix(C22, K);
    return C;
}

// Para llamar al algoritmo desde matrix_multiplication.cpp
vector<vector<int>> Llamar_strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    Matrix matA = createMatrix(n);
    Matrix matB = createMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matA[i][j] = A[i][j];
            matB[i][j] = B[i][j];
        }
    }
    Matrix matC = strassen(matA, matB, n);
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = static_cast<int>(matC[i][j]);
        }
    }
    deleteMatrix(matA, n);
    deleteMatrix(matB, n);
    deleteMatrix(matC, n);
    return C;
}