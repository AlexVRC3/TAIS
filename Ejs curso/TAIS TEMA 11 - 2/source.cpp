
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
T = segundos que permite la botella estar bajo el agua
N = numero de cofres
Pi = profundidad a la que esta el cofre i
Oi = cantidad de oro que contiene el cofre i


RECURSION
---------

oro(i,j) = cantidad maxima de oro que se puede conseguir cuando quedan j segundos debajo del agua y podemos recoger cofres del 1 al i

                { oro(i - 1,j)                                      si 3Pi > j
oro(i,j) =      {
                { max(oro(i - 1, j) , oro(i - 1, j - 3Pi) + Oi      si 3Pi <= j


Llamada inicial : oro(N,M)

EXPLICACION Y COSTE
-------------------

Se utiliza programación dinamica descendente de manera que se guarda en una matriz la solucion a los subproblemas que se van resolviendo, dado que en la recursion se repiten muchos calculos de
subproblemas. La solución queda almacenada en la posicion de la matriz N,T ya que la matriz tiene N + 1 filas y T + 1 columnas.

El coste en tiempo de resolver el problema esta en el orden de O(N * T) porque recorremos toda la matriz y sobre cada elemento realizamos operaciones constantes.
El coste en espacio esta en el orden de O(N * T) por la matriz donde almacenamos las soluciones de los problemas.

Podriamos conseguir reducir el espacio adicional a O(T) aplicando programacion ascendente pero al necesitar mostrar por pantalla el oro y la profundidad de cada cofre recogido es obligatorio
utilizar una matriz.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

// calcula la longitud del mayor palíndromo en patitos[i..j]
int patin_rec(string const& patitos, int i, int j, Matriz<int>& patin) {
    int& res = patin[i][j];
    if (res == -1) {
        if (i > j) res = 0;
        else if (i == j) res = 1;
        else if (patitos[i] == patitos[j])
            res = patin_rec(patitos, i + 1, j - 1, patin) + 2;
        else
            res = max(patin_rec(patitos, i + 1, j, patin),
                patin_rec(patitos, i, j - 1, patin));
    }
    return res;
}


// devuelve el palíndromo más largo en patitos[i..j]
string reconstruir(string const& patitos, Matriz<int> const& patin,
    int i, int j) {
    if (i > j) return {};
    if (i == j) return { patitos[i] };
    if (patitos[i] == patitos[j])
        return patitos[i] + reconstruir(patitos, patin, i + 1, j - 1) + patitos[j];
    else if (patin[i][j] == patin[i + 1][j])
        return reconstruir(patitos, patin, i + 1, j);
    else
        return reconstruir(patitos, patin, i, j - 1);
}

// añade al final de sol el palíndromo más largo en patitos[i..j]
void reconstruir(string const& patitos, Matriz<int> const& patin,
    int i, int j, string& sol) {
    if (i > j) return;
    if (i == j) sol.push_back(patitos[i]);
    else if (patitos[i] == patitos[j]) {
        sol.push_back(patitos[i]);
        reconstruir(patitos, patin, i + 1, j - 1, sol);
        sol.push_back(patitos[j]);
    }
    else if (patin[i][j] == patin[i + 1][j])
        reconstruir(patitos, patin, i + 1, j, sol);
    else
        reconstruir(patitos, patin, i, j - 1, sol);
}

bool resuelveCaso() {

    string patitos;
    cin >> patitos;

    if (!std::cin)  // fin de la entrada
        return false;

    int n = patitos.length();

    Matriz<int> patindromo(n, n, -1);
    cout << patin_rec(patitos, 0, n - 1, patindromo) << '\n';
    cout << reconstruir(patitos, patindromo, 0, n - 1) << '\n';
    string sol;
    reconstruir(patitos, patindromo, 0, n - 1, sol);
    cout << sol << '\n';

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
