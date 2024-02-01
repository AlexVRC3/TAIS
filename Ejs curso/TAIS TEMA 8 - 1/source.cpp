
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

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

int minimizarParches(std::vector<int> const& m, int l) { // O(n) 
    int nParches = 1;
    int maxDist = m[0] + l;

    for (int i = 1; i < m.size(); i++) {
        if (m[i] > maxDist) {
            nParches++;
            maxDist = m[i] + l;
        }
    }

    return nParches;
}


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    int a, l; 
    cin >> a >> l;

    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<int> manguera(a);
    for (int& i : manguera)
        std::cin >> i;

    std::cout << minimizarParches(manguera, l) << "\n";

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
