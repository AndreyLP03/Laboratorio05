#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Bitacora.h"
#include "AnalisisAves.h"

using namespace std;
using namespace EIF201;

// Busca un ave por anillo y modifica sus datos de forma segura
void modificarAveEnMemoria(NodoAve* cabeza) {
    if (cabeza == nullptr) {
        cout << "\n[ALERTA] La lista esta vacia en memoria. Primero debes cargar los datos (Opcion 2)." << endl;
        return;
    }

    string anilloBuscar;
    cout << "\n--- MODIFICAR REGISTRO DE AVE ---" << endl;
    cout << "Ingrese el codigo de anillo del ave a modificar: ";
    getline(cin, anilloBuscar);

    NodoAve* aux = cabeza;
    bool encontrado = false;

    while (aux != nullptr) {
        if (aux->anillo == anilloBuscar) {
            encontrado = true;
            cout << "\n¡Ave encontrada!" << endl;
            cout << "Datos actuales: " << aux->especie << " | Peso: " << aux->peso << "g | Sexo: " << aux->sexo << " | Fecha: " << aux->fecha << endl;
            cout << "---------------------------------------------" << endl;

            cout << "Ingrese nuevo nombre de especie: ";
            getline(cin, aux->especie);

            string pesoTexto;
            cout << "Ingrese nuevo peso (en gramos): ";
            getline(cin, pesoTexto);
            try {
                aux->peso = stod(pesoTexto);
            }
            catch (...) {
                aux->peso = 0.0;
            }

            string sexoTexto;
            cout << "Ingrese nuevo sexo ('M', 'H', 'X'): ";
            getline(cin, sexoTexto);
            if (!sexoTexto.empty()) {
                aux->sexo = toupper(sexoTexto[0]);
            }
            else {
                aux->sexo = 'X';
            }

            cout << "Ingrese nueva fecha (YYYY-MM-DD): ";
            getline(cin, aux->fecha);

            cout << "\n[EXITO] Datos modificados en memoria temporal." << endl;
            cout << "[NOTA] Use la Opcion 4 para guardar estos cambios permanentemente en el archivo." << endl;
            break;
        }
        aux = aux->siguiente;
    }

    if (!encontrado) {
        cout << "\n[ERROR] No se encontro ninguna ave con el anillo: " << anilloBuscar << endl;
    }
}

// Reescribe el archivo txt completo con el estado actual de la lista
bool guardarListaEnArchivo(const string& ruta, NodoAve* cabeza) {
    ofstream archivo(ruta, ios::trunc);
    if (!archivo.is_open()) return false;

    NodoAve* aux = cabeza;
    while (aux != nullptr) {
        archivo << aux->anillo << ";"
            << aux->especie << ";"
            << aux->peso << ";"
            << aux->sexo << ";"
            << aux->fecha << "\n";
        aux = aux->siguiente;
    }

    archivo.close();
    return true;
}

int main() {
    string rutaArchivo = "datos.txt";
    Bitacora miBitacora(rutaArchivo);
    AnalisisAves miAnalizador;
    NodoAve* cabezaLista = nullptr;

    string opcionTexto = "";
    int opcion = 0;

    do {
        cout << "\n--------------------------------------------" << endl;
        cout << "     SISTEMA DE ANALISIS DE AVES         " << endl;
        cout << "-------------------------------------------" << endl;
        cout << " 1. Registrar una nueva ave " << endl;
        cout << " 2. CARGAR y procesar Bitacora " << endl;
        cout << " 3. MODIFICAR datos de un ave existente" << endl;
        cout << " 4. GUARDAR cambios modificados " << endl;
        cout << " 5. Mostrar aves en Orden Cronologico" << endl;
        cout << " 6. Mostrar aves en Orden Inverso" << endl;
        cout << " 7. Ver Metricas Generales (Contar y Pesos)" << endl;
        cout << " 8. Ver el Ave mas Pesada" << endl;
        cout << " 9. Salir" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Seleccione una opcion: ";

        getline(cin, opcionTexto);
        try {
            opcion = stoi(opcionTexto);
        }
        catch (...) {
            opcion = 0; 
        }

        switch (opcion) {
        case 1: {
            string anillo, especie, fecha, pesoTexto, sexoTexto;
            double peso = 0.0;
            char sexo = 'X';

            cout << "\n--- REGISTRAR NUEVA AVE ---" << endl;
            cout << "Ingrese codigo de anillo (ej: TS-0427): ";
            getline(cin, anillo);

            cout << "Ingrese nombre de la especie: ";
            getline(cin, especie);

            cout << "Ingrese peso (en gramos): ";
            getline(cin, pesoTexto);
            try { peso = stod(pesoTexto); }
            catch (...) { peso = 0.0; }

            cout << "Ingrese sexo ('M', 'H', 'X'): ";
            getline(cin, sexoTexto);
            if (!sexoTexto.empty()) sexo = toupper(sexoTexto[0]);

            cout << "Ingrese fecha (YYYY-MM-DD): ";
            getline(cin, fecha);

            if (miBitacora.registrarAve(anillo, especie, peso, sexo, fecha)) {
                cout << "\n[EXITO] Ave registrada en el archivo." << endl;
            }
            else {
                cout << "\n[ERROR] No se pudo escribir en el archivo." << endl;
            }
            break;
        }
        case 2:
            Bitacora::liberarLista(cabezaLista);
            cout << "\nCargando registros desde " << rutaArchivo << "..." << endl;
            miBitacora.cargarValidas(cabezaLista);
            cout << "\n--- REPORTE DE CARGA ---" << endl;
            cout << "Registros validos cargados a memoria RAM: " << miBitacora.getValidas() << endl;
            cout << "Registros descartados/danados: " << miBitacora.getDescartadas() << endl;
            break;

        case 3:
            modificarAveEnMemoria(cabezaLista);
            break;

        case 4:
            if (cabezaLista == nullptr) {
                cout << "\n[ALERTA] La lista esta vacia. No hay nada que guardar." << endl;
            }
            else if (guardarListaEnArchivo(rutaArchivo, cabezaLista)) {
                cout << "\n[EXITO] Archivo '" << rutaArchivo << "' actualizado permanentemente." << endl;
            }
            else {
                cout << "\n[ERROR] No se pudo actualizar el archivo." << endl;
            }
            break;

        case 5:
            if (cabezaLista == nullptr) {
                cout << "\n[ALERTA] No hay datos cargados para mostrar. Use primero la Opcion 2." << endl;
            }
            else {
                cout << "\n>>> LISTA DE AVES (ORDEN CRONOLOGICO):" << endl;
                miAnalizador.imprimirCronologico(cabezaLista);
            }
            break;

        case 6:
            if (cabezaLista == nullptr) {
                cout << "\n[ALERTA] No hay datos cargados para mostrar. Use primero la Opcion 2." << endl;
            }
            else {
                cout << "\n>>> LISTA DE AVES (ORDEN INVERSO):" << endl;
                miAnalizador.imprimirInverso(cabezaLista);
            }
            break;

        case 7:
            if (cabezaLista == nullptr) {
                cout << "\n[ALERTA] No hay datos en memoria. Use primero la Opcion 2." << endl;
            }
            else {
                int total = miAnalizador.contar(cabezaLista);
                double pesoTotal = miAnalizador.sumaPesos(cabezaLista);
                cout << "\n>>> METRICAS GENERALES:" << endl;
                cout << "Total de aves registradas: " << total << endl;
                cout << "Suma total de pesos: " << fixed << setprecision(2) << pesoTotal << " gramos" << endl;
                if (total > 0) cout << "Peso promedio: " << (pesoTotal / total) << " gramos" << endl;
            }
            break;

        case 8:
            if (cabezaLista == nullptr) {
                cout << "\n[ALERTA] No hay datos en memoria. Use primero la Opcion 2." << endl;
            }
            else {
                NodoAve* masPesada = miAnalizador.aveMasPesada(cabezaLista);
                if (masPesada != nullptr) {
                    cout << "\n>>> RECORD DE PESO RECURSIVO:" << endl;
                    cout << "Especie: " << masPesada->especie << " | Anillo: " << masPesada->anillo << " | Peso: " << masPesada->peso << "g" << endl;
                }
            }
            break;

        case 9:
            cout << "\nLiberando memoria y saliendo..." << endl;
            Bitacora::liberarLista(cabezaLista);
            cout << "¡Proceso terminado!" << endl;
            break;

        default:
            cout << "\n[OPCION INVALIDA] Intente de nuevo." << endl;
            break;
        }

    } while (opcion != 9);

    return 0;
}