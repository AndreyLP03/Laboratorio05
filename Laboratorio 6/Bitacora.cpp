#include "Bitacora.h"
#include <fstream>
#include <sstream>

using namespace std;

namespace EIF201 {

    Bitacora::Bitacora(const string& ruta)
    {
        ruta_ = ruta;
        validas_ = 0;
        descartadas_ = 0;
    }

    bool Bitacora::registrarAve(const string& anillo,
        const string& especie,
        double peso,
        char sexo,
        const string& fecha)
    {
        ofstream archivo(ruta_, ios::app);

        if (!archivo.is_open()) {
            return false;
        }

        archivo << anillo << ";"
            << especie << ";"
            << peso << ";"
            << sexo << ";"
            << fecha << endl;

        archivo.close();

        return true;
    }

    int Bitacora::cargarTodas(NodoAve*& cabeza)
    {
        ifstream archivo(ruta_);

        cabeza = nullptr;

        if (!archivo.is_open()) {
            return 0;
        }

        string linea;

        int cantidad = 0;

        while (getline(archivo, linea)) {

            string anillo;
            string especie;
            string pesoTexto;
            string sexoTexto;
            string fecha;

            stringstream ss(linea);

            getline(ss, anillo, ';');
            getline(ss, especie, ';');
            getline(ss, pesoTexto, ';');
            getline(ss, sexoTexto, ';');
            getline(ss, fecha, ';');

            double peso = stod(pesoTexto);

            char sexo = sexoTexto[0];

            NodoAve* nuevo = new NodoAve(anillo,
                especie,
                peso,
                sexo,
                fecha);

            if (cabeza == nullptr) {

                cabeza = nuevo;

            }
            else {

                NodoAve* aux = cabeza;

                while (aux->siguiente != nullptr) {
                    aux = aux->siguiente;
                }

                aux->siguiente = nuevo;
            }

            cantidad++;
        }

        archivo.close();

        return cantidad;
    }

    int Bitacora::cargarValidas(NodoAve*& cabeza)
    {
        ifstream archivo(ruta_);

        cabeza = nullptr;

        validas_ = 0;
        descartadas_ = 0;

        if (!archivo.is_open()) {
            return 0;
        }

        string linea;

        while (getline(archivo, linea)) {

            if (linea.empty()) {
                descartadas_++;
                continue;
            }

            string anillo;
            string especie;
            string pesoTexto;
            string sexoTexto;
            string fecha;

            stringstream ss(linea);

            bool correcto = true;

            if (!getline(ss, anillo, ';')) {
                correcto = false;
            }

            if (!getline(ss, especie, ';')) {
                correcto = false;
            }

            if (!getline(ss, pesoTexto, ';')) {
                correcto = false;
            }

            if (!getline(ss, sexoTexto, ';')) {
                correcto = false;
            }

            if (!getline(ss, fecha, ';')) {
                correcto = false;
            }

            double peso = 0;

            try {

                peso = stod(pesoTexto);

                if (peso <= 0) {
                    correcto = false;
                }

            }
            catch (...) {

                correcto = false;
            }

            char sexo = 'X';

            if (!sexoTexto.empty()) {

                sexo = sexoTexto[0];

                if (sexo != 'M' &&
                    sexo != 'H' &&
                    sexo != 'X') {

                    correcto = false;
                }

            }
            else {

                correcto = false;
            }

            if (!correcto) {
                descartadas_++;
                continue;
            }

            NodoAve* nuevo = new NodoAve(anillo,
                especie,
                peso,
                sexo,
                fecha);

            if (cabeza == nullptr) {

                cabeza = nuevo;

            }
            else {

                NodoAve* aux = cabeza;

                while (aux->siguiente != nullptr) {
                    aux = aux->siguiente;
                }

                aux->siguiente = nuevo;
            }

            validas_++;
        }

        archivo.close();

        return validas_;
    }

    int Bitacora::getValidas() const
    {
        return validas_;
    }

    int Bitacora::getDescartadas() const
    {
        return descartadas_;
    }

    void Bitacora::liberarLista(NodoAve*& cabeza)
    {
        NodoAve* aux = cabeza;

        while (aux != nullptr) {

            NodoAve* temp = aux;

            aux = aux->siguiente;

            delete temp;
        }

        cabeza = nullptr;
    }

} // namespace EIF201
