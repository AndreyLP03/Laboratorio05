#pragma once

#include "NodoLocutor.h"

namespace EIF201 {

    class RotacionCircular {
    private:
        NodoLocutor* cola;     
        int          cantidad;

        
        NodoLocutor* getCabeza() const;

    public:
        RotacionCircular();
        ~RotacionCircular();

        void insertarAlFinal(const string& nombre);



      
        void insertarAlInicio(const string& nombre);

        
        bool insertarDespuesDe(const string& referencia, const string& nuevo_nombre);

        
        bool existeLocutor(const string& nombre) const;

      
        int obtenerPosicion(const string& nombre) const;

        
        string turnoActual() const;

        
        bool eliminarLocutor(const string& nombre);

      
        bool eliminarTurnoActual();

       
        string siguiente();

  
        void simularTurnos(int n);

        
        void imprimirRotacion() const;

        int getCantidad() const;
        bool estaVacia() const;


        void imprimirEstadisticas() const;
        string locutorMasActivo() const;

    };

} // namespace EIF20
