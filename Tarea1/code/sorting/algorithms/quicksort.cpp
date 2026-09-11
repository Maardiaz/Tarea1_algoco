// Tarea 1: Algoritmos y Complejidad (INF-221) Semestre 2026-2
// Autor: Martín Angelo Araya Díaz
// Rol: 202473646-9
// Algoritmo sacado de "C++ Program For Quick Sort" - GeeksforGeeks.
// https://www.geeksforgeeks.org/cpp/cpp-program-for-quicksort/





// El funcionamiento del quiksort es que recibe el arreglo por referencia, luego lo que hace es elegir un
// elemento random del arreglo como pivote (esto lo cambié de la implementacion original de geeksforgeeks) porque 
// en esta usan el ultimo elemento y me daba error para entradas grandes.
// Luego de seleccionar el pivote lo deja al final y usa 2 punteros para ir recorriendo el arreglo e ir intercambiando las posiciones
// de los numeros menores y mayores que el pivote, luego en el luegar donde los punteros coincidan es donde va el pivote originalmente 
// hace que todos los menores al pivote esten a la izquierda y todos los mayores a la derecha, luego de forma recursiva
// lo que hace es aplicar esto mismo para los otros subarreglos

// Complejidad Temporal: O(n log n) caso promedio o O(n^2) en el peor caso 
// Complejidad Espacial: O(log n) debido a la pila de llamadas recursivas.

#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>

using namespace std;


int partition(vector<int>& vec, int low, int high) {
    // Seleccionar un índice aleatorio como pivote
    int randomIndex = low + rand() % (high - low + 1);
    swap(vec[randomIndex], vec[high]);
    int pivot = vec[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return i + 1;
}
void quickSort(vector<int>& vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}
// Para usar en sorting.cpp
void Llamar_quicksort(vector<int>& arr) {
    if (!arr.empty()) {
        static bool seeded = false;
        if (!seeded) {
            srand(time(NULL));
            seeded = true;
        }
        quickSort(arr, 0, arr.size() - 1);
    }
}