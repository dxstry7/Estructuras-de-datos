#include <iostream>
#include <unordered_set>
#include "vector.h"
using namespace std;

// 🔧 Función plantilla para eliminar duplicados en O(n)
template <typename T>
void eliminar_duplicados(Vector<T>& vector) {
    unordered_set<T> seen;
    unsigned int i = 0;
    while (i < vector.getSize()) {
        if (seen.find(vector[i]) != seen.end()) {
            vector.erase(i);
        } else {
            seen.insert(vector[i]);
            i++;
        }
    }
}

int main() {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(3);
    vec.push_back(3);

    cout << "Vector original: ";
    for (size_t i = 0; i < vec.getSize(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    // Elimina los elementos duplicados del vector 'vec' en O(n) tiempo, modificando el vector original.
    eliminar_duplicados(vec);

    cout << "Vector sin duplicados: ";
    for (size_t i = 0; i < vec.getSize(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    return 0;
}
