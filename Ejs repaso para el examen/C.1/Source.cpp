
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"
#include "EnterosInf.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
const int INF = 10000000000;

EntInf resolver(const vector<int>& cortes, const int N, const int L) {
    Matriz<EntInf> minEsfuerzo(N, N, 0);

    for (int d = 2; d < N; d++)
    {
        for (int i = 0; i < N - d; i++)
        {
            int j = i + d;
            minEsfuerzo[i][j] = INF;
            for (int k = i + 1; k < j; k++)
            {
                EntInf temp = minEsfuerzo[i][k] + minEsfuerzo[k][j] + 2 * (cortes[j] - cortes[i]);
                if (temp < minEsfuerzo[i][j]) // Es mejor cortar por k
                    minEsfuerzo[i][j] = temp;
            }
        }
    }
    return minEsfuerzo[0][N - 1];
}


bool resuelveCaso() {

    int L, N;
    cin >> L >> N;

    if (L == 0 && N == 0)  // fin de la entrada
        return false;

    vector<int> cortes(N + 2);
    cortes[0] = 0;
    cortes[N + 1] = L;
    for (int i = 1; i <= N ; i++)
    {
        cin >> cortes[i];
    }

    cout << resolver(cortes, N + 2, L) << "\n";

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
