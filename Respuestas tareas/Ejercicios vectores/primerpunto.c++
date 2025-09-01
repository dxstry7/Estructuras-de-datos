#include <iostream>
using namespace std;

class Vector {
private:
    int *storage;

public:
    Vector() {storage = new int[10];} //QUEDA EN EL HEAP
    ~Vector() {delete[] storage;} //LIBERA EL HEAP
    void LlenarEspacios () {
        for (int i = 0; i < 10; i++) {
            storage[i] = i;
        }
    }
    void MostrarElementos () {
        for (int i = 0; i < 10; i++) {
            printf("Elemento %d: %d\n", i+1, storage[i]);
        }
        cout << endl;
    }
    int* getStorage() { return storage; }
int SumaElementos(int *A) {
    int suma = 0;
    for (int i = 0; i < 10; i++) {
        suma += A[i];
    };
    return suma;
}
}; // Cierra la definición de la clase Vector

int SumaElementos(int *A) {
    int suma = 0;
    for (int i = 0; i < 10; i++) {
        suma += A[i];
    }
    return suma;
}

int main() {
    Vector B;
    B.LlenarEspacios();
    B.MostrarElementos();
    int suma = SumaElementos(B.getStorage());
    cout << "La suma de los elementos es: " << suma << endl;
    return 0;
}
