/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

#include "Digrafo.h" // propios o los de las estructuras de datos de clase

/*@ <answer>

La idea principal es representar el problema mediante un grafo dirigido. En este grafo, los vértices corresponden a las instrucciones del programa, y las aristas indican la transición hacia la siguiente instrucción, teniendo en cuenta las instrucciones de salto o condicionales.
Para identificar la existencia de ciclos en el grafo, implementamos una búsqueda en profundidad (DFS). Durante este recorrido, mantenemos un vector que indica si un vértice está siendo explorado por una llamada DFS anterior. Si detectamos que un vértice ya en exploración se encuentra de nuevo, hemos identificado un ciclo en el grafo. 
Gracias a que diseñamos el grafo con un vértice adicional, podemos saber si se han recorrido todos los vértices o no. Esto nos permite determinar si el programa terminará "a veces" o si "nunca" finalizará. Si el grafo es un DAG (Grafo Dirigido Acíclico), sabemos con certeza que el programa finalizará siempre su ejecución.
En cuanto a la complejidad, si excluimos la lectura del archivo de entrada, el coste del algoritmo es O(V+A). Esto se debe a que, mediante el DFS, recorremos cada vértice una única vez y pasamos por las aristas cuando exploramos los vértices adyacentes.
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


class Solucion {
public:
    Solucion(Digrafo const& dg) : visit(dg.V(), false), enExploracion(dg.V(), false), hayCiclo(false) {
        dfs(dg, 0);
    }

    void answer() {
         
        if (hayCiclo && !visit[visit.size() - 1])
            cout << "NUNCA" << endl;
        else if (hayCiclo && visit[visit.size() - 1])
            cout << "A VECES" << endl;
        else if(!hayCiclo && visit[visit.size() - 1])
            cout << "SIEMPRE" << endl;

    }

private:    

    vector<bool> visit;
    vector<bool> enExploracion;
    bool hayCiclo;

    void dfs(Digrafo const& g, int v) {

        enExploracion[v] = true;
        visit[v] = true;

        for (int w : g.ady(v)) {
            if (!visit[w])
                dfs(g, w);
            else if (enExploracion[w]) {
                hayCiclo = true;
            }
        }
        enExploracion[v] = false;
    }
};

bool resuelveCaso() {

    int L;
    cin >> L;

    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo dg(L + 1);

    for (int i = 0; i < L; i++) {
        char I; 
        cin >> I;

        switch (I) {
            case 'A':
                dg.ponArista(i, i + 1);
                break;

            case 'J':
            case 'C':
                int n; std::cin >> n;
                dg.ponArista(i, n - 1);

            if (I == 'C')
                dg.ponArista(i, i + 1);
            break;
        }
    }

    Solucion sol(dg);

    sol.answer();

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
