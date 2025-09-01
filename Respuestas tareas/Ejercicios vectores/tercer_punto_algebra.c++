#include <iostream>
#include <cmath>
using namespace std;
// ---------------------------------------------------------
// (1) Clase plantilla AlgebraVector
// ---------------------------------------------------------
template <typename V> class AlgebraVector {
    private:
        V *storage; //Puntero al heap
        int size; //Dimensión del vector
    public:
        // ------------------------------------------ CONSTRUCTORES ------------------------------------------
        AlgebraVector(int s) { //INICIALIZA UN VECTOR DE DIMENSIÓN s, este solo es para crear un vector de ceros sin copiar datos de un array
            size = s;
            storage = new V[s]; //Reserva memoria en el heap
            for (int i = 0; i < s; i++) {
                storage[i] = 0; //Inicializa en 0
            }
        }
        AlgebraVector (int s, const V init[]) {
            size = s;
            storage = new V[s];
            for (int i = 0; i < s; i++) {
                storage[i] = init[i];
            }
        }
        AlgebraVector (const AlgebraVector& other) { //CONSTRUCTOR DE COPIA
            size = other.size;
            storage = new V[other.size];
            for (int i = 0; i < other.size; i++) {
                storage[i] = other.storage[i];
            }
        }
        ~AlgebraVector() { //DESTRUCTOR
            delete[] storage; //Libera memoria en el heap
        }
        // ------------------------------------------ METODOS ------------------------------------------
        AlgebraVector<V> SumaVectores (const AlgebraVector& other) {
            if (size != other.size) {
                std::cout <<"Error: Los vectores deben tener la misma dimensión para sumar.\n";
                return AlgebraVector<V>(0);
            } else {
                AlgebraVector<V> ResultadoSuma(size);
                for (int i = 0; i < size; i++) {
                    ResultadoSuma.storage[i] = storage[i] + other.storage[i];
                }
                return ResultadoSuma;
            }
        };
        AlgebraVector<V> RestaVectores (const AlgebraVector& other) {
            if (size != other.size) {
                std::cout <<"Error: Los vectores deben tener la misma dimensión para restar.\n";
                return AlgebraVector<V>(0);
            } else {
                AlgebraVector<V> ResultadoResta(size);
                for (int i = 0; i < size; i++) {
                    ResultadoResta.storage[i] = storage[i] - other.storage[i];
                }
                return ResultadoResta;
            }
        }
        AlgebraVector<V> MultiplicacionEscalar (double escalar) const {
            AlgebraVector<V> ResultadoMultiplicacion(size);
            for (int i = 0; i < size; i++) {
                ResultadoMultiplicacion.storage[i] = storage[i] * escalar;
            }
            return ResultadoMultiplicacion;
        };
        V ProductoPunto (const AlgebraVector& other) const {
            if (size != other.size){
                std:: cout <<"Error: Los vectores deben tener la misma dimensión para el producto punto.\n";
                return 0;
            } else {    
                V resultado = 0;
                for (int i = 0; i < size; i++) {
                    resultado += storage[i] * other.storage[i];
                }
                return resultado;
            }
        };
        V Magnitud () const {
            V discriminante = 0;
            for (int i = 0; i< size; i++) {
                discriminante += storage[i] * storage[i];
            }
            return sqrt(discriminante);
        };
        AlgebraVector<V> ImprimirVector() {
            for (int i = 0; i < size; i++) {
                std::cout << storage[i] << " ";
            }
            return *this;
        };
};