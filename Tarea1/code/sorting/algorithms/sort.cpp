// Tarea 1: Algoritmos y Complejidad (INF-221) Semestre 2026-2
// Autor: Martín Angelo Araya Díaz
// Rol: 202473646-9
#include <algorithm>
#include <vector>
using namespace std;

std::vector<int> sortArray(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());  // std::sort de la STL
    return arr;
}
// Para llamar a sort sin retornar una copia
void Llamar_stdsort(vector<int>& arr) {
    std::sort(arr.begin(), arr.end());
}
