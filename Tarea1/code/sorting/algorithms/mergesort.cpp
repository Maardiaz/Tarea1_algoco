// Tarea 1: Algoritmos y Complejidad (INF-221) Semestre 2026-2
// Autor: Martín Angelo Araya Díaz
// Rol: 202473646-9
// Referencia / Bibliografía:
// Algoritmo sacado de "C++ Program for Merge Sort" - GeeksforGeeks.
// https://www.geeksforgeeks.org/cpp/cpp-program-for-merge-sort/


// Explicación general del código:
// Lo que hace el codigo es primero recibir por refeerncia el arreglo, luego separa el arreglo en 2 partes y se llama recursivamente
// en cada recursión lo que hace es dividir cada mitad hasta llegar al caso base, técnicamente primero genera el arbol de recursión izquierdo
// entonces se va cortando el arreglo hasta que llegue al caso base (ordenado) y vuelve al anterior, luego ordena el sub arreglo mas grande 
// Complejidad Temporal: θ(n log n) 
// Complejidad Espacial: O(n) por los vectores auxiliares 

#include <vector>
using namespace std;
void merge(vector<int>& vec, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> leftVec(n1), rightVec(n2);
    for (i = 0; i < n1; i++)
        leftVec[i] = vec[left + i];
    for (j = 0; j < n2; j++)
        rightVec[j] = vec[mid + 1 + j];
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftVec[i] <= rightVec[j]) {
            vec[k] = leftVec[i];
            i++;
        } else {
            vec[k] = rightVec[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        vec[k] = leftVec[i];
        i++;
        k++;
    }
    while (j < n2) {
        vec[k] = rightVec[j];
        j++;
        k++;
    }
}
void mergeSort(vector<int>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}
// Para llamar en el sorting.cpp
void Llamar_mergesort(vector<int>& arr) {
    if (!arr.empty()) {
        mergeSort(arr, 0, arr.size() - 1);
    }
}