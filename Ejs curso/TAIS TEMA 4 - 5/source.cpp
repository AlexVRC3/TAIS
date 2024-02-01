
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <deque>
#include <queue>
using namespace std;

#include "Grafo.h" // propios o los de las estructuras de datos de clase



/*@ <answer>

complejidad total del algoritmo se encuentra en el orden de O(C + K * (V + A)), donde C es el número de aristas, 
K es el número de consultas, V es el número de nodos y A es el número de aristas en el grafo.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

using Camino = std::deque<int>;

class NodosLejanos {
    public:
        NodosLejanos(Grafo const& g, int origen, int TTL) : visit(g.V(), false), ant(g.V()), dist(g.V()), alcanzables(0){
         
            bfs(g, origen, TTL);
        }

        int getInAlcanzables() {
            return visit.size() - 1 - alcanzables;
        }
        bool hayCamino(int v) const {
            return visit[v];
        }

        int distancia(int v) {
            return dist[v];
        }

    private:
        vector<bool> visit;
        vector<int> ant;
        vector<int> dist;
        int alcanzables;

        void bfs(Grafo const& g, int vIni, int TTL) {
            std::queue<int> q;
            dist[vIni] = 0; visit[vIni] = true;
            q.push(vIni);
            while (!q.empty()) {
                int v = q.front(); q.pop();
                for (int w : g.ady(v))
                {
                    if (!visit[w]) {
                        ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
                        q.push(w);
                        if (dist[w] <= TTL)
                            alcanzables++;
                    }
                }
            }
        }
       
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, C;
    cin >> N >> C;

    if (!std::cin)  // fin de la entrada
        return false;

    Grafo g(N);

    int v, w;
    for (int i = 0; i < C; i++)
    {
        cin >> v >> w;
        g.ponArista(v - 1, w - 1);
    }
    int K, origen, ttl;
    cin >> K;
    
    for (int i = 0; i < K; i++)
    {
        cin >> origen >> ttl;
        NodosLejanos nl(g, origen - 1, ttl);
        cout << nl.getInAlcanzables() << endl;
        
    }
    cout << "---" << endl;
   
    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución

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
