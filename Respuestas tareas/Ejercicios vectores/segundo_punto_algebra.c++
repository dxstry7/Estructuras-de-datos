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
// ---------------------------------------------------------
// (2) Clase plantilla MatrizAlgebra
// ---------------------------------------------------------
class MatrizAlgebra {
    private:
        int filas, columnas;
        AlgebraVector<double>** storage;
    public: 
        // ------------------------------------------ CONSTRUCTORES ------------------------------------------
        MatrizAlgebra(int f, int c) { //INICIALIZA UNA MATRIZ DE DIMENSIONES F*C CON TODOS SUS ELEMENTOS EN 0
            filas = f;
            columnas = c;
            storage = new AlgebraVector<double>*[filas];
            for (int i = 0; i < filas; ++i) {
                storage[i] = new AlgebraVector<double>(columnas);
            }
        }
        MatrizAlgebra(int f, int c, const double init[]) { //INICIALIZA UNA MATRIZ DE DIMENSIONES F*C COPIANDO LOS DATOS DE UN ARRAY
            filas = f;
            columnas = c;
            storage = new AlgebraVector<double>*[filas];
            for (int i = 0; i < filas; ++i) {
                storage[i] = new AlgebraVector<double>(columnas, &init[i * columnas]);
            }
        }
        MatrizAlgebra(const MatrizAlgebra& other) { //CONSTRUCTOR DE COPIA
            filas = other.filas;
            columnas = other.columnas;
            storage = new AlgebraVector<double>*[filas];
            for (int i = 0; i < filas; ++i) {
                storage[i] = new AlgebraVector<double>(*(other.storage[i]));
            }
        }
        ~MatrizAlgebra() { //DESTRUCTOR
            for (int i = 0; i < filas; ++i) {
                delete storage[i];
            }
            delete[] storage;
        }
        // ------------------------------------------ METODOS ------------------------------------------
        MatrizAlgebra SumaMatrices (const MatrizAlgebra& other) {
            if (filas != other.filas || columnas != other.columnas) {
                std::cout <<"Error: To do the sum, both matrices musth have the same dimensions. \n";
                return MatrizAlgebra(0,0);
            } else {
                MatrizAlgebra ResultadoSuma (filas, columnas);
                for (int i = 0; i < filas; i++) {
                    for (int j = 0; j < columnas; j++) {
                        ResultadoSuma.storage[i][j] = storage[i][j].SumaVectores(other.storage[i][j]);
                    }
                }
            }
        }

        MatrizAlgebra MultiplicacionEscalar (int escalar) {
            MatrizAlgebra ResultadoM (filas, columnas);
            for (int i = 0; i < filas; i++) {
                *(ResultadoM.storage[i]) = storage[i]->MultiplicacionEscalar(escalar);
            }
        }

        MatrizAlgebra Transpuesta () {
            MatrizAlgebra ResultadoT (columnas, filas);
            for (int i = 0; i < columnas; i++) {
                for (int j = 0; j < filas; j++) {
                    ResultadoT.storage[i][j] = storage[j][i];
                }
            }
            return ResultadoT;
        }

        MatrizAlgebra VectorMatriz(const MatrizAlgebra& vec) { //SE TOMARÁ DE LA FORMA Ax = B
            if (columnas != vec.filas) {
                std::cout <<"Error: The number of columns in the first matrix must be equal to the number of rows in the second matrix.\n";
                return MatrizAlgebra(0,0);
            } 
            MatrizAlgebra ResultadoVM (filas, vec.columnas);
            for (int i = 0; i < filas; i++) {
                double suma = 0;
                for (int j = 0; j < vec.columnas; j++) {
                    suma += storage[i][j].ProductoPunto(vec.storage[j][0]);
                }
                ResultadoVM.storage[i][0] = suma;
            }
            return ResultadoVM;
    }
        MatrizAlgebra ImprimirMatriz() {
            for (int i = 0; i < filas; i++) {
                storage[i]->ImprimirVector();
                std::cout << std::endl;
            }
        }
};

int main () {
    // ---------------------------------------------------------
    double matrizA[] = {
        1, 3, 0,
        2, 4, 1,
        0, 5, 6
    };
    double matrizB[] = {
        2, 3, 4,
        9, 8, 7,
        6, 5, 4
    };
    double vectorX[] = {
        1,
        0,
        3
    };
    MatrizAlgebra A(3, 3, matrizA);
    MatrizAlgebra B(3, 3, matrizB);
    MatrizAlgebra X(3, 1, vectorX);
    
    std::cout << "Matriz A: \n";
    A.ImprimirMatriz();
    std::cout << "Matriz B: \n";
    B.ImprimirMatriz();
    std::cout << "Vector X: \n";
    X.ImprimirMatriz();

    std::cout << "Suma de A y B: \n";
    MatrizAlgebra C = A.SumaMatrices(B);
    C.ImprimirMatriz();
    std::cout << "Multiplicación de A por el escalar 2: \n";
    MatrizAlgebra D = A.MultiplicacionEscalar(2);
    D.ImprimirMatriz();
    std::cout << "Transpuesta de A: \n";
    MatrizAlgebra E = A.Transpuesta();
    E.ImprimirMatriz();
    std::cout << "Producto de A por el vector X: \n";
    MatrizAlgebra F = A.VectorMatriz(X);
    F.ImprimirMatriz();
}