
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#include "Matriz.h"

/*@ <answer>

bizcocho(i,j) = numero de veces que podemos comer la misma fruta en un bizcocho de longitud desde i a j

Fi = 0 si no hay fruta, 1 si hay un trozo de naranja y 2 si hay un trozo de limon


                          { bizcocho(i + 2,j) + (Fi != 0 && Fi == Fi+1)
bizcocho(i,j) = max entre { bizcocho(i,j - 2) + (Fj != 0 && Fj == Fj-1)   
                          { bizcocho(i + 1,j - 1) + (Fi != 0 && Fi == Fj)

Los casos base son cuando i > j = 0 osea los elementos de la primera diagonal de la matriz 

Llamada inicial bizcocho(0,N-1)

Se utiliza programacion dinamica descendente y se van guardando en la matriz los subproblemas ya resueltos para no tener que repetir calculos. La solucion queda almacenada en la posicion
de la matriz[0][N-1]. La parte superior de la matriz es la que nos interesa y el resto de valores en los que i > j son 0. El coste en tiempo es del orden de O(N*N) que es el numero
maximo de llamadas que se podrian realizar y cada una se invoca como mucho 2 veces y la segunda no genera mas trabajo debido a que ya estará calculada. El coste en espacio es del orden de 
O(N*N) debido a la matriz donde almacenamos las soluciones a los subproblemas.


 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

//int posValida(const Matriz<int>& bizcocho, int i, int j) {
//    if (i < 0 || i >= bizcocho.numfils() || j < 0 || j >= bizcocho.numcols()) return 0;
//    else return bizcocho[i][j];
//}
//
//int resolver(const vector<int>& frutas, const int N) {
//    Matriz<int> bizcocho(N, N, 0);
//
//    // Las dos primeras diagonales son los casos basicos d = 0 y d = 1
//
//    for (int d = 2; d <= N; d++) // Recorre diagonales
//    {
//        for (int i = N - d; i >= 0; i--) // Recorre elementos de la diagonal
//        {
//            int j = i + d - 1;
//            int b1 = posValida(bizcocho, i + 2, j) + (frutas[i] != 0 && frutas[i] == frutas[i + 1]);
//            int b2 = posValida(bizcocho, i, j - 2) + (frutas[j] != 0 && frutas[j] == frutas[j - 1]);
//            int b3 = bizcocho[i + 1][j - 1] + (frutas[i] != 0 && frutas[i] == frutas[j]);
//
//            bizcocho[i][j] = max({ b1,b2,b3 });
//        }
//    }
//    return bizcocho[0][N - 1];
//}

int resolver(const vector<int>& frutas, int i, int j, Matriz<int>& bizcocho) {
    if (i < 0 || i >= bizcocho.numfils() || j < 0 || j >= bizcocho.numcols()) return 0;
    int& res = bizcocho[i][j];
    if (res == -1) {
        if (i > j) res = 0;
        else {
            int v1 = resolver(frutas, i + 2, j, bizcocho) + (frutas[i] != 0 && frutas[i] == frutas[i + 1]);
            int v2 = resolver(frutas, i, j - 2, bizcocho) + (frutas[j] != 0 && frutas[j] == frutas[j-1]);
            int v3 = resolver(frutas, i + 1, j - 1, bizcocho) + (frutas[i] != 0 && frutas[i] == frutas[j]);
            res = max({ v1,v2,v3 });
        }
    }
    return res;
}
bool resuelveCaso() {

    int N;
    cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;
    vector<int> frutas(N);
    for (int& i : frutas)
        cin >> i;
    Matriz<int> bizcocho(N, N, -1);
    cout << resolver(frutas, 0, N - 1, bizcocho) << endl;

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
