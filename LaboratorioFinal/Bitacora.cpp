
#include "Bitacora.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace EIF201 {

    
    Bitacora::Bitacora(const std::string& ruta)
        : ruta_(ruta), validas_(0), descartadas_(0) { 
    }

    
    int Bitacora::getValidas() const {
        return validas_;
    }

    int Bitacora::getDescartadas() const {
        return descartadas_;
    }

    
    bool Bitacora::registrarAve(const std::string& anillo,
        const std::string& especie,
        double peso,
        char sexo,
        const std::string& fecha) {
        std::ofstream archivo(ruta_, std::ios::app); 

        if (!archivo.is_open()) { 
            return false;
        }

  
        archivo << anillo << ";"
            << especie << ";"
            << peso << ";"
            << sexo << ";"
            << fecha << "\n";

        archivo.close(); 
        return true;
    }

    
    int Bitacora::cargarTodas(NodoAve*& cabeza) {
        cabeza = nullptr;
        std::ifstream archivo(ruta_);

        if (!archivo.is_open()) {
            return 0; 
        }

        std::string linea;
        int contador = 0;
        NodoAve* ultimo = nullptr;

        while (std::getline(archivo, linea)) { // [cite: 483]
            if (linea.empty()) continue;

            std::stringstream ss(linea); // [cite: 484]
            std::string anillo, especie, pesoStr, fecha;
            char sexo;

            std::getline(ss, anillo, ';'); 
            std::getline(ss, especie, ';'); 
            std::getline(ss, pesoStr, ';'); 
            ss >> sexo;
            ss.ignore();
            std::getline(ss, fecha, ';');

            double peso = std::stod(pesoStr);

            NodoAve* nuevo = new NodoAve(anillo, especie, peso, sexo, fecha); 

            if (cabeza == nullptr) {
                cabeza = nuevo;
            }
            else {
                ultimo->siguiente = nuevo; 
            }
            ultimo = nuevo;
            contador++;
        }

        archivo.close();
        return contador; 
    }

    
    int Bitacora::cargarValidas(NodoAve*& cabeza) {
        cabeza = nullptr;
        validas_ = 0;
        descartadas_ = 0;

        std::ifstream archivo(ruta_);
        if (!archivo.is_open()) {
            return 0;
        }

        std::string linea;
        NodoAve* ultimo = nullptr;

        while (std::getline(archivo, linea)) {
            if (linea.empty()) {
                descartadas_++; 
                continue;
            }

            std::stringstream ss(linea);
            std::string anillo, especie, pesoStr, sexoStr, fecha;

            if (!std::getline(ss, anillo, ';') ||
                !std::getline(ss, especie, ';') ||
                !std::getline(ss, pesoStr, ';') ||
                !std::getline(ss, sexoStr, ';') ||
                !std::getline(ss, fecha)) {

                descartadas_++; 
                continue;
            }

            
            if (sexoStr.length() != 1) {
                descartadas_++;
                continue;
            }

            char sexo = sexoStr[0];
            if (sexo != 'M' && sexo != 'H' && sexo != 'X') { 
                descartadas_++;
                continue;
            }

            double peso = 0.0;
            try {
                peso = std::stod(pesoStr);
                if (peso <= 0) { 
                    descartadas_++;
                    continue;
                }
            }
            catch (...) {
                descartadas_++;
                continue;
            }

            if (anillo.empty() || especie.empty() || fecha.empty()) {
                descartadas_++;
                continue;
            }

            NodoAve* nuevo = new NodoAve(anillo, especie, peso, sexo, fecha); 
            if (cabeza == nullptr) {
                cabeza = nuevo;
            }
            else {
                ultimo->siguiente = nuevo;
            }
            ultimo = nuevo;
            validas_++;
        }

        archivo.close();
        return validas_;
    }

    
    void Bitacora::liberarLista(NodoAve*& cabeza) {
        NodoAve* actual = cabeza;
        while (actual != nullptr) {
            NodoAve* siguienteNodo = actual->siguiente;
            delete actual; 
            actual = siguienteNodo;
        }
        cabeza = nullptr;
    }

} 
