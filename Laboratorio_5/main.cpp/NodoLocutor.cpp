#include "NodoLocutor.h"


namespace EIF201 {

    NodoLocutor::NodoLocutor(const string& n)
        : nombre(n), siguiente(nullptr), turnosAsignados(0) {
        cout << "[NodoLocutor creado: " << n << "]" << endl;
    }

    // Implementación del destructor
    NodoLocutor::~NodoLocutor() {
        cout << "[NodoLocutor destruido: " << nombre << "]" << endl;
    }
}