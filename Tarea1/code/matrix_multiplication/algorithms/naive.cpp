// Tarea 1: Algoritmos y Complejidad (INF-221) Semestre 2026-2
// Autor: Martín Angelo Araya Díaz
// Rol: 202473646-9
// Algoritmo extraído y adaptado de "Matrix multiplication in C++.
// https://www.studymite.com/cpp/examples/multiply-two-matrices-in-cpp



// El funcionamiento de naive es que basciamente con el primer for recorre todas las filas "i" de la primera matriz, luego con el 
// segundo for recorre las columnas "j" de la segunda matriz y con el tercer for va acomulando el resultado de la multiplicacion
// para el elemento en la posición [i][j]

// Complejidad Temporal: O(n^3)
// Complejidad Espacial: O(n^2)
#include <vector>

using namespace std;

//Para llamar a la función en el matrix_multiplication.cpp
vector<vector<int>> Llamar_naive(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}