#include "NodoDoble.h"
#include "NodoRotacionCircular.h"
using namespace EIF201;
using namespace std;
#include<string>
#include<iostream>

int main() {


    cout << "\nMODULO A: HistorialDobl" << endl;
    {
        NodoDoble h;

        // Inserción
        h.insertarAlFinal("rock1");
        h.insertarAlFinal("pop7");
        h.insertarAlFinal("jazz3");
        h.insertarAlInicio("clas5");
        h.insertarEnPosicion("folk2", 2);
        h.insertarAntesDe("jazz3", "bosa1");
        h.insertarDespuesDe("pop7", "soul4");
        h.imprimirCronologico();

        h.imprimirInverso();

        cout << "Posicion jazz3:        " << h.obtenerPosicion("jazz3") << endl; 
        cout << "Cancion en pos 0:      " << h.obtenerEnPosicion(0) << endl; 
        cout << "jazz3 existe:          " << (h.existeCancion("jazz3") ? "si" : "no") << endl; // si
        cout << "Pos desde final pop7:  " << h.obtenerPosicionDesdeElFinal("pop7") << endl; // 3

        h.eliminarPrimera("bosa1");
        h.eliminarCabeza();
        h.eliminarCola();
        h.eliminarEnPosicion(1);
        h.eliminarUltima("pop7");
        h.imprimirCronologico();
        // Esperado: rock1 <-> soul4
        cout << "Cantidad: " << h.getCantidad() << endl; // 2
    } // destructor libera rock1 y soul4

    // MÓDULO B – RotacionCircular
    cout << "\nMODULO B: RotacionCircular" << endl;
    {
        RotacionCircular r;

        // Inserción
        r.insertarAlFinal("Maria");
        r.insertarAlFinal("Carlos");
        r.insertarAlFinal("Adriana");
        r.insertarAlInicio("Diego");
        r.insertarDespuesDe("Carlos", "Elena");
        r.imprimirRotacion();

        cout << "Carlos existe:         " << (r.existeLocutor("Carlos") ? "si" : "no") << endl;



        cout << "Posicion Carlos:       " << r.obtenerPosicion("Carlos") << endl;
        cout << "Turno actual:          " << r.turnoActual() << endl;


        r.simularTurnos(7);
        r.imprimirEstadisticas(); // Muestra los turnos acumulados por cada uno
        cout << "Locutor con mas turnos: " << r.locutorMasActivo() << endl;
        cout << "Cantidad: " << r.getCantidad() << endl;
       
        
        
        cout << "---------Eliminaciones-----"<<endl;
        r.eliminarLocutor("Carlos");
        r.eliminarTurnoActual();
        r.imprimirRotacion();
        r.eliminarLocutor("Adriana");

        //verificacion
        while (!r.estaVacia()) r.eliminarTurnoActual();
        cout << "Vacia: " << (r.estaVacia() ? "si" : "no") << endl;
        cout << "Siguiente vacia: '" << r.siguiente() << "'" << endl;
    }



    return 0;
}