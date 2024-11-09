#include "trees/rb.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

using namespace std;
using namespace trees;
using namespace std::chrono;

// Función para leer llaves desde un archivo binario
int* readKeysFromFile(const string& filename, int* n_keys) {
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cerr << "Error al abrir el archivo: " << filename << endl;
        *n_keys = 0;
        return nullptr;
    }

    char* val = new char[4];
    int n = 0;

    // Contar la cantidad de llaves en el archivo
    fin.read(val, 4);
    while (!fin.eof()) {
        n++;
        fin.read(val, 4);
    }
    fin.close();

    // Leer las llaves en un arreglo
    fin.open(filename, ios::binary);
    int* keys = new int[n];
    for (int i = 0; i < n; i++) {
        fin.read(val, 4);
        keys[i] = *reinterpret_cast<int*>(val);
    }
    fin.close();

    *n_keys = n;
    delete[] val;
    return keys;
}

int main() {
    int n_data = 0;

    // Usa la ruta absoluta para los archivos de datos
    string dataFilename = "/home/santiago/eda/eda_cpp/rb_tree/data_trees/keys_sorted_1024.bin";
    string queryFilename = "/home/santiago/eda/eda_cpp/rb_tree/data_trees/data_trees/queries_1000.bin";

    // Lee las llaves del archivo para insertar
    int* data = readKeysFromFile(dataFilename, &n_data);
    if (data == nullptr) {
        cerr << "Error al cargar las llaves de inserción desde: " << dataFilename << endl;
        return 1;
    }

    // Crear el árbol Red-Black
    RB rbtree;

    // Medir el tiempo de inserción de las llaves en el árbol
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n_data; i++) {
        rbtree.insert(data[i]);
    }
    auto end = high_resolution_clock::now();
    auto insertTime = duration_cast<milliseconds>(end - start).count();
    cout << "Tiempo de inserción desde " << dataFilename << ": " << insertTime << " ms" << endl;

    // Lee las llaves para realizar las búsquedas
    int n_queries = 0;
    int* queries = readKeysFromFile(queryFilename, &n_queries);
    if (queries == nullptr) {
        cerr << "Error al cargar las llaves de consulta desde: " << queryFilename << endl;
        delete[] data; // Liberar memoria antes de salir
        return 1;
    }

    // Medir el tiempo de búsqueda de las llaves en el árbol
    start = high_resolution_clock::now();
    for (int i = 0; i < n_queries; i++) {
        rbtree.find(queries[i]);
    }
    end = high_resolution_clock::now();
    auto searchTime = duration_cast<milliseconds>(end - start).count();
    cout << "Tiempo de búsqueda en " << queryFilename << ": " << searchTime << " ms" << endl;

    // Liberar memoria asignada para las llaves y consultas
    delete[] data;
    delete[] queries;

    return 0;
}


