#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include "Digrafo.h"

using namespace std;

class Solucion {
public:
    Solucion(Digrafo const& g) : visit(g.V(), false), dist(g.V(), -1), origen(0) {
        bfs(g);
    }

    int answer(int destino) {
        return dist[destino];
    }

private:
    vector<bool> visit;
    vector<int> dist;
    int origen;

    void bfs(Digrafo const& g) {
        queue<int> q;
        dist[origen] = 0;
        visit[origen] = true;
        q.push(origen);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v))
            {
                if (!visit[w]) {
                    dist[w] = dist[v] + 1; visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
};

bool resuelveCaso() {
    int N, K, S, E;
    cin >> N >> K >> S >> E;

    if (N == 0 && K == 0 && S == 0 && E == 0) {
        return false; // Fin de la entrada
    }

    Digrafo tablero(N * N);

    unordered_map<int, int> inicioSerpiente;

    // Registrar el inicio de serpientes
    for (int i = 0; i < E + S; i++) {
        int inicio, fin;
        cin >> inicio >> fin;
        inicioSerpiente[inicio] = fin;
        
    }

    // Agrega las aristas del tablero, teniendo en cuenta las serpientes y escaleras
    for (int i = 1; i <= N * N; i++) {
        for (int j = 1; j <= K && i + j <= N * N; j++) {
            int destino = i + j;
            if (destino <= N * N) {
                auto it = inicioSerpiente.find(destino);
                if (it != inicioSerpiente.end()) {
                    tablero.ponArista(i - 1, it->second - 1);
                }
                else {
                    tablero.ponArista(i - 1, destino - 1);
                }
            }
        }
    }

    Solucion sol(tablero);

   
    // Imprime la distancia mínima
    cout << sol.answer((N * N) - 1) << '\n';

    return true;
}

int main() {
    // Ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // Para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
