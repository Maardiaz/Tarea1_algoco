// Tarea 1: Algoritmos y Complejidad (INF-221) Semestre 2026-2
// Autor: Martín Angelo Araya Díaz
// Rol: 202473646-9
#include <bits/stdc++.h>
#include <sys/resource.h>

using namespace std;

// Declaración de las funciones de algoritmos
vector<vector<int>> Llamar_naive(const vector<vector<int>>& A, const vector<vector<int>>& B);
vector<vector<int>> Llamar_strassen(const vector<vector<int>>& A, const vector<vector<int>>& B);

size_t getHWMKB() {
    ifstream status("/proc/self/status");
    string line;
    while (getline(status, line)) {
        if (line.rfind("VmHWM:", 0) == 0) {
            stringstream ss(line.substr(6));
            size_t kb;
            ss >> kb;
            return kb;
        }
    }
    return 0;
}

vector<vector<int>> readMatrix(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> matrix;
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        vector<int> row;
        int val;
        while (ss >> val) {
            row.push_back(val);
        }
        if (!row.empty()) {
            matrix.push_back(row);
        }
    }
    file.close();
    return matrix;
}

void measureAndSaveMatrix(const string& algName, const string& baseName,
                          function<vector<vector<int>>(const vector<vector<int>>&, const vector<vector<int>>&)> algFunc,
                          const vector<vector<int>>& A, const vector<vector<int>>& B) {

    size_t hwmBefore = getHWMKB();
    auto start = chrono::high_resolution_clock::now();
    vector<vector<int>> C = algFunc(A, B);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = end - start;
    size_t hwmAfter = getHWMKB();
    size_t memoryUsed = (hwmAfter > hwmBefore) ? (hwmAfter - hwmBefore) : 0;
    string measureFileName = "data/measurements/" + baseName + "_" + algName + "_measurements.txt";
    ofstream measureFile(measureFileName);
    if (measureFile.is_open()) {
        measureFile << "Algoritmo: " << algName << "\n";
        measureFile << "Tiempo_ms: " << elapsed.count() << "\n";
        measureFile << "Memoria_KB: " << memoryUsed << "\n";
        measureFile.close();
    }
    string outputFileName = "data/matrix_output/" + baseName + "_" + algName + "_out.txt";
    ofstream outputFile(outputFileName);
    if (outputFile.is_open()) {
        for (size_t i = 0; i < C.size(); ++i) {
            for (size_t j = 0; j < C[i].size(); ++j) {
                outputFile << C[i][j] << (j == C[i].size() - 1 ? "" : " ");
            }
            outputFile << "\n";
        }
        outputFile.close();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: ./matrix_app <ruta_al_archivo_1>" << endl;
        return 1;
    }

    string inputFileName1 = argv[1];
    string baseName = inputFileName1;
    size_t lastSlash = baseName.find_last_of("/\\");
    if (lastSlash != string::npos) baseName = baseName.substr(lastSlash + 1);
    size_t suffixPos = baseName.find("_1.txt");
    if (suffixPos != string::npos) {
        baseName = baseName.substr(0, suffixPos);
    } else {
        size_t dotPos = baseName.find_last_of(".");
        if (dotPos != string::npos) baseName = baseName.substr(0, dotPos);
    }
    string path1 = "data/matrix_input/" + baseName + "_1.txt";
    string path2 = "data/matrix_input/" + baseName + "_2.txt";
    vector<vector<int>> A = readMatrix(path1);
    vector<vector<int>> B = readMatrix(path2);

    if (A.empty() || B.empty()) {
        cerr << "Error: No se pudieron leer las matrices o estan vacias." << endl;
        return 1;
    }
    measureAndSaveMatrix("naive", baseName, Llamar_naive, A, B);
    measureAndSaveMatrix("strassen", baseName, Llamar_strassen, A, B);

    return 0;
}