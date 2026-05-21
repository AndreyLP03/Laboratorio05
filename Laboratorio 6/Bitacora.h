#ifndef EIF201_BITACORA_H
#define EIF201_BITACORA_H

#include "NodoAve.h"
#include <string>

namespace EIF201 {

    class Bitacora {
    private:
        std::string ruta_;
        int validas_;
        int descartadas_;

    public:
        Bitacora(const std::string& ruta);

        // Escribe un ave al final del archivo (modo append).
        // Retorna true si la operacion exitosa, false en caso contrario.
        bool registrarAve(const std::string& anillo,
            const std::string& especie,
            double peso,
            char sexo,
            const std::string& fecha);

        // Carga todas las lineas, asumiendo formato correcto.
        // Construye una lista enlazada y la asigna a cabeza (por referencia).
        // Retorna la cantidad de aves cargadas.
        int cargarTodas(NodoAve*& cabeza);

        // Carga las lineas validas, descarta las dañadas.
        // Tras la llamada, getValidas() y getDescartadas() reportan los contadores.
        int cargarValidas(NodoAve*& cabeza);

        int getValidas() const;
        int getDescartadas() const;

        // Funcion utilitaria estatica: libera una lista enlazada de NodoAve.
        static void liberarLista(NodoAve*& cabeza);
    };

} // namespace EIF201

#endif
