#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept> // Para std::out_of_range

// 🔹 Clase plantilla Vector<T>
template <typename T>
class Vector {
private:
    T* data;                // Apuntador al arreglo dinámico
    unsigned int size;      // Número de elementos actuales
    unsigned int capacity;  // Capacidad máxima antes de redimensionar
    double policy;          // Política de redimensionamiento

public:
    // 🔸 Constructores
    Vector();                                      // Constructor por defecto
    Vector(unsigned int cap, double p = 1.5);      // Constructor con capacidad inicial
    Vector(const Vector<T>& other, double p = 1.5);// Constructor de copia
    ~Vector();                                     // Destructor

    // 🔸 Métodos internos
    void resize();                                 // Redimensiona según la política
    void reserve(const Vector<T>& other, unsigned int cantidad); // Reservar espacio (sin implementar)

    // 🔸 Métodos públicos
    void push_back(const T& value);                // Agrega un elemento
    void push_back(const Vector<T>& other);        // Agrega otro vector
    void pop_back();                               // Elimina el último elemento
    void insert(unsigned int index, const T& value);// Inserta en posición (1-based)
    void erase(unsigned int index);                // Elimina en posición (1-based)
    void shrink_to_fit();                          // Ajusta capacidad al tamaño actual

    // 🔸 Acceso a elementos
    T& operator[](unsigned int index);             // Acceso sin verificación
    const T& operator[](unsigned int index) const; // Acceso sin verificación (const)
    T& at(unsigned int index);                     // Acceso con verificación
    const T& at(unsigned int index) const;         // Acceso con verificación (const)

    // 🔸 Utilidades
    unsigned int getSize() const;                  // Devuelve el tamaño actual
    bool empty() const;                            // Verifica si está vacío
};

// 🔹 Implementación de métodos plantilla

template <typename T>
Vector<T>::Vector() : data(nullptr), size(0), capacity(0), policy(1.5) {}

template <typename T>
Vector<T>::Vector(unsigned int cap, double p) : size(0), capacity(cap), policy(p) {
    data = new T[cap];
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other, double p) : size(other.size), capacity(other.capacity), policy(p) {
    if (capacity == 0) {
        data = nullptr;
    } else {
        data = new T[capacity];
        for (unsigned int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template <typename T>
void Vector<T>::resize() {
    capacity = static_cast<unsigned int>(capacity * policy);
    T* newData = new T[capacity];
    for (unsigned int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

template <typename T>
void Vector<T>::reserve(const Vector<T>& other, unsigned int cantidad) {
    // Método reservado para implementación futura
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size >= capacity) {
        resize();
    }
    data[size++] = value;
}

template <typename T>
void Vector<T>::push_back(const Vector<T>& other) {
    while (size + other.size > capacity) {
        resize();
    }
    for (unsigned int i = 0; i < other.size; ++i) {
        data[size + i] = other.data[i];
    }
    size += other.size;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size > 0) {
        --size;
    }
}

template <typename T>
void Vector<T>::insert(unsigned int index, const T& value) {
    if (index == 0 || index > size + 1) {
        throw std::out_of_range("Index out of range");
    }
    unsigned int fixed_index = index - 1;
    if (size >= capacity) {
        resize();
    }
    for (unsigned int i = size; i > fixed_index; --i) {
        data[i] = data[i - 1];
    }
    data[fixed_index] = value;
    ++size;
}

template <typename T>
void Vector<T>::erase(unsigned int index) {
    if (size == 0) {
        throw std::out_of_range("Cannot erase from an empty vector");
    }
    if (index == 0 || index > size) {
        throw std::out_of_range("Index out of range");
    }
    unsigned int fixed_index = index - 1;
    for (unsigned int i = fixed_index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (capacity > size) {
        T* newData = new T[size];
        for (unsigned int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = size;
    }
}

template <typename T>
T& Vector<T>::operator[](unsigned int index) {
    return data[index];
}

template <typename T>
const T& Vector<T>::operator[](unsigned int index) const {
    return data[index];
}

template <typename T>
T& Vector<T>::at(unsigned int index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
const T& Vector<T>::at(unsigned int index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
unsigned int Vector<T>::getSize() const {
    return size;
}

template <typename T>
bool Vector<T>::empty() const {
    return size == 0;
}

#endif // VECTOR_H
