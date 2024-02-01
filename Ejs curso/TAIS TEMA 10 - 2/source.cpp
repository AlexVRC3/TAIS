
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

#include "EnterosInf.h"
#include "Matriz.h"

/*@ <answer>
Pi = puntuacion del sector i, i € {1,....S}
S = numero de sectores
V = valor que hay que conseguir


RECURSION
---------

dardos (i,j) = minimo número de dardos para conseguir la puntuación j pudiendo tirar dardos a los sectores del 1 al i (Infinito si no es posible)

               {    dardos(i - 1, j)                                 si Pi > j
dardos (i,j) = {
               {    min(dardos(i - 1, j), dardos(i, j - Li) + 1)     si Pi <= j


CASOS BASE:
    - dardos(0,j) = Infinito
    - dardos(i,0) = 0
    - dardos(0,0) = 0

Se utiliza programación dinamica ascendente. Se va generando la tabla con S + 1 filas y V + 1 columnas (puntuaciones de 0 a V). La posicion [0][0] y la primera fila tendran valor Infinito. 
A partir de ahi se recorre la tabla de arriba a abajo y de izquierda a derecha de forma que la solución queda almacenada en la ultima posicion de la tabla. Aunque se puede almacenar la tabla en una matriz
realmente para generar una fila solo necesitamos el valor superior [i - 1][j] y uno de esa misma fila [i][j - Pi]. Para cada posición, cuando nos desplacemos a la derecha no necesitaremos mas el elemento superior,
por lo que podemos mantener un unico vector en el que se va cambiando la posición correspondiente a la j por la que vamos.

El coste en tiempo de resolver el problema esta en el orden de O(S * V) porque recorremos toda la matriz y sobre cada elemento realizamos operaciones constantes.
El coste en tiempo de reconstruir la solución esta en el orden O(K) donde K = max(S,V) ya que en cada vuelta disminuimos una columna o fila como mínimo.
El coste en espacio esta en el orden de O(V) por el vector donde almacenamos la fila por la que vamos.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

vector<int> resolver(vector<int> const& p, int v) {
    int n = p.size();
    vector<EntInf> puntuaciones(v + 1,Infinito);
    puntuaciones[0] = 0;
    // calcular la matriz sobre el propio vector
    for (int i = 1; i <= n; ++i) {
        for (int j = p[i - 1]; j <= v; ++j) {
            puntuaciones[j] = min(puntuaciones[j], puntuaciones[j - p[i - 1]] + 1);
        }
    }

    vector<int> sol;
    if (puntuaciones[v] != Infinito) {
        int i = n, j = v;
        while (j > 0) { // no se ha llegado a la puntuacion
            if (p[i - 1] <= j && puntuaciones[j] == puntuaciones[j - p[i - 1]] + 1) {
                // tomamos una puntuacion de este valor
                sol.push_back(p[i - 1]);
                j = j - p[i - 1];
            }
            else // no tomamos más puntuaciones de este valor
                --i;
        }
    }
    return sol;
}

//vector<int> resolver(vector<int> const& P, int V) {
//    int n = P.size();
//    Matriz<EntInf> puntuaciones(n + 1,V + 1, Infinito);
//    puntuaciones[0][0] = 0;
//    // calcular la matriz sobre el propio vector
//    for (int i = 1; i <= n; ++i) {
//        puntuaciones[i][0] = 0;
//        for (int j = 1; j <= V; ++j) {
//            if (P[i - 1] > j)
//                puntuaciones[i][j] = puntuaciones[i - 1][j];
//            else
//                puntuaciones[i][j] = min(puntuaciones[i - 1][j], puntuaciones[i][j - P[i - 1]] + 1);
//            
//        }
//    }
//
//    vector<int> sol;
//    if (puntuaciones[n][V] != Infinito) {
//        int i = n, j = V;
//        while (j > 0) { // no se ha llegado a la puntuacion
//            if (P[i - 1] <= j && puntuaciones[i][j] == puntuaciones[i][j - P[i - 1]] + 1) {
//                // tomamos una puntuacion de este valor
//                sol.push_back(P[i - 1]);
//                j = j - P[i - 1];
//            }
//            else // no tomamos más puntuaciones de este valor
//                --i;
//        }
//    }
//    return sol;
//}


bool resuelveCaso() {
    int V, S;

    cin >> V >> S;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> puntuaciones(S);
    for (int i = 0; i < S; i++)
    {
        cin >> puntuaciones[i];
    }

    vector<int> sol = resolver(puntuaciones, V);

    if (sol.empty()) {
        cout << "Imposible" << endl;
    }
    else {
        int tam = sol.size();
        cout << tam << ": ";
        auto it = sol.begin();
        while (it != sol.end()) {
            cout << *it;
            if (next(it) != sol.end()) {
                cout << " ";
            }
            it++;
        }
        cout << endl;
    }
   

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
