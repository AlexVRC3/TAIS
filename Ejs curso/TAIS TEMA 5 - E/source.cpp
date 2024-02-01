/*@ <authors>
 *
 * Alejandro Vida Ram�rez de Arellano TAIS71
 * Gabriel Torres Mart�n TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

#include "Digrafo.h" // propios o los de las estructuras de datos de clase

/*@ <answer>

La idea principal es representar el problema mediante un grafo dirigido. En este grafo, los v�rtices corresponden a las instrucciones del programa, y las aristas indican la transici�n hacia la siguiente instrucci�n, teniendo en cuenta las instrucciones de salto o condicionales.
Para identificar la existencia de ciclos en el grafo, implementamos una b�squeda en profundidad (DFS). Durante este recorrido, mantenemos un vector que indica si un v�rtice est� siendo explorado por una llamada DFS anterior. Si detectamos que un v�rtice ya en exploraci�n se encuentra de nuevo, hemos identificado un ciclo en el grafo. 
Gracias a que dise�amos el grafo con un v�rtice adicional, podemos saber si se han recorrido todos los v�rtices o no. Esto nos permite determinar si el programa terminar� "a veces" o si "nunca" finalizar�. Si el grafo es un DAG (Grafo Dirigido Ac�clico), sabemos con certeza que el programa finalizar� siempre su ejecuci�n.
En cuanto a la complejidad, si excluimos la lectura del archivo de entrada, el coste del algoritmo es O(V+A). Esto se debe a que, mediante el DFS, recorremos cada v�rtice una �nica vez y pasamos por las aristas cuando exploramos los v�rtices adyacentes.
 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
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
