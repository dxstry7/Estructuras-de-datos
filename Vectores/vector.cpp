#include <iostream>
using namespace std;

template <typename T> class Vector { // DECLARACIÓN DE LA PLANTILLA CLASE VECTOR PARA CUALQUIER TIPO DE DATO, AL USAR TEMPLATE SE PERMITE CUALQUIER TIPO DE DATO
    private:
        T* data; //PUNTERO AL ARRAY DINÁMICO
        unsigned int size; //TAMAÑO ACTUAL DEL VECTOR (NÚMERO DE ELEMENTOS ALMACENADOS)
        unsigned int capacity; //MAX NUMBERS OF ELEMENTS THE VECTOR CAN HOLDING WITHOUT RESIZING
        double policy; //POLÍTICA DE REDIMENSIONAMIENTO
    public:
        // CONSTRUCTORES
        Vector () { //CONSTRUCTOR POR DEFECTO
            data = nullptr;
            size = 0;
            capacity = 0;
            policy = 1.5;
        }
        Vector(unsigned int cap, double p = 1.5) { //CONSTRUCTOR PARA UN TAMAÑO INICIAL
            data = new T[cap]; //RESERVA DE MEMORIA DINÁMICA PARA EL ARRAY
            size = 0;
            capacity = cap;
            policy = p;
        }
        Vector(const Vector<T> &other, double p = 1.5) { // CONSTRUCTOR DE COPIA
            size = other.size;
            capacity = other.capacity;
            policy = p;
            if (capacity == 0) {
                data = nullptr;
            } else {
                data = new T[capacity];
                for (unsigned int i = 0; i < size; i++) {
                    data[i] = other.data[i];
                }
            }
        }
        ~Vector() { //DESTRUCTOR
            delete[] data; //LIBERAR LA MEMORIA ASIGNADA
        }
        void resize () {
            capacity = static_cast<unsigned int>(capacity * policy);
            T* newData = new T[capacity];
            for (unsigned int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        void reserve (const Vector<T>& other, unsigned int cantidad) { //RESERVAR ESPACIO (No sigue la política de redimensionamiento)

        }
    public: //METODOS
        void push_back(const T& value) { //VALOR
            if (size >= capacity) {
                resize();
            }
            data[size] = value;
            size++;
        }
        void push_back(const Vector<T>& other) {// OTRO VECTOR
            while (size + other.size > capacity) {
                resize();
            }
            for (unsigned int i = 0; i < other.size; i++) {
                data[size + i] = other.data[i];
            }
            size += other.size;
        }
        void pop_back() { //ELIMINAR EL ÚLTIMO ELEMENTO
            if (size > 0) {
                size--; //AL DISMINUIR EL TAMAÑO YA NO SE PUEDE ACCEDER AL EL, CUANDO SE USA PUSHBACK SE SOBREESCRIBE
            }
        }
        void insert(unsigned int index, const T& value) { //INSERTAR UN ELEMENTO EN UNA POSICIÓN DETERMINADA, NO TIENE EN CUENTA EL ESTANDAR DE C++
            if (index == 0 || index > size + 1) {
                throw out_of_range("Index out of range");
            }
            unsigned int fixed_index = index - 1;
            if (size >= capacity) {
                resize();
            for (unsigned int i = size; i > fixed_index; i--) {
                data[i] = data[i-1];
            }
            data[fixed_index] = value;
            size++;
        }
        void erase(unsigned int index) { // ELIMINAR UN ELEMENTO EN UNA POSICIÓN DETERMINADA
            if (size == 0) {
                throw out_of_range("Cannot erase from an empty vector");
            }
            if (index == 0 || index > size) {
                throw out_of_range("Index out of range");
            }
            unsigned int fixed_index = index - 1;
            for (unsigned int i = fixed_index; i < size - 1; i++) {
                data[i] = data[i + 1];
            }
            size--;
        }
        unsigned int getSize () const { //DEVUELVE EL TAMAÑO ACTUAL DEL VECTOR
            return size;
        }
        void shrink_to_fit() { //AJUSTAR LA CAPACIDAD AL TAMAÑO ACTUAL
            if (capacity> size) {
                newData = new T[size];
                for (unsigned int i = 0; i < size; i++) {
                    newData[i] = data[i];
                }
                delete[] data;
                data = newData;
                capacity = size;
            }
        }
        T &operator[](unsigned int index) {
            return data[index];
        }
        const T &operator[](unsigned int index) const {
            return data[index];
        }

        T &at(unsigned int index) {
            if (index >= size) {
                throw out_of_range("Index out of range");
            }
            return data[index];
        }

        const T &at(unsigned int index) const {
            if (index >= size) {
                throw out_of_range("Index out of range");
            }
            return data[index];
        }

        bool empty() const { return size == 0; } 
    }  
};