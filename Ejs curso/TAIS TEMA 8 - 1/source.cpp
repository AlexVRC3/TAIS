
/*@ <authors>
 *
 * Alejandro Vida Ram�rez de Arellano TAIS71
 * Gabriel Torres Mart�n TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;



/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

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
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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
