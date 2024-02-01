
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int valida(int j, const vector<int> &formas) {
    if (j < 0 || j >= formas.size()) return 0;
    else return formas[j];
}

int resolver(const Matriz<char>& obras) {
    int N = obras.numfils();
    int M = obras.numcols();
    vector<int> formas(M, 0);
    formas[0] = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (obras[i][j] != 'X') {

                formas[j] += valida(j - 1, formas);
            }
            else {
                formas[j] = 0;
            }
        }
    }

    return formas[M - 1];
}


bool resuelveCaso() {

    int N, M;
    cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<char> obras(N, M);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> obras[i][j];
        }
    }

    cout << resolver(obras) << endl;

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
