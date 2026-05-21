#include "AnalisisAves.h"
#include <iostream>

using namespace std;

namespace EIF201 {

    int AnalisisAves::contar(NodoAve* cab) const
    {
        if (cab == nullptr) {
            return 0;
        }

        return 1 + contar(cab->siguiente);
    }

    double AnalisisAves::sumaPesos(NodoAve* cab) const
    {
        if (cab == nullptr) {
            return 0.0;
        }

        return cab->peso + sumaPesos(cab->siguiente);
    }

    int AnalisisAves::contarEspecie(NodoAve* cab,
        const string& especie) const
    {
        if (cab == nullptr) {
            return 0;
        }

        if (cab->especie == especie) {

            return 1 + contarEspecie(cab->siguiente,
                especie);
        }

        return contarEspecie(cab->siguiente,
            especie);
    }

    bool AnalisisAves::existeEspecie(NodoAve* cab,
        const string& especie) const
    {
        if (cab == nullptr) {
            return false;
        }

        if (cab->especie == especie) {
            return true;
        }

        return existeEspecie(cab->siguiente,
            especie);
    }

    NodoAve* AnalisisAves::aveMasPesada(NodoAve* cab) const
    {
        if (cab == nullptr) {
            return nullptr;
        }

        return maxAux(cab, cab);
    }

    NodoAve* AnalisisAves::maxAux(NodoAve* cab,
        NodoAve* mejor) const
    {
        if (cab == nullptr) {
            return mejor;
        }

        if (cab->peso > mejor->peso) {
            mejor = cab;
        }

        return maxAux(cab->siguiente,
            mejor);
    }

    void AnalisisAves::imprimirCronologico(NodoAve* cab) const
    {
        if (cab == nullptr) {
            return;
        }

        cout << "Anillo: " << cab->anillo << endl;
        cout << "Especie: " << cab->especie << endl;
        cout << "Peso: " << cab->peso << endl;
        cout << "Sexo: " << cab->sexo << endl;
        cout << "Fecha: " << cab->fecha << endl;
        cout << "-------------------" << endl;

        imprimirCronologico(cab->siguiente);
    }

    void AnalisisAves::imprimirInverso(NodoAve* cab) const
    {
        imprimirInversoAux(cab);
    }

    void AnalisisAves::imprimirInversoAux(NodoAve* cab) const
    {
        if (cab == nullptr) {
            return;
        }

        imprimirInversoAux(cab->siguiente);

        cout << "Anillo: " << cab->anillo << endl;
        cout << "Especie: " << cab->especie << endl;
        cout << "Peso: " << cab->peso << endl;
        cout << "Sexo: " << cab->sexo << endl;
        cout << "Fecha: " << cab->fecha << endl;
        cout << "-------------------" << endl;
    }

} // namespace EIF201