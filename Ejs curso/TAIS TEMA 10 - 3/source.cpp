
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
Oij = "X" si hay obras en la interseccion [i][j], '.' si no las hay.
N = numero de calles este-oeste
M = numero de calles norte-sur


RECURSION
---------

caminos (i,j) = cuantos caminos diferentes hay para llegar a la interseccion [i][j] desde [1][1] con un camino de longitud i - 1 + j - 1

                {    0                                           si Oij = 'X'
caminos (i,j) = {
                {    caminos(i - 1, j) + caminos(i, j-1)         si Oij = '.'


CASOS BASE:
   - caminos(i,j) = 1 si i = 1 /\ j = 1 (intersección inicial)
   - caminos(i,j) = 0 si i < 1 \/ i > N \/ j < 1 \/ j > M (hemos sobrepasado los límites de la ciudad)

Se utiliza programación dinamica ascendente. Se va generando la tabla con N filas y M columnas de arriba a abajo y de izquierda a derecha tal y como define la funcion recursiva. La solucion del problema
quedará almacenada en la ultima posicion de la matriz. Aunque como solo neceistamos la posicion superior y el de su izquierda para calcular cada subprograma, podemos usar un vector. La solucion quedara
en la ultima posicion del vector.

El coste en tiempo de resolver el problema esta en el orden de O(N * M) porque recorremos toda la matriz y sobre cada elemento realizamos operaciones constantes.
El coste en espacio esta en el orden de O(M) por el vector donde almacenamos la fila por la que vamos.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int casilla(int j, const vector<int>& caminos) {
    if (j < 0) return 0;
    else return caminos[j];
}

int caminos(const Matriz<char>& matriz) {
    int N = matriz.numfils();
    int M = matriz.numcols();
    vector<int> caminos(M, 0);
    caminos[0] = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (matriz[i][j] == 'X')
                caminos[j] = 0;
            else
                caminos[j] = caminos[j] + casilla(j - 1, caminos);
        }
    }
    return caminos[M - 1];
}

//int casilla(int i, int j, const Matriz<int>& caminos) {
//    if (i < 0 || i >= caminos.numfils() || j < 0 || j >= caminos.numcols()) return 0;
//    else return caminos[i][j];
//}
//
//int caminos(const Matriz<char>& matriz) {
//    int N = matriz.numfils();
//    int M = matriz.numcols();
//    Matriz<int> caminos(N,M, 0);
//    caminos[0][0] = 1;
//    for (int i = 0; i < N; i++)
//    {
//        for (int j = 0; j < M; j++)
//        {
//            if (i != 0 || j != 0) {
//                if (matriz[i][j] == 'X')
//                    caminos[i][j] = 0;
//                else
//                    caminos[i][j] = casilla(i - 1, j, caminos) + casilla(i, j - 1, caminos);
//            }
//           
//        }
//    }
//    return caminos[N-1][M-1];
//}


bool resuelveCaso() {

    // leer los datos de la entrada
    int N, M;

    cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<char> matriz(N, M);
    char aux;

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
