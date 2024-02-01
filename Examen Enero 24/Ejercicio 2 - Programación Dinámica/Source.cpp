
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#include "Matriz.h"

/*@ <answer>

N es el tamaño de la secuencia1 y M es el tamaño de la secuencia2

puntuacion(i,j) = Maxima puntuacion que se puede obtener si disponemos de los caracteres del i al N y del j al M respetando las reglas.

                            { puntuacion(i + 1, j) + P[sec1[i]][4]  Guion abajo
puntuacion(i,j) = max entre { puntuacion(i , j + 1) + P[4][sec2[j]]  Guion arriba
                            { puntuacion(i + 1, j + 1) + P[sec1[i]][sec2[j]] Alineamos los caracteres

Casos base:
    - i == N puntuacion(i,j) = puntuacion(i, j + 1) hasta que se termine j porque ya no quedan mas caracteres en i y hay que rellenar con guiones
    - j == M puntuacion(i,j) = puntuacion(i + 1, j) hasta que se termine i porque ya no quedan mas caracteres en j y hay que rellenar con guiones
    - i == N && j == M puntuacion(i,j) = 0 ya estan alineadas las secuencias

Coste O(N * M) en tiempo por el numero de subproblemas resueltos y  en espacio O(M) por la matriz que solo tiene dos filas.


 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int indice(char c) {
    if (c == 'A')
        return 0;
    else if (c == 'C')
        return 1;
    else if (c == 'G')
        return 2;
    else // T
        return 3;

}

int puntuacionAsc(const Matriz<int>& P, const vector<int>& sec1, const vector<int>& sec2) {
    int N = sec1.size();
    int M = sec2.size();
    Matriz<int> puntuacion(2, M, 0);

    for (int j = 0; j <= M; ++j) {
        puntuacion[0][j] = j * P[4][sec2[j - 1]]; // Penalización por guiones en sec2
    }

    for (int i = 1; i <= N; ++i) {
        puntuacion[i % 2][0] = i * P[sec1[i - 1]][4]; // Penalización por guiones en sec1
        for (int j = 1; j <= M; ++j) {
            int v1 = puntuacion[(i - 1) % 2][j] + P[sec1[i - 1]][4]; // [X,-]
            int v2 = puntuacion[i % 2][j - 1] + P[4][sec2[j - 1]]; // [-,X]
            int v3 = puntuacion[(i - 1) % 2][j - 1] + P[sec1[i - 1]][sec2[j - 1]]; // [X,Y]

            puntuacion[i % 2][j] = max({ v1, v2, v3 });
        }
    }

    return puntuacion[N % 2][M];
}

int puntuacion(Matriz<int>& m, const Matriz<int>& P, int i, int j, const vector<int>& sec1, const vector<int>& sec2) {
    int& res = m[i][j];
    if (res == -1) {
        
        if (i == sec1.size() && j == sec2.size())
            res = 0;
        else if (i == sec1.size())
            res = puntuacion(m, P, i, j + 1, sec1, sec2) + P[4][sec2[j]]; // secuencia1 terminada hay que rellenar con guiones
        else if(j == sec2.size())
            res = puntuacion(m, P, i + 1, j, sec1, sec2) + P[sec1[i]][4]; // secuencia2 terminada hay que rellenar con guiones
        else {
            int v1 = puntuacion(m, P, i + 1, j, sec1, sec2) + P[sec1[i]][4]; // [X,-]
            int v2 = puntuacion(m, P, i, j + 1, sec1, sec2) + P[4][sec2[j]]; // [-,X]
            int v3 = puntuacion(m, P, i + 1, j + 1, sec1, sec2) + P[sec1[i]][sec2[j]]; // [X,Y]

            res = max({ v1, v2, v3 });
        }
    }
    return res;
}


void resuelveCaso() {
    Matriz<int> P(5, 5);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cin >> P[i][j];
        }
    }

    int numSec;
    cin >> numSec;
    vector<int> sec1;
    vector<int> sec2;
    string linea;

    while (numSec--) {
        cin >> linea;
        for (int i = 0; i < linea.size(); i++)
        {
            sec1.push_back(indice(linea[i]));
        }
        cin >> linea;
        for (int i = 0; i < linea.size(); i++)
        {
            sec2.push_back(indice(linea[i]));
        }

        int N = sec1.size();
        int M = sec2.size();
        Matriz<int> mat(N + 1, M + 1, -1);

        cout << puntuacion(mat, P, 0, 0, sec1, sec2) << endl;
       // cout << puntuacionAsc(P, sec1, sec2) << endl;
        sec1.clear(); // Esto y los casos base es lo que me faltaba en el examen 
        sec2.clear();
    }
 
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
