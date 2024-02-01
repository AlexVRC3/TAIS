/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

#include "Grafo.h" // propios o los de las estructuras de datos de clase

/*@ <answer>

Realizamos 3 recorridos en anchura para calcular las distancias al resto de vertices desde la casa de alex, desde la casa de lucas y desde el trabajo, una vez tenemos eso recorremos todos los vertices del grafo y buscamos el punto de encuentro que nos proporciona un coste minimo del recorrido total.
Explicacion: Coste O(V + A) por el triple uso del recorrido en anchura

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
class Solucion {


public:
    Solucion(Grafo const& g, int a, int l, int t) : visitAlex(g.V(), false), visitLucas(g.V(), false), visitTrabajo(g.V(), false), ant(g.V()), distAlex(g.V(), -1), distLucas(g.V(), -1), distTrabajo(g.V(), -1), a(a), l(l), t(t) {

        bfs(g, a, distAlex, visitAlex);
        bfs(g, l, distLucas, visitLucas);
        bfs(g, t, distTrabajo, visitTrabajo);
    }
    int calcularCostoMinimo() {

        int costoMinimo = distAlex[t] + distLucas[t];
        int idx = -1;  // Inicializamos el índice en -1 para indicar que no se juntan en un camino

        for (int puntoEncuentro = 0; puntoEncuentro < distAlex.size(); puntoEncuentro++) {
            if (distAlex[puntoEncuentro] != -1 && distLucas[puntoEncuentro] != -1) {
                int costo = distAlex[puntoEncuentro] + distLucas[puntoEncuentro] + distTrabajo[puntoEncuentro];
                if (costo < costoMinimo) {
                    costoMinimo = costo;
                    idx = puntoEncuentro;  // Actualizamos el índice si encontramos un punto de encuentro más cercano
                }
            }
        }
        return costoMinimo;
    }

private:

    std::vector<bool> visitAlex;
    std::vector<bool> visitLucas;
    std::vector<bool> visitTrabajo;

    std::vector<int> ant;
    std::vector<int> distAlex;
    std::vector<int> distLucas;
    std::vector<int> distTrabajo;

    int a;
    int l;
    int t;

    void bfs(Grafo const& g, int v, vector<int>& dist, vector<bool>& visit) {
        queue<int> q;
        dist[v] = 0;
        visit[v] = true;
        q.push(v);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    ant[w] = v;
                    dist[w] = dist[v] + 1;
                    visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
};


bool resuelveCaso() {

    int N, C, casaAlex, casaLucas, trabajo;
    cin >> N >> C >> casaAlex >> casaLucas >> trabajo;
    if (!std::cin) return false;

    Grafo peaje(N);
    int v, w;
    for (int i = 0; i < C; i++)
    {
        cin >> v >> w;
        peaje.ponArista(v - 1, w - 1);
    }
    Solucion sol(peaje, casaAlex - 1, casaLucas - 1, trabajo - 1);

    int costoMinimo = sol.calcularCostoMinimo();

    cout << costoMinimo << endl;
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