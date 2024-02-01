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

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int resolver(const vector<int>& cubos, const int N) {
    vector<int> vacas(N, 0);
    
    if (N % 2 == 1) {
        for (int i = 0; i < N; i++)
        {
            vacas[i] = cubos[i];
        }
    }
    else {
        for (int i = 0; i < N - 1; i++)
        {
            vacas[i] = max(cubos[i], cubos[i + 1]);
        }
    }

    for (int d = (N % 2 == 1 ? 2 : 3); d < N; d++)
    {
        for (int i = 0; i < N - d; i++)
        {
            int j = i + d; 
            int comoIzq = cubos[i] + (cubos[i + 1] >= cubos[j] ? vacas[i + 2] : vacas[i + 1]);
            int comoDer = cubos[j] + (cubos[i] >= cubos[j - 1] ? vacas[i + 1]: vacas[i]);
            vacas[i] = max(comoIzq, comoDer);
        }
    }
    return vacas[0];
}


bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    cin >> N;

    if (N == 0)  // fin de la entrada
        return false;

    vector<int> cubos(N);
    for (int& i : cubos)
        cin >> i;

    cout << resolver(cubos, N) << "\n";

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
