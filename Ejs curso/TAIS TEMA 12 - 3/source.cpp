
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

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


EntInf recurrencia1(const vector<int>& v, const vector<int>& c, int p) {
    int n = v.size();
    vector<EntInf> f(p + 1, Infinito);
    f[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = p; j > 0; j--)
        {
            int k = 0;
            while (k <= c[i - 1] && k * v[i - 1] <= j) {
                EntInf temp = f[j - k * v[i - 1]] + k;
                if (temp < f[j])
                    f[j] = temp;
                k++;
            }
        }
    }
    return f[p];
}

bool resuelveCaso() {

    int N,P;
    cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> v(N);
    vector<int> c(N);
    for (int i = 0; i < N; i++)
    {
        cin >> v[i];
    }
    for (int i = 0; i < N; i++)
    {
        cin >> c[i];
    }

    cin >> P;

    EntInf sol = recurrencia1(v, c, P);
    if (sol == Infinito)
        cout << "NO" << endl;
    else
        cout << "SI " << sol << endl;

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
