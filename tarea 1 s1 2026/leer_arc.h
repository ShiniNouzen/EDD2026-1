#ifndef LEER_ARC_H
#define LEER_ARC_H
#include <iostream>
#include <fstream>
#include <string>
#include "Arr.h"
using namespace std;
class arch{
    public:
    Arr arreglo;
    void lectura(string nom_arch){
        ifstream file(nom_arch);
        if(!file.is_open()){
            cerr<<"no se pudo abrir el archivo "<<nom_arch<<endl;
            exit(1);
        }
        int valor;
        while(file >> valor && valor!=-1){
            arreglo.append(valor);
        }
        file.close();
        return;
    }
};
#endif // LEER_ARC_H
