#include <iostream>
#include <fstream>
#include <vector>

// Funcion ´para imprimir el contenido del vector
void printVector(const std::vector<int>& vec) {
    for (const auto& num : vec) {
        std::cout << num << ' ';
    }
    std::cout << '\n';
}

// Funcion para preguntar los valores de la matriz
void fillVector(std::vector<int>& vec) {
    for (auto& num : vec) {
        std::cout << "Enter a number: ";
        std::cin >> num;
    }
}

// Funcion para guardar el contenido del vector en el archivo binario
void saveVectorToBinaryFile(const std::vector<int>& vec, const std::string& fileName) {
    std::ofstream outputFile(fileName, std::ios::binary);
    if (!outputFile) {
        std::cerr << "No se puede abrir el archivo de salida.\n";
        return;
    }
    for (const auto& num : vec) {
        outputFile.write(reinterpret_cast<const char*>(&num), sizeof(num));
    }
    outputFile.close();
}

// Funcion para cargar el contenido del vector desde el archivo binario
void loadVectorFromBinaryFile(std::vector<int>& vec, const std::string& fileName) {
    std::ifstream inputFile(fileName, std::ios::binary);
    if (!inputFile) {
        std::cerr << "No se peude abrir el archivo de entrada.\n";
        return;
    }
    vec.clear();
    int num;
    while (inputFile.read(reinterpret_cast<char*>(&num), sizeof(num))) {
        vec.push_back(num);
    }
    inputFile.close();
}

int main() {
    int size;
    std::cout << "Ingrese el tamaño de la matriz: ";
    std::cin >> size;

    std::vector<int> vec(size);
    fillVector(vec);

    std::cout << "Contenido del vector: ";
    printVector(vec);

    std::string fileName = "vectorData.bin";
    saveVectorToBinaryFile(vec, fileName);

    vec.clear();
    loadVectorFromBinaryFile(vec, fileName);

    std::cout << "Vector contenido despues de ser cargado del archivo binario: ";
    printVector(vec);

    return 0;
}