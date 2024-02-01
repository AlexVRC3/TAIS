
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
int valida(int i, int j, const Matriz<int>& casillas) {
    if (i >= casillas.numfils() || j >= casillas.numcols() || j < 0 || i < 0) return 0;
    else return casillas[i][j];
}

int resolver(const Matriz<int>& tablero, int &columna) {
    int N = tablero.numfils();
    Matriz<int> casillas(N, N, 0);
    int maxCol = -1;
    for (int i = 0; i < N ; i++)
    {
        for (int j = 0; j < N; j++)
        {
            casillas[i][j] = tablero[i][j] + max({ valida(i - 1, j, casillas), valida(i - 1, j - 1, casillas), valida(i -1, j + 1, casillas) });
            if (i == N - 1 && casillas[i][j] > maxCol) { // Sacamos el resultado mirando cual es la maxima puntuacion a la que podemos llegar en la fila superior
                maxCol = casillas[i][j];
                columna = j + 1;
            }
        }
    }
    return maxCol;
}


bool resuelveCaso() {

    // leer los datos de la entrada

    int N;
    cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<int> tablero(N, N);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> tablero[i][j];
        }
    }
    int columna = -1;
    cout << resolver(tablero, columna) << " " << columna << endl;

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
