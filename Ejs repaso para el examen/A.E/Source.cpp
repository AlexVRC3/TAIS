
/*@ <authors>
 *
 * Alejandro Vida Ram�rez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h"

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

int valida(const int i, const int j, const Matriz<int>& formas) {
    if (i >= formas.numfils() || j >= formas.numcols()) return 0;
    else return formas[i][j];
}

int resolver(const Matriz<int>& A) {
    int N = A.numfils();
    int M = A.numcols();
    Matriz<int> formas(N, M, 0);
    formas[N-1][M-1] = 1;
    
    for (int i = N - 1; i >= 0; i--)
    {
        for (int j = M - 1; j >= 0; j--)
        {
            formas[i][j] += valida(i + A[i][j], j, formas) + valida(i, j + A[i][j], formas);
        }
    }
    return formas[0][0];
}


bool resuelveCaso() {

    int N, M;
    cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<int> mat(N, M);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> mat[i][j];
        }
    }
    cout << resolver(mat) << endl;

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
