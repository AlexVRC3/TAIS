
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
Vij = El valor que hay en el tablero en la posicion [i][j]
N = dimension del tablero


RECURSION
---------

tablero(i,j) = puntuacion maxima que se puede obtener empezando desde la posicion [i][j]


               {                   tablero(i - 1, j) + Vij                 //empezar en [i][j] y subir arriba
tablero(i,j) = {       max de      tablero(i - 1, j - 1) + Vij             //empezar en [i][j] y subir arriba a la izquierda
               {                   tablero(i - 1, j + 1) + Vij             //empezar en [i][j] y subir arriba a la derecha


CASOS BASE:
   - tablero(i,j) = 0 si i < 1 || i > N
   - tablero(i,j) = 0 si j < 1 || j > N

Se utiliza programación dinamica ascendente. Se va generando la tabla con N filas y columnas de arriba a abajo y de izquierda a derecha tal y como define la funcion recursiva. La solucion del problema
quedará almacenada en la ultima fila de la matriz y sera el maximo valor de esa misma. Cabe destacar que como para calcular cada posicion solo necesitamos las posiciones [i - 1][j - 1], [i - 1][j] y 
[i - 1][j + 1], podemos mantener un unico vector donde se va actualizando la posicion j (y la superior derecha se guarda en una variable auxiliar).

El coste en tiempo de resolver el problema esta en el orden de O(N^2) porque recorremos toda la matriz y sobre cada elemento realizamos operaciones constantes.
El coste en espacio esta en el orden de O(N) por el vector donde almacenamos la solucion de los subproblemas

i - 1 | j | i

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct tSol {
    int suma;
    int col_ini;
};

int casilla(int i, int j, const Matriz<int>& matriz) {
    int N = matriz.numfils();
    if (i < 0 || i >= N || j < 0 || j >= N)
        return 0;
    else
        return matriz[i][j];
}

//int casilla(int j, const vector<int>& v) {
//    int N = v.size();
//    if (j < 0 || j >= N)
//        return 0;
//    else
//        return v[j];
//}


//tSol resolver(const Matriz<int>& matriz) {
//    int N = matriz.numfils();
//    int puntuacion = -1, inicio = -1;
//    Matriz<int> pd(N, N, 0);
//
//    for (int i = 0; i < N; i++)
//    {
//        for (int j = N - 1; j>= 0; j--)
//        {
//            int v1 = casilla(i - 1, j, pd) + matriz[i][j];
//            int v2 = casilla(i - 1, j - 1, pd) + matriz[i][j];
//            int v3 = casilla(i - 1, j + 1, pd) + matriz[i][j];
//            pd[i][j] = max(v1, v2);
//            pd[i][j] = max(pd[i][j], v3);
//            if (i == N - 1) {
//                if (pd[i][j] >= puntuacion) {
//                    puntuacion = pd[i][j];
//                    inicio = j;
//                }
//            }
//        }
//    }
//
//    return { puntuacion, inicio + 1};
//}

tSol resolver(const Matriz<int>& matriz) {
    int N = matriz.numfils();
    int puntuacion = -1, inicio = -1;
    Matriz<int> pd(N, N, 0);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int v1 = casilla(i - 1, j, pd) + matriz[i][j];
            int v2 = casilla(i - 1, j - 1, pd) + matriz[i][j];
            int v3 = casilla(i - 1, j + 1, pd) + matriz[i][j];
            pd[i][j] = max(v1, v2);
            pd[i][j] = max(pd[i][j], v3);
            if (i == N - 1) {
                if (pd[i][j] > puntuacion) {
                    puntuacion = pd[i][j];
                    inicio = j;
                }
            }
        }
    }

    return { puntuacion, inicio + 1 };
}

//tSol resolver(const Matriz<int>& matriz) {
//    int N = matriz.numfils();
//    int puntuacion = -1, inicio = -1;
//    int aux = 0;
//    vector<int> v(N, 0);
//
//    for (int i = 0; i < N; i++)
//    {
//        for (int j = N - 1; j >= 0; j--)
//        {
//            int v1 = casilla(j - 1, v) + matriz[i][j];
//            int v2 = casilla(j, v) + matriz[i][j];
//            int v3 = aux + matriz[i][j];
//            aux = v[j];
//            v[j] = max(v1, v2);
//            v[j] = max(v[j], v3);
//            if (i == N - 1) {
//                if (v[j] >= puntuacion) {
//                    puntuacion = v[j];
//                    inicio = j;
//                }
//            }
//        }
//    }
//
//    return { puntuacion, inicio + 1 };
//}



bool resuelveCaso() {

    // leer los datos de la entrada

    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    Matriz<int> matriz(N, N);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> matriz[i][j];
        }
    }


    tSol sol = resolver(matriz);

    cout << sol.suma << " " << sol.col_ini << endl;
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
