#ifndef ARR_H
#define ARR_H
#include <iostream>
#include <cstdlib> //necesario para el exit(1)
using namespace std;
class Arr { //clase para manejar arreglos de forma modular
private:
    int* A;     // bloque de heap arr
    unsigned long n;      // n de elementos
    unsigned long cap;  // límite
public: 
    Arr() { //inicializo variables para evitar errores
        cap=1;  
        n=0;              
        A=new int[cap];
    }
    ~Arr(){   //destructor
        delete[] A;
    }   
    void append(int v){//funcion append solicitada
        if(n==cap){
            int* B= new int[cap*2];
            for(unsigned long i=0; i<n; i++){
                B[i]=A[i];
            }
            delete[] A;
            A=B;
            cap*=2;
        }
        A[n++]=v;
    }
    void remove(){//funcion remove solicitada
        if(n == 0) {
            cout<<"No puedes eliminar valores de un arreglo vacío \n";
            return;
        }
        n--;
        if(n==cap/2 && cap>1){
            int* B= new int[cap/2];
            for(unsigned long i=0; i<n; i++){
                B[i]=A[i];
            }
            delete[] A;
            A=B;
            cap/=2;
        }
    }
    bool setvalue(unsigned long i, int v){//funcion setvalue solicitada
        if(i<n){
            A[i]=v;
            return true;
        }
        else{
            return false;
        }
    }
    int getvalue(unsigned long i){//funcion getvalue solicitada
        if(i<n){
            return A[i];
    }
        else{
            cerr<<"Error de acceso al arreglo \n";
            exit(1);
        }
    }
    unsigned long size(){//funcion size solicitada
        return n;
    }
};   
#endif // ARR_H
