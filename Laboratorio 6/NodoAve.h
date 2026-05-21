#ifndef EIF201_NODO_AVE_H
#define EIF201_NODO_AVE_H

#include <string>

namespace EIF201 {

    struct NodoAve {
        std::string anillo;     // codigo de anillo (ej. "TS-0427")
        std::string especie;    // nombre comun (ej. "Garza Tigre")
        double peso;            // en gramos
        char sexo;              // 'M', 'H' o 'X' (indeterminado)
        std::string fecha;      // formato YYYY-MM-DD
        NodoAve* siguiente;

        NodoAve(const std::string& anillo_,
            const std::string& especie_,
            double peso_,
            char sexo_,
            const std::string& fecha_)
            : anillo(anillo_), especie(especie_), peso(peso_),
            sexo(sexo_), fecha(fecha_), siguiente(nullptr) {
        }
    };

} // namespace EIF201

#endif
