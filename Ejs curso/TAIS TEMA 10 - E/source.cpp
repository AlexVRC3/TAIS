
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


#include "Matriz.h"


/*@ <answer>
* 
NOTACIONES
----------
Aij = el valor de la matriz en esa posicion
N = numero de filas de la matriz
M = numero de de columnas de la matriz


RECURSION
---------

caminos (i,j) = cuantos caminos diferentes hay para llegar a la interseccion [i][j] desde [1][1] con un camino de longitud i - 1 + j - 1 teniendo en cuenta los saltos

                { 1, si i = 0 /\ j = 0 (intersección inicial)         Caso base
caminos(i, j) = {
                { 0, si i < 0 \/ i >= N \/ j < 0 \/ j >= M (si esta fuera de los límites de la matriz no se tiene en cuenta para actualizar)         Caso Base
                {
                { caminos(i - Aij, j) + caminos(i, j - Aij), de lo contrario         Caso Recursivo
                      

Llamada inicial : caminos(N,M)

EXPLICACION Y COSTE
-------------------

Se utiliza programación dinamica ascendente. Se va generando la tabla con N filas y M columnas de arriba a abajo y de izquierda a derecha tal y como define la funcion recursiva ya que para calcular
cada subproblema necesitas la posicion superior teniendo en cuenta el salto de tamaño Aij y la de la izquierda con el mismo salto. Mantenemos una matriz en la que vamos guardando las soluciones (reduccion
de espacio adicional no contemplada en esta entrega en concreto) El resultado del problema quedará almacenada en la ultima posicion de la matriz.

El coste en tiempo de resolver el problema esta en el orden de O(N * M) porque recorremos toda la matriz y sobre cada elemento realizamos operaciones constantes.
El coste en espacio esta en el orden de O(N * M) por la matriz donde almacenamos las soluciones de los problemas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

 int caminos(const Matriz<int>& matriz) {
    int N = matriz.numfils();
    int M = matriz.numcols();
    Matriz<int> caminos(N,M, 0);
    caminos[0][0] = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (caminos[i][j] > 0) {
                int salto_der = j + matriz[i][j];
                int salto_abajo = i + matriz[i][j];

                if (salto_der < M) {
                    caminos[i][salto_der] += caminos[i][j];
                }
                if (salto_abajo < N) {
                    caminos[salto_abajo][j] += caminos[i][j];
                }
            }
        }
    }
    return caminos[N-1][M-1];
}



bool resuelveCaso() {
   
    int N, M;
    cin >> N >> M;
    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<int> matriz(N, M);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> matriz[i][j];
        }
    }

    cout << caminos(matriz) << endl;

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
