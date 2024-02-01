
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "EnterosInf.h"

/*@ <answer>

NOTACIONES
----------
L = longitud del tronco
N = numero de cortes a realizar + 2 (son las del inicio y el final)
Mi = punto del tronco en el que se debe realizar el corte i

RECURSION
---------

minCoste(i,j) = minimo esfuerzo para realizar cortes en las marcas desde la i + 1 hasta la j - 1

minCoste(i,j) = min tq i < k < j (minCoste(i,k) + minCoste(k,j)) + 2 * (Mj - Mi)

EXPLICACION Y COSTE
-------------------

Se utiliza programación dinamica ascendente y de esta manera se va rellenando la tabla con N filas y N columnas. La diagonal principal y todas las posiciones que quedan por debajo de ella
son 0 ya que j >= i. La diagonal que esta por encima de la principal tambien vale 0 por ser la diagonal de los casos base. Para rellenar el resto de matriz se ira haciendo por diagonales hasta llegar
a la posicion superior derecha de la matriz, donde quedará almacenada la solución al problema (caso i = 0, j = N - 1).

En cuanto al coste:
   - El coste en tiempo esta en el orden de O(N^2 / 2) = O (N^2) aunque recorramos solo la mitad de la matriz. (No se si seria O(N^3) ya que el ultimo bucle tambien depende de i y j no solo de N ahi tengo la duda
   - El coste en espacio esta en el orden de O(N^2), por la matriz donde guardamos las soluciones de los subproblemas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

const int INF = 1000000000;

using matriz = vector<vector<EntInf>>;

EntInf minCoste(const vector<int>& cortes) {
    int N = cortes.size();
    matriz mat(N, vector<EntInf>(N, 0));
    for (int d = 2; d < N; d++) // recorre diagonales
    {
        for (int i = 0; i < N - d; i++) // recorre elementos de cada diagonal
        {
            int j = i + d;
            mat[i][j] = INF;
            for (int k = i + 1; k < j; k++)
            {
                EntInf aux = mat[i][k] + mat[k][j] + 2 * (cortes[j] - cortes[i]);
                if (aux < mat[i][j]) // es mejor hacer el corte por k
                    mat[i][j] = aux;
            }
        }
    }
    return mat[0][N - 1];
}

bool resuelveCaso() {

    int L, N;
    cin >> L >> N;
    if (L == 0 && N == 0)
        return false;

    vector<int> cortes(N + 2);
    cortes[0] = 0;
    cortes[N + 1] = L;
    for (int i = 1; i <= N; i++)
    {
        cin >> cortes[i];
    }

    cout << minCoste(cortes) << endl;

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
