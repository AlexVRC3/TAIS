
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

#include "Digrafo.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Solucion {
public:
    Solucion(Digrafo const& g) : visit(g.V(), false), apilado(g.V(), false), hayciclo(false) {
           dfs(g, 0);
    }
    bool hayCiclo() const { return hayciclo; }

    bool hayCamino(int v) const {
        return visit[v];
    }

private:
    vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
    vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
    bool hayciclo;

    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (!visit[w]) { // encontrado un nuevo vértice, seguimos
                dfs(g, w);
            }
            else if (apilado[w]) { // hemos detectado un ciclo

                hayciclo = true;
            }
        }
        apilado[v] = false;
    }

};

bool resuelveCaso() {

    // leer los datos de la entrada
    int L;
    cin >> L;

    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo dg(L + 1);
    char aux;
    int salto;
    for (int i = 0; i < L; i++)
    {
        cin >> aux;
        if (aux == 'A') {
            dg.ponArista(i, i + 1);
        }
        else if (aux == 'J') {
            cin >> salto;
            dg.ponArista(i, salto - 1);
        }
        else {
            cin >> salto;
            dg.ponArista(i, salto - 1);
            dg.ponArista(i, i + 1);
        }
           
    }

    Solucion sol(dg);
    if (!sol.hayCiclo())
        cout << "SIEMPRE\n";
    else if (sol.hayCamino(L))
        cout << "A VECES\n";
    else
        cout << "NUNCA\n";

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
