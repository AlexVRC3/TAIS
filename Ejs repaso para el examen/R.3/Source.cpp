
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#include "Grafo.h"

/*@ <answer>

Se realizan recorridos en anchura desde los vertices del grafo para asi recorrer todas las componentes conexas del mismo. Para cada componente conexa guardamos la cantidad de oro
mas pequeña y la acumulamos en minTotal. De esta manera podemos difundir el rumor con el menor gasto de oro posible. El coste de la solucion es del orden de O(V+A) por los bfs
siendo V el numero de vertices del grafo y A el de aristas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Solucion {
public:
    Solucion(Grafo const& g, const vector<int> &cantidades) : visit(g.V(), false), cantidades(cantidades), min(10001), minTotal(0) {
        for (int i = 0; i < g.V(); i++)
        {
            if (!visit[i]) {
                bfs(g, i);
                minTotal += min;
                min = 10001;
            }
               
        }
    }
 
    int getOroMin() const {
        return minTotal;
    }
   
private:
    vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    int minTotal;
    int min;
    vector<int> cantidades;

    void bfs(Grafo const& g, int orig) {
        queue<int> q;
        visit[orig] = true;
        q.push(orig);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            if (cantidades[v] < min)
                min = cantidades[v];
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int N, M;
    cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;
    vector<int> cantidades(N);
    for (int& i : cantidades)
        cin >> i;
    Grafo g(N);
    int v, w;
    for (int i = 0; i < M; i++)
    {
        cin >> v >> w;
        g.ponArista(v - 1, w - 1);
    }

    Solucion sol(g, cantidades);
    
    cout << sol.getOroMin() << endl;

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
