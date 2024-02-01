
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


/*@ <answer>

Coste O(V + A)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    // leer los datos de la entrada
    int V, A;
    cin >> V >> A;

    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> salida(V, 0);
    vector<int> entrada(V, 0);

    int v, w;
    for (int i = 0; i < A; i++)
    {
        cin >> v >> w;
        salida[v]++;
        entrada[w]++;
    }

    bool sumidero = false;
    int idx = -1;

    for (int i = 0; i < V; i++)
    {
        if (salida[i] == 0 && entrada[i] == V - 1) {
            sumidero = true;
            idx = i;
        }
    }

    if (sumidero)
        cout << "SI " << idx << endl;
    else
        cout << "NO" << endl;

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
