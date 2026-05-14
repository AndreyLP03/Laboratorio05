#include "NodoDoble.h"

using namespace std;

namespace EIF201 {

    NodoDoble::NodoDoble()
        : cabeza(nullptr), cola(nullptr), cantidad(0) {
    }

    NodoDoble::~NodoDoble() {
        NodoHistorial* actual = cabeza;
        while (actual != nullptr) {
            NodoHistorial* temp = actual->siguiente; // guardar antes de eliminar
            delete actual;
            actual = temp;
        }
        cabeza = nullptr;
        cola = nullptr;
        cout << "[HistorialDoble destruido]" << endl;
    }

    void NodoDoble::insertarAlInicio(const string& cancion) {
        NodoHistorial* nuevo = new NodoHistorial(cancion);
        if (cabeza == nullptr) {
            cabeza = nuevo; // lista vacía: nuevo es cabeza y cola
            cola = nuevo;
        }
        else {
            nuevo->siguiente = cabeza; 
            cabeza->anterior = nuevo;  
            cabeza = nuevo;  
            
        }
        cantidad++;
    }

    void NodoDoble::insertarAlFinal(const string& cancion) {
        NodoHistorial* nuevo = new NodoHistorial(cancion);
        if (cola == nullptr) {
            cabeza = nuevo;
            cola = nuevo;
        }
        else {
            nuevo->anterior = cola;  
            cola->siguiente = nuevo; 
            cola = nuevo; 
            // nuevo->siguiente queda nullptr: es el final de la lista
        }
        cantidad++;
    }



    void NodoDoble::insertarEnPosicion(const string& cancion, int pos) {
        if (pos <= 0) { insertarAlInicio(cancion); return; }
        if (pos >= cantidad) { insertarAlFinal(cancion); return; }

        NodoHistorial* nuevo = new NodoHistorial(cancion);
        NodoHistorial* actual = cabeza;
        for (int i = 0; i < pos; i++) {
            actual = actual->siguiente;
        }
        // 'actual' es el nodo que quedará despues del nuevo

        NodoHistorial* previo = actual->anterior;
        nuevo->siguiente = actual;    // nuevo -> actual
        nuevo->anterior = previo;     // previo <- nuevo
        previo->siguiente = nuevo;    // previo -> nuevo (reemplaza a actual)
        actual->anterior = nuevo;     // nuevo <- actual
        cantidad++;
    }


    bool NodoDoble::insertarAntesDe(const string& referencia, const string& nueva) {
        NodoHistorial* actual = cabeza;
        while (actual != nullptr) {
            if (actual->cancion == referencia) {
                if (actual == cabeza) {
                    insertarAlInicio(nueva);
                }
                else {
                    NodoHistorial* nuevo = new NodoHistorial(nueva);
                    NodoHistorial* previo = actual->anterior;

                    nuevo->siguiente = actual;
                    nuevo->anterior = previo;
                    previo->siguiente = nuevo;
                    actual->anterior = nuevo;

                    cantidad++;
                }
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    bool NodoDoble::insertarDespuesDe(const string& referencia, const string& nueva) {
        NodoHistorial* actual = cabeza;
        while (actual != nullptr) {
            if (actual->cancion == referencia) {
                if (actual == cola) {
                    insertarAlFinal(nueva);
                }
                else {
                    NodoHistorial* nuevo = new NodoHistorial(nueva);
                    NodoHistorial* sig = actual->siguiente;
                    nuevo->anterior = actual;
                    nuevo->siguiente = sig;
                    actual->siguiente = nuevo;
                    sig->anterior = nuevo;
                    cantidad++;
                }
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }


    bool NodoDoble::existeCancion(const string& cancion) const {
        NodoHistorial* actual = cabeza;
        while (actual != nullptr) {
            if (actual->cancion == cancion)
            {
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }


    int NodoDoble::obtenerPosicion(const string& cancion) const {
        NodoHistorial* actual = cabeza;
        int pos = 0;
        while (actual != nullptr) {
            if (actual->cancion == cancion) {
                return pos;
            }
            actual = actual->siguiente;
            pos++;
        }
        return -1;
    }



    string NodoDoble::obtenerEnPosicion(int pos) const {
        if (pos < 0 || pos >= cantidad) {
            return "";
        }
        NodoHistorial* actual = cabeza;
        for (int i = 0; i < pos; i++) {
            actual = actual->siguiente;
        }
        return actual->cancion;
    }


    int NodoDoble::obtenerPosicionDesdeElFinal(const string& cancion) const {
        NodoHistorial* actual = cola;
        int pos = 0;
        while (actual != nullptr) {
            if (actual->cancion == cancion) {
                return pos;
            }
            actual = actual->anterior;
            pos++;
        }
        return -1;
    }



    bool NodoDoble::eliminarPrimera(const string& cancion) {
        NodoHistorial* actual = cabeza;
        while (actual != nullptr) {
            if (actual->cancion == cancion) {
                // Reconectar vecino izquierdo
                if (actual->anterior != nullptr) {
                    actual->anterior->siguiente = actual->siguiente;
                }
                else {
                    cabeza = actual->siguiente; // era la cabeza
                }

                // Reconectar vecino derecho
                if (actual->siguiente != nullptr) {
                    actual->siguiente->anterior = actual->anterior;
                }
                else {
                    cola = actual->anterior;     // era la cola
                }

                delete actual;
                actual = nullptr; // evitar puntero colgante
                cantidad--;
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }


    bool NodoDoble::eliminarUltima(const string& cancion) {
        NodoHistorial* actual = cola;
        while (actual != nullptr) {
            if (actual->cancion == cancion) {
                if (actual->anterior != nullptr) {
                    actual->anterior->siguiente = actual->siguiente;
                }
                else {
                    cabeza = actual->siguiente;
                }

                if (actual->siguiente != nullptr) {
                    actual->siguiente->anterior = actual->anterior;
                }
                else {
                    cola = actual->anterior;
                }

                delete actual;
                actual = nullptr;
                cantidad--;
                return true;
            }
            actual = actual->anterior; // recorrido inverso
        }
        return false;
    }


    bool NodoDoble::eliminarEnPosicion(int pos) {
        if (pos < 0 || pos >= cantidad) { return false; }
        if (pos == 0) { return eliminarCabeza(); }
        if (pos == cantidad - 1) { return eliminarCola(); }

        NodoHistorial* actual = cabeza;
        for (int i = 0; i < pos; i++) { actual = actual->siguiente; }

        actual->anterior->siguiente = actual->siguiente;
        actual->siguiente->anterior = actual->anterior;
        delete actual;
        actual = nullptr;
        cantidad--;
        return true;
    }

    bool NodoDoble::eliminarCabeza() {
        if (cabeza == nullptr) { return false; }
        return eliminarPrimera(cabeza->cancion);
    }

    bool NodoDoble::eliminarCola() {
        if (cola == nullptr) { return false; }
        return eliminarUltima(cola->cancion);
    }


    void NodoDoble::imprimirCronologico() const {
        NodoHistorial* actual = cabeza;
        cout << "Cronologico: ";
        while (actual != nullptr) {
            cout << actual->cancion;
            if (actual->siguiente != nullptr) { cout << " <-> "; }
            actual = actual->siguiente;
        }
        cout << endl;
    }

    void NodoDoble::imprimirInverso() const {
        NodoHistorial* actual = cola;
        cout << "Inverso:     ";
        while (actual != nullptr) {
            cout << actual->cancion;
            if (actual->anterior != nullptr) { cout << " <-> "; }
            actual = actual->anterior;
        }
        cout << endl;
    }

    int NodoDoble::getCantidad() const { return cantidad; }
    bool NodoDoble::estaVacia()   const { return cabeza == nullptr; }

}
