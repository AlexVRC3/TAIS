
/*@ <authors>
 *
 * Alejandro Vida Ram�rez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

#include "Matriz.h"
#include "EnterosInf.h"

/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

void Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C) {
    int V = G.numfils(); // n�mero de v�rtices de G
    // inicializaci�n
    C = G;
    // actualizaciones de las matrices
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                auto temp = C[i][k] + C[k][j];
                if (temp < C[i][j]) { // es mejor pasar por k
                    C[i][j] = temp;
                }
            }
        }
    }
}

EntInf ordenMax(const Matriz<EntInf>& C) {
    EntInf orden = 0;
    for (int i = 0; i < C.numfils(); i++)
    {
        for (int j = 0; j < C.numcols(); j++)
        {
            orden = max(orden, C[i][j]);
        }
    }
    return orden;
}

pair<bool, EntInf> separacion(const Matriz<EntInf>& G) {
    Matriz<EntInf> C;
    Floyd(G, C);
    bool conexo = true;
    EntInf orden = ordenMax(C);
    if (orden == Infinito)
        conexo = false;
    return{ conexo,orden };
}

bool resuelveCaso() {

    int P, R;
    cin >> P >> R;

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<EntInf> G(P, P, Infinito);
    for (int i = 0; i < P; i++)
    {
        G[i][i] = 0; // Casos base
    }

    string s1, s2;
    int indPersona = 0;
    unordered_map<string, int> personas;
    for (int i = 0; i < R; i++)
    {
        cin >> s1 >> s2;
        if (personas.count(s1) == 0) {
            personas[s1] = indPersona;
            indPersona++;
        }
        if (personas.count(s2) == 0) {
            personas[s2] = indPersona;
            indPersona++;
        }
        G[personas[s1]][personas[s2]] = 1;
        G[personas[s2]][personas[s1]] = 1;
    }
    
    pair<bool, EntInf> sol = separacion(G);
    if (sol.first)
        cout << sol.second << "\n";
    else
        cout << "DESCONECTADA\n";
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
