#include <iostream>
#include "Arr.h"//archivo que incluye mi TDA arreglo
#include "leer_arc.h"//archivo que incluye TDA de lectura de archivo
using namespace std;
arch myfile; //chiste tonto, intenté ponerle Linux por Arch pero la consola daba error al ser palabra reservada.
int main(){
    string nombre;
    cout<<"porfavor ingrese el nombre de su archivo sin el prefijo '.txt'\n";
    cin>>nombre;
    nombre+=".txt";
    myfile.lectura(nombre); //se lee y añaden las componentes del archivo llamando a la funcion lectura
    while(true){ //ciclo de interfaz de usuario
        int opt; //variable para asignar opcion en consola
        unsigned long pos; //variable para poner posicion en consola
        int v1; //variable para añadir valores al arreglo en consola
        cout<<"bienvenido a la interfaz de usuario de tu arreglo extensible \n"; 
        cout<<"para asignar un valor entero a una posicion específica dentro del rango, ingrese 1 \n";
        cout<<"para obtener el valor entero de una posicion específica en el rango, ingrese 2 \n";
        cout<<"para agregar un nuevo valor al final del arreglo, ingrese 3 \n";
        cout<<"para remover la última componente del arreglo, ingrese 4 \n";
        cout<<"para saber la cantidad total de componentes en su arreglo, ingrese 5 \n";
        cout<<"para finalizar el programa, ingrese 0 \n"<<endl;
        cin>>opt;//se le asigna un valor a opt
        if(opt==1){ //funcion para cambiar un valor por uno nuevo
            cout<<"ingrese la posicion en el formato (n-1) en que quiere añadir su elemento \n"<<endl;
            cin>>pos;
            cout<<"ingrese el valor a agregar \n"<<endl;
            cin>>v1;
            myfile.arreglo.setvalue(pos, v1);
        }
        else if(opt==2){ //funcion para consultar valor
            cout<<"ingrese la posicion en el formato (n-1) del elemento que desea consultar \n"<<endl;
            cin>>pos;
            cout<<"el valor en la pos "<<pos<<" es: "<<myfile.arreglo.getvalue(pos)<<endl<<endl;
        }
        else if(opt==3){ //funcion append
            cout<<"ingrese el valor a agregar al final del arreglo \n"<<endl;
            cin>>v1;
            myfile.arreglo.append(v1);
        }
        else if(opt==4){ //funcion remove
            myfile.arreglo.remove();
            cout<<"el elemento ha sido removido exitosamente \n"<<endl;
        }
        else if(opt==5){ //funcion size
            cout<<"el número de elementos en el arreglo es: "<<myfile.arreglo.size()<<endl<<endl;
        }
        else if(opt==0){ //funcion para terminar ejecucion
            break;
        }
    }
};

