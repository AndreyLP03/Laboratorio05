#pragma once

#include <iostream>
#include<string>

using namespace std;

namespace EIF201 {

    struct NodoLocutor {
        string         nombre;
        NodoLocutor* siguiente;  
        int turnosAsignados;
        NodoLocutor(const string& n);

        ~NodoLocutor();
        
    };

} 


