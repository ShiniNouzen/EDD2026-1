**Integrantes:** Martin Guzmán y Axel Garrido
**SO:** Ubuntu y Arch Linux respectivamente (g++ 15.1.1 en el caso de Arch)
**Versión de C++:** 17
**Versión del compilador:** 15.2.0

**Cómo funciona el código:** El código funciona con una mezcla del algoritmo de Kahn (por Arthur B. Kahn) y la lógica de caminos críticos. A esto se le integra una cola de prioridad (Min-Heap). Se utilizó como referencia base el tutorial de Programiz (https://www-programiz-com.translate.goog/cpp-programming/priority-queue?_x_tr_sl=en&_x_tr_tl=es&_x_tr_hl=es&_x_tr_pto=tc), el cual fue modificado estructuralmente para cumplir con la doble condición de priorización del problema: ordenar por el menor tiempo de inicio acumulado y desempatar evaluando el menor ID del edificio.
