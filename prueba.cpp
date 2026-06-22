#include <iostream>
#include <cmath>

using namespace std;

struct edificio {
    int id;
    edificio* siguiente;
    edificio(int tem) {
        id = tem;
        siguiente = nullptr;
    }
};

class grafo {
    private:
        int nverte;
        edificio** condo;
    public:
        grafo(int n) {
            nverte = n;
            condo = new edificio*[n];
            for (int i = 0; i < n; ++i) {
                condo[i] = nullptr;
            }
        }
        ~grafo() {
            for (int i = 0; i < nverte; ++i) {
                edificio* actual = condo[i];
                while (actual != nullptr) {
                    edificio* temp = actual;
                    actual = actual->siguiente;
                    delete temp;
                }
            }
            delete[] condo;
        }
        void construiredificio(int inicio, int destino) {
            edificio* nuevo = new edificio(destino);
            nuevo->siguiente = condo[inicio];
            condo[inicio] = nuevo;
        }
        void eliminar_dependencia(int inicio, int destino) {
            edificio* actual = condo[inicio];
            edificio* anterior = nullptr;
            while (actual != nullptr) {
                if (actual->id == destino) {
                    if (anterior == nullptr) {
                        condo[inicio] = actual->siguiente;
                    } else {
                        anterior->siguiente = actual->siguiente;
                    }
                    delete actual;
                    return;
                }
                anterior = actual;
                actual = actual->siguiente;
            }
        }
        int nVertex() { return nverte; }
        edificio* dependencias_getter(int inicio) { return condo[inicio]; }
};

struct ElementoCola {
    int id;
    int tiempo_inicio;
};

class ColaPrioridad {
    private:
        ElementoCola* heap;
        int capacidad;
        int tamano;

        void intercambiar(ElementoCola& a, ElementoCola& b) {
            ElementoCola temp = a;
            a = b;
            b = temp;
        }

        void hundir(int i) {
            int izq = 2 * i + 1;
            int der = 2 * i + 2;
            int menor = i;
            //se ordenan de menor a mayor en cuanto tiempo, si es que son iguales se hace por el id
            if (izq < tamano && (heap[izq].tiempo_inicio < heap[menor].tiempo_inicio || 
                                (heap[izq].tiempo_inicio == heap[menor].tiempo_inicio && heap[izq].id < heap[menor].id))) {
                menor = izq;
            }
            
            if (der < tamano && (heap[der].tiempo_inicio < heap[menor].tiempo_inicio || 
                                (heap[der].tiempo_inicio == heap[menor].tiempo_inicio && heap[der].id < heap[menor].id))) {
                menor = der;
            }
            
            if (menor != i) {
                intercambiar(heap[i], heap[menor]);
                hundir(menor); 
            }
        }

    public:
        ColaPrioridad(int cap) {
            capacidad = cap;
            tamano = 0;
            heap = new ElementoCola[capacidad];
        }
        ~ColaPrioridad() { 
            delete[] heap; 
        }
        
        bool vacia() { 
            return tamano == 0; 
        }
        
        void insertar_rapido(int id, int t_inicio) {
            heap[tamano++] = {id, t_inicio};
        }

        void construir_heap() {
            for (int i = (tamano / 2) - 1; i >= 0; i--) {
                hundir(i);
            }
        }

        void insertar(int id, int t_inicio) {
            int i = tamano++;
            heap[i] = {id, t_inicio};
            while (i != 0 && (heap[(i - 1) / 2].tiempo_inicio > heap[i].tiempo_inicio || 
                             (heap[(i - 1) / 2].tiempo_inicio == heap[i].tiempo_inicio && heap[(i - 1) / 2].id > heap[i].id))) {
                intercambiar(heap[i], heap[(i - 1) / 2]);
                i = (i - 1) / 2;
            }
        }
        
        int extraer() {
            if (tamano <= 0) return -1;
            int raiz = heap[0].id;
            heap[0] = heap[--tamano];
            if (tamano > 0) hundir(0);
            return raiz;
        }
};

int ordenamiento_y_deteccion(grafo& g, int* tiempo, int* orden_salida) {
    int n = g.nVertex();
    int* libreta = new int[n];
    int* tiempo_final = new int[n];
    //se resetean los contadores a 0 y se guardan los tiempos "iniciales" para poder empezar a contar 
    for (int j = 0; j < n; ++j) {
        tiempo_final[j] = tiempo[j];
        libreta[j] = 0; 
    }
    // se recorren los edificios contando la cantidad de dependencias de cada uno y guardando esto en un arreglo [0,3,1.....,0] 
    for (int j = 0; j < n; ++j) {
        edificio* aux = g.dependencias_getter(j);
        while (aux != nullptr) {
            libreta[aux->id]++;
            aux = aux->siguiente;
        }        
    }

    ColaPrioridad cola(n);
    // Se añaden al arreglo de la cola los edificios sin dependencias iniciales mediante insertar_rapido,y luego se ordenan para formar el heap
    for (int j = 0; j < n; ++j) {
        if (libreta[j] == 0) {
            cola.insertar_rapido(j, 0); 
        }
    }
    cola.construir_heap();
    // se revisan los edificios que dependen de "current"(destinos), se calcula cuanto va a demorar en terminar de construir el edificio "destino" y si este camino hace que se demore su construccion se actualiza su tiempo final acumulado en el contador 
    int index = 0;
    while (!cola.vacia()) {
        int current = cola.extraer();
        orden_salida[index++] = current;
        
        edificio* i = g.dependencias_getter(current);
        while (i != nullptr) {
            int destino = i->id;
            if (tiempo_final[current] + tiempo[destino] > tiempo_final[destino]) {
                tiempo_final[destino] = tiempo_final[current] + tiempo[destino];
            }
            libreta[destino]--;
            if (libreta[destino] == 0) {
                int tiempo_inicio_destino = tiempo_final[destino] - tiempo[destino];
                cola.insertar(destino, tiempo_inicio_destino);
            }
            i = i->siguiente;
        }
    }
    
    delete[] libreta;
    ////aqui se revisan posibles fallas como dependencias cíclicas, si no hay se obtiene el tiempo maximo total
    if (index != n) {
        delete[] tiempo_final;
        return -1;
    }
    
    int tiempo_maximo = 0;
    for (int j = 0; j < n; ++j) {
        if (tiempo_final[j] > tiempo_maximo) {
            tiempo_maximo = tiempo_final[j];
        }
    }
    
    delete[] tiempo_final;
    return tiempo_maximo;
}

int main() {
    int n, m, q;
    if (!(cin >> n >> m >> q)) return 0;

    int* tiempo = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> tiempo[i];
    }

    grafo g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g.construiredificio(a - 1, b - 1);//se les resta uno porque se empieza desde 0
    }

    int* orden_salida = new int[n];

    int tiempo_total = ordenamiento_y_deteccion(g, tiempo, orden_salida);
    if (tiempo_total == -1) {
        cout << "-1\n";
    } else {
        for (int i = 0; i < n; ++i) cout << (orden_salida[i] + 1) << " ";
        cout << "\n" << tiempo_total << "\n";
    }

    int q_raiz = sqrt(q);
    int contador_de_q = 0;

    for (int i = 0; i < q; ++i) { //los tipos de consulta
        int tipo;
        cin >> tipo;

        if (tipo == 1) {
            int id, nuevo_tiempo;
            cin >> id >> nuevo_tiempo;
            tiempo[id - 1] = nuevo_tiempo;
        } 
        else if (tipo == 2) {
            int a, b;
            cin >> a >> b;
            g.construiredificio(a - 1, b - 1);
        } 
        else if (tipo == 3) {
            int a, b;
            cin >> a >> b;
            g.eliminar_dependencia(a - 1, b - 1);
        }

        contador_de_q++;
        //cuando se llega al maximo de la cantidad de consultas, se muestra el resultado del saco de consultas y se resetea para el siguiente conjunto
        if (contador_de_q == q_raiz) {  
            tiempo_total = ordenamiento_y_deteccion(g, tiempo, orden_salida);
            if (tiempo_total == -1) {
                cout << "-1\n";
            } else {
                for (int j = 0; j < n; ++j) cout << (orden_salida[j] + 1) << " ";
                cout << "\n" << tiempo_total << "\n";
            }
            contador_de_q = 0;
        }
    }

    // si es que q no es un cuadrado perfecto se trata con las que faltaron
    if (contador_de_q > 0) {
        tiempo_total = ordenamiento_y_deteccion(g, tiempo, orden_salida);
        if (tiempo_total == -1) {
            cout << "-1\n";
        } else {
            for (int j = 0; j < n; ++j) cout << (orden_salida[j] + 1) << " ";
            cout << "\n" << tiempo_total << "\n";
        }
    }

    delete[] tiempo;
    delete[] orden_salida;
    return 0;
}