
/*@ <answer>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "IndexPQ.h"
#include <utility>
using namespace std;


/*@ <answer>

    Como las operaciones en la IndexPQ tienen coste O(log n) el coste total es O(n log n) debido al recorrido del bucle principal

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
    int n, citado;
    string tipo, palabra;
    IndexPQ<string, pair<int, int>, greater<pair<int, int>>> tendencia;
    vector<pair<string, pair<int, int>>> tc;

    cin >> n;
    if (!cin)
        return false;

    for (int i = 0; i < n; i++) {
        cin >> tipo;
        if (tipo == "C" || tipo == "E") {
            cin >> palabra >> citado;
            pair<int, int> par = (tipo == "C") ? make_pair(citado, i) : make_pair(-citado, i);
            tendencia.update2(palabra, par);
        }
        else if (tipo == "TC") {

            if (tendencia.size() != 0) {
                auto p1 = tendencia.top();
                cout << 1 << " " << p1.elem << "\n";
                tendencia.pop();

                if (tendencia.size() != 0) {
                    auto p2 = tendencia.top();
                    cout << 2 << " " << p2.elem << "\n";
                    tendencia.pop();

                    if (tendencia.size() != 0) {

                        cout << 3 << " " << tendencia.top().elem << "\n";

                    }
                    tendencia.push(p2.elem, p2.prioridad);
                }
                tendencia.push(p1.elem, p1.prioridad);
            }
        }
    }
    cout << "---\n";

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
