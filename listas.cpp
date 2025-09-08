#include <iostream>
using namespace std;
// HAY QUE IMPLEMENTAR EXCEPCIONES, EL PROGRAMA TIENE QUE SER FÁCIL DE USAR Y DÍFICIL DE USAR MAL
// ------- DECLARACIÓN DE LA PLANTILLA CLASE PARA CUALQUIER TIPO DE DATO
template <typename T> class List {
  private:
    class Node {
    private:
      T data;
      Node *next;

    public:
      // --- CONSTRUCTOR DEL NODO ----
      Node() : data(), next(nullptr) {}

      // --- CONSTRUCTOR DEL NODO CON PARÁMETRO ----
      Node(const T& value) : data(value), next(nullptr) {}

      // --- MÉTODOS DEL NODO ----
      Node* getNext() const { return next; } // OBTENER EL PUNTERO DEL SIGUIENTE NODO

      const T& getvalue() const { return data; } // ← CORREGIDO: el tipo de retorno debe ser T, no Node
      T& getvalue() { return data; } // ← CORREGIDO: el tipo de retorno debe ser T, no Node

      void setNext(Node *n) { next = n; } // ASIGNAR EL PUNTERO DEL SIGUIENTE NODO
    };

    Node *first; // PUNTERO AL PRIMER NODO DE LA LISTA
    Node *last;  // PUNTERO AL ÚLTIMO NODO DE LA LISTA
    unsigned int sz;

  public:
    // --- CONSTRUCTORES DE LA LISTA ----
    List() : first(nullptr), last(nullptr), sz(0) {} // ← CORREGIDO: 'nullpt' debe ser 'nullptr'

    ~List() { // ← CORREGIDO: el destructor no debe tener guion
      Node *temp = first;
      while (first != nullptr) {
        temp = first;
        first = first->getNext();
        delete temp;
      }
      last = nullptr;
      sz = 0;
    }

    // --- MÉTODOS DE LA LISTA ----
    bool empty() const {
      return (first == nullptr || last == nullptr);
    }

    void push_back(const T& value) {
      Node *newNode = new Node(value);
      if (!empty()) { // CASO EN QUE LA LISTA YA TIENE ELEMENTOS
        last->setNext(newNode);
        last = newNode;
      } else {
        first = newNode;
        last = newNode;
      }
      sz++;
    }

    void pop_back() { // ELIMINA EL ÚLTIMO ELEMENTO DE LA LISTA
      if (!empty()) {
        if (first == last) { //ESTE ES EL CASO DONDE SOLO HAY UN ELEMENTO EN LA LISTA
          delete first;
          first = nullptr;
          last = nullptr;
          sz--;
        } else { // HAY MÁS DE UN ELEMENTO
          Node *temp = first;
          while (temp->getNext() != last) {
            temp = temp->getNext();
          }
          temp->setNext(nullptr); // ← CORREGIDO: temp es puntero, se accede con '->'
          delete last;
          last = temp;
          sz--;
        }
      } else {
        std::cout << "The list is empty, isn't possible delete the last element." << std::endl;
      }
    }

    void push_front(const T& value) { // INSERTA UN NUEVO ELEMENTO AL INICIO DE LA LISTA
      Node *newNode = new Node(value);
      if (!empty()) { // CASO EN EL QUE LA LISTA YA TIENE ELEMENTOS
        newNode->setNext(first);
        first = newNode;
        sz++;
      } else {
        first = newNode;
        last = newNode;
        sz++;
      }
    }

    void pop_front() { // ELIMINA EL PRIMER ELEMENTO DE LA LISTA
      if (!empty()) {
        Node *temp = first;
        first = first->getNext();
        delete temp;
        sz--;
        if (first == nullptr) { // SI LA LISTA QUEDA VACÍA, ACTUALIZAR 'last'
          last = nullptr;
        }
      } else {
        std::cout << "The list is empty, isn't possible delete the first element." << std::endl;
      }
    }
    T& front () { //DEVUELVE UN REFERENCIA AL PRIMER ELEMENTO DE LA LISTA, PERMITIENDO SU MODIFICACIÓN
      if (!empty()) {
        return first->getvalue();
      } else {
        std::cout << "The list is empty, isn't possible return the first element." << std::endl;
        exit(EXIT_FAILURE); // TERMINA EL PROGRAMA, ES ALGO MUY RADICAL YA QUE NO PERMITE RECUPERARSE, SE USA CUANDO HAY UN ERROR GRAVE
      }
    }
    const T& front () const { // DEVUELVE UNA REFERENCIA CONSTANTE AL PRIMER ELEMENTO DE LA LISTA, SIN PERMITIR SU MODIFICACIÓN
      if (!empty()) {
        return first->getvalue();
      } else {
        std::cout << "The list is empty, isn't possible return the first element." << std::endl;
        exit(EXIT_FAILURE); // XQ HAY QUE COLOCAR UN THROW O UN EXIT SI TENEMOS UN CONDICIONAL QUE VERIFICA SI LA LISTA ESTA VACÍA????????????????
      }
    }

    T& back() { //DEVUELVE UN REFERENCIA AL ÚLTIMO ELEMENTO DE LA LISTA, PERMITIENDO SU MODIFICACIÓN
      if (!empty()) {
        return last->getvalue();
      } else {
        std::cout << "The list is empty, isn't possible return the last element." << std::endl;
        exit(EXIT_FAILURE); // XQ HAY QUE COLOCAR UN THROW O UN EXIT SI TENEMOS UN CONDICIONAL QUE VERIFICA SI LA LISTA ESTA VACÍA????????????????
      }
    }
    const T& back() const { // DEVUELVE UNA REFERENCIA CONSTANTE AL ÚLTIMO ELEMENTO DE LA LISTA, SIN PERMITIR SU MODIFICACIÓN
      if (!empty()) {
        return last->getvalue();
      } else {
        std::cout << "The list is empty, isn't possible return the last element." << std::endl;
        exit(EXIT_FAILURE); // XQ HAY QUE COLOCAR UN THROW O UN EXIT SI TENEMOS UN CONDICIONAL QUE VERIFICA SI LA LISTA ESTA VACÍA????????????????
      }
    }
    unsigned int size() const { //DEVUELVE EL NÚMERO DE ELEMENTOS EN LA LISTA
      return sz; 
    }
    void clear() { //ELIMINA TODOS LOS ELEMENTOS DE LA LISTA
      Node *temp = first;
      while (first != nullptr) {
        temp = first;
        first = first->getNext();
        delete temp;
      }
      last = nullptr;
      sz = 0;
      /*
      TAMBIÉN SE PUEDE HACER ASÍ:
      while (!empty()) {
        pop_front(); // O popback();
      }
      */
    }
    // ---- ES COMO ESPACIOS VECTORIALES DONDE SE PUEDE DEFINIR COMO VA A COMPORTARSE UN OPERADOR A BASE DE LO QUE SE DEFINA EN LA FUNCIÓN ----
    const T& operator[](unsigned int index) const { //SOBRECARGA DEL OPERADOR DE SUBÍNDICE PARA ACCEDER A LOS ELEMENTOS DE LA LISTA
      if (index >= sz) {
        std::cout << "Index out of range." << std::endl;
        exit(EXIT_FAILURE); // XQ HAY QUE COLOCAR UN THROW O UN EXIT SI TENEMOS UN CONDICIONAL QUE VERIFICA SI EL ÍNDICE ESTÁ FUERA DE RANGO????????????????
      } else {
        Node *temp = first;
        for (unsigned int i = 0; i < index; i++) {
          temp = temp->getNext();
        }
        return temp->getvalue();
      }
    }
    T& operator[](unsigned int index) { //SOBRECARGA DEL OPERADOR DE SUBÍNDICE PARA PERMITIR LA MODIFICACIÓN DE ELEMENTOS
      if (index >= sz) {
        std::cout << "Index out of range." << std::endl;
        exit(EXIT_FAILURE); // XQ HAY QUE COLOCAR UN THROW O UN EXIT SI TENEMOS UN CONDICIONAL QUE VERIFICA SI EL ÍNDICE ESTÁ FUERA DE RANGO????????????????
      } else {
        Node *temp = first;
        for (unsigned int i = 0; i < index; i++) {
          temp = temp->getNext();
        }
        return temp->getvalue();
      }
    }
    void insert(unsigned int index, const T& val) {
      if (index > sz) {
        std::cout << "Index out of range" << std::endl;
        exit(EXIT_FAILURE); // XQ HAY QUE COLOCAR UN THROW O UN EXIT SI TENEMOS UN CONDICIONAL QUE VERIFICA SI EL ÍNDICE ESTÁ FUERA DE RANGO????????????????
      } else if (index == 0) {
        push_front(val);
      } else if (index == sz) {
        push_back(val);
      } else {
        Node *newNode = new Node(val);
        Node *temp = first; // PUNTERO TEMPORAL PARA RECORRER LA LISTA
        for (unsigned int i = 0; i < index - 1; i++) {
          temp = temp->getNext();
        } 
      } //EL BUCLE APUNTA A LA DIRECCIÓN ANTERIOR AL ÍNDICE DONDE SE DESEA INSERTAR
      newNode -> setNext (temp -> getNext());
      temp -> setNext (newNode);
      sz++;
    }
    void erase(unsigned int index) {
      if (index >= sz) {
          std::cout <<"Index out of range"<< std::endl;
      } else if (index == 0){
          pop_front();
      } else {
          Node *temp = first;
          for (unsigned int i = 0; i<index-1; i++) {
              temp = temp->getNext();
          }
          Node *eliminar = temp->getNext();
          temp -> setNext(eliminar->getNext());
          delete eliminar;
          sz--;
          if (temp->getNext() == nullptr) {
              last = temp;
          }
      }
    }
    void print() const {
      Node *temp = first;
      while (temp != nullptr) {
        cout << temp->getvalue() << " ";
        temp = temp->getNext();
      }
      cout << endl; 
    }
    void reverse() {
      if (empty() || sz==1) {
        return ; // SOLO HAY UN ELEMENTO O NINGUNO, NO HAY NADA QUE HACER
      } else {
          Node *previo = nullptr;
          Node *actual = first;
          Node *siguiente = nullptr;
          first = last;
          while (actual != nullptr) {
              
          }
      }
    }
    List(const List &other) {
      /** your implementation here */
    }
    void push_back(const List &other) {
      /** your implementation here */
    }
    void push_front_l(const List &other) {
      /** your implementation here */
    }
};
int main () {
  List<int> lista;
  lista.push_back(10);
  lista.push_back(20);
  lista.push_back(30);
  lista.push_front(5);
  lista.print(); // Salida esperada: 5 10 20 30
  cout << "First element: " << lista.front() << endl; // Salida esperada: 5
  cout << "Last element: " << lista.back() << endl;   // Salida esperada: 30
  cout << "Size: " << lista.size() << endl;           // Salida esperada: 4
  lista.pop_front();
  lista.print(); // Salida esperada: 10 20 30
  lista.pop_back();
  lista.print(); // Salida esperada: 10 20
  lista.insert(1,15);
  lista.print(); // Salida esperada: 10 15 20
  lista.erase(0);
  lista.print(); // Salida esperada: 15 20
  // ULTIMOS TESTS
  return 0;
}