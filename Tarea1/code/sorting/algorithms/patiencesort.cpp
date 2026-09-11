// Tarea 1: Algoritmos y Complejidad (INF-221) Semestre 2026-2
// Autor: Martín Angelo Araya Díaz
// Rol: 202473646-9
// Algoritmo sacado de "Patience Sorting" - GeeksforGeeks
// https://www.geeksforgeeks.org/dsa/patience-sorting/


// Se basa en la idea de distribuir los elementos en "pilas" decrecientes y
// luego fusionarlas para obtener la secuencia ordenada.
// Este algoritmo se basa en usar pilas para ordenar los elementos.
// Lo que hace este algoritmo es, primero recibir el vector por referencia, luego se itera sobre cada elemento del arreglo y se busca
// algun otro elemento que sea mayor de izquierda a derecha, entonces lo apila, esto hace que cada pila esté ordenada de forma decreciente
// en caso de que no haya algun elemento entonces se usa este como base de una nueva pila.
// Finalmente cuando están todas las pilas listas, va viendo el elemento de arriba y va comparando cuales son menores y estos los va dejando
// en el arreglo, haciendo que al final quede ordenadó de menor a mayor.

// Complejidad Temporal: O(n^2) en este caso (La implementación de geeksforgeeks tiene esta complejidad).
// En teoría debería ser  O(nlgn)
// Complejidad Espacial: O(n) debido al almacenamiento de las pilas.

#include <vector>
#include <climits>
using namespace std;
vector<int> merge_piles(vector<vector<int>>& v) {
    vector<int> ans;
    while (1) {
        int minu = INT_MAX;
        int index = -1;
        for (size_t i = 0; i < v.size(); i++) {
            if (minu > v[i][v[i].size() - 1]) {
                minu = v[i][v[i].size() - 1];
                index = i;
            }
        }
        ans.push_back(minu);
        v[index].pop_back();

        if (v[index].empty()) {
            v.erase(v.begin() + index);
        }

        if (v.size() == 0)
            break;
    }
    return ans;
}
// Para llamar en sorting.cpp
void Llamar_patiencesort(vector<int>& arr) {
    if (arr.empty()) return;

    vector<vector<int>> piles;

    // Distribuir elementos en las pilas
    for (size_t i = 0; i < arr.size(); i++) {
        if (piles.empty()) {
            vector<int> temp;
            temp.push_back(arr[i]);
            piles.push_back(temp);
        }
        else {
            int flag = 1;
            for (size_t j = 0; j < piles.size(); j++) {
                if (arr[i] < piles[j][piles[j].size() - 1]) {
                    piles[j].push_back(arr[i]);
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                vector<int> temp;
                temp.push_back(arr[i]);
                piles.push_back(temp);
            }
        }
    }
    arr = merge_piles(piles);
}