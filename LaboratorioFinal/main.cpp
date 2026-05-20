#include <iostream>
#include "Bitacora.h"
#include "AnalisisAves.h"

int main() {
   
    EIF201::NodoAve* listaAves = nullptr;

   
    EIF201::Bitacora bitacora("archivo/anillamientos.txt.txt");

    std::cout << "----------------------------------------------------\n";
    std::cout << "    HUMEDAL TERRABA-SIERPE     \n";
    std::cout << "-----------------------------------------------------\n\n";

    std::cout << ">>>  Carga Defensiva de Archivos...\n";

   
    int cargadas = bitacora.cargarValidas(listaAves);

    std::cout << " -> Procesamiento completado.\n";
    std::cout << " -> Aves cargadas con exito : " << cargadas << "\n";
    std::cout << " -> Registros validos : " << bitacora.getValidas() << "\n";
    std::cout << " -> Registros descartados: " << bitacora.getDescartadas() << "\n\n";

    std::cout << "---------------------------------------------\n";
    std::cout << ">> [MODULO B] Analisis Metrico Recursivo...\n";
    std::cout << "---------------------------------------------\n\n";

   
    EIF201::AnalisisAves analizador;

    std::cout << "--------IMPRESION CRONOLOGICA ---\n";
    analizador.imprimirCronologico(listaAves);
    std::cout << "----------------------------------------------------\n\n";

    std::cout << "-----IMPRESION INVERSA -------------\n";
    analizador.imprimirInverso(listaAves);
    std::cout << "----------------------------------------------------\n\n";

    
    std::cout << "------- METRICAS GENERALES CALCULADAS ---\n";
    std::cout << " Total de aves contadas recursivamente: " << analizador.contar(listaAves) << "\n";
    std::cout << " Suma total de los pesos acumulados : " << analizador.sumaPesos(listaAves) << " g\n\n";

    
    std::string especieBuscar = "Garza Tigre";
    std::cout << "--- --- BUSQUEDAS ESPECIFICAS ---\n";
    std::cout << " ¿Existe la especie '" << especieBuscar << " ?  "
        << (analizador.existeEspecie(listaAves, especieBuscar) ? "SI" : "NO") << "\n";
    std::cout << " Cantidad de ejemplares de '" << especieBuscar << "': "
        << analizador.contarEspecie(listaAves, especieBuscar) << "\n\n";

    
    std::cout << "------ EVALUACION DE MAXIMOS ---\n";
    EIF201::NodoAve* masPesada = analizador.aveMasPesada(listaAves);
    if (masPesada != nullptr) {
        std::cout << " Ave mas pesada registrada: Anillo [" << masPesada->anillo << "]\n"
            << " Especie: " << masPesada->especie << "\n"
            << " Peso   : " << masPesada->peso << " g\n\n";
    }
    else {
        std::cout << " No hay datos suficientes para calcular el ave mas pesada.\n\n";
    }

    //  LIBERACION DE MEMORIA
    std::cout << ">> Liberando memoria de la lista...\n";
    EIF201::Bitacora::liberarLista(listaAves);

    std::cout << ">>> Memoria en limpio. Ejecucion finalizada con exito.\n";

    return 0;
}