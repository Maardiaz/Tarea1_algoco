#include <bits/stdc++.h>
#include <sys/resource.h>
using namespace std;

void Llamar_mergesort(vector<int>& arr);
void Llamar_patiencesort(vector<int>& arr);
void Llamar_quicksort(vector<int>& arr);
void Llamar_stdsort(vector<int>& arr);  
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

void measureAndSave(const string& algName, const string& baseName,
                    function<void(vector<int>&)> algFunc, vector<int> arr) {
    size_t hwmBefore = getHWMKB();
    auto start = chrono::high_resolution_clock::now();
    algFunc(arr);
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
    string outputFileName = "data/array_output/" + baseName + "_" + algName + "_out.txt";
    ofstream outputFile(outputFileName);
    if (outputFile.is_open()) {
        for (size_t i = 0; i < arr.size(); ++i) {
            outputFile << arr[i] << (i == arr.size() - 1 ? "" : " ");
        }
        outputFile.close();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    string inputFileName = argv[1];
    string baseName = inputFileName;
    size_t lastSlash = baseName.find_last_of("/\\");
    if (lastSlash != string::npos) baseName = baseName.substr(lastSlash + 1);
    size_t lastDot = baseName.find_last_of(".");
    if (lastDot != string::npos) baseName = baseName.substr(0, lastDot);
    ifstream inputFile(inputFileName);
    vector<int> arrOriginal;
    int number;
    while (inputFile >> number) arrOriginal.push_back(number);
    inputFile.close();
    cout << "Procesando: " << baseName << endl;
    cout << "  Iniciando std_sort..." << endl;
    measureAndSave("std_sort", baseName, Llamar_stdsort, arrOriginal);
    cout << "  Iniciando quicksort..." << endl;
    measureAndSave("quicksort", baseName, Llamar_quicksort, arrOriginal);
    cout << "  Iniciando mergesort..." << endl;
    measureAndSave("mergesort", baseName, Llamar_mergesort, arrOriginal);
    cout << "  Iniciando patiencesort..." << endl;
    measureAndSave("patiencesort", baseName, Llamar_patiencesort, arrOriginal);
    return 0;
}