#pragma once
#include "NodoHistorial.h"


namespace EIF201{



class NodoDoble
{

private:
    NodoHistorial* cabeza;    // primer nodo de la lista
    NodoHistorial* cola;      // último nodo de la lista
    int            cantidad;  // cantidad de nodos actuales

public:
    
    NodoDoble();
    ~NodoDoble();

  
    void insertarAlInicio(const string& cancion);

    void insertarAlFinal(const string& cancion);

    void insertarEnPosicion(const string& cancion, int pos);

    bool insertarAntesDe(const string& referencia, const string& nueva);

    bool insertarDespuesDe(const string& referencia, const string& nueva);

    
    bool existeCancion(const string& cancion) const;

 
    int obtenerPosicion(const string& cancion) const;

    
    string obtenerEnPosicion(int pos) const;

    
    int obtenerPosicionDesdeElFinal(const string& cancion) const;

    
    bool eliminarPrimera(const string& cancion);

    bool eliminarUltima(const string& cancion);

    
    bool eliminarEnPosicion(int pos);

   
    bool eliminarCabeza();

    
    bool eliminarCola();

    void imprimirCronologico() const; 
    void imprimirInverso() const;     

    // Consultas
    int getCantidad() const;
    bool estaVacia() const;




};

}