**Integrantes:** Martin Guzmán y Axel Garrido
**SO:** Ubuntu y Arch Linux respectivamente (g++ 15.1.1 en el caso de Arch)
**Versión de C++:** 17
**Versión del compilador:** 15.2.0

**Cómo funciona el código:** El código implementa un arreglo dinámico en el cual se usa `class Arr` para administrar memoria. Utiliza `append` para agregar valores, donde revisa si la cantidad de elementos (`n`) iguala a `cap`, que sería la capacidad de memoria, reserva un nuevo bloque de memoria con el doble de capacidad, procede a copiar los datos, eliminar el bloque de memoria anterior y añade el nuevo valor. `remove` elimina el último valor, revisa si es que la cantidad de elementos se reduce a la mitad de la capacidad (`cap`) y disminuye la reserva de memoria a la mitad. Se usan `setvalue` y `getvalue` para acceder, modificar y validar los datos en las posiciones requeridas. Se usa `class arch` para abrir el archivo `.txt` hasta que se encuentre un `-1` o se acabe el archivo y lleva los datos al arreglo. En `main` se crea el "menú" donde el usuario escribe el nombre de su archivo, y elige cómo quiere observar y modificar su archivo con lo que implementamos anteriormente.
