#ifndef LEER_ARC_H
#define LEER_ARC_H
#include <iostream>
#include <fstream>
#include <string>
#include "Arr.h"//incluyo mi librería/archivo Arr.h
using namespace std;
class arch{//clase para abrir el archivo
    public:
    Arr arreglo;//llamo a la clase arreglo
    void lectura(string nom_arch){//funcion de lectura del archivo
        ifstream file(nom_arch);
        if(!file.is_open()){//compruebo que haya abierto correctamente el archivo, de lo contrario da error y cierra el programa
            cerr<<"no se pudo abrir el archivo "<<nom_arch<<endl;
            exit(1);
        }
        int valor;//auxiliar para convertir los valores del archivo a enteros y pegarlos a la lista
        while(file >> valor && valor!=-1){
            arreglo.append(valor);//se añaden a la lista
        }
        file.close();//se cierra el archivo para no tener leakeos de memoria
        return;//retorna de la funcion void
    }
};
#endif // LEER_ARC_H
