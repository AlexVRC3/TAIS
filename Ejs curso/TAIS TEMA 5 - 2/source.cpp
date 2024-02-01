#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
using namespace std;

#include "Digrafo.h" // propios o los de las estructuras de datos de clase

class OrdenTopologico {
public:
    OrdenTopologico(Digrafo const& g) : visit(g.V(), false), enExploracion(g.V(), false){
        tieneCiclo = false;
        for (int v = 0; v < g.V(); ++v) {
            if (!visit[v] && !tieneCiclo) {
                dfs(g, v);
            }
        }
    }

    deque<int> const& orden() const {
        return _orden;
    }

    bool hayCiclo() const {
        return tieneCiclo;
    }

private:
    vector<bool> visit;
    deque<int> _orden;
    vector<bool> enExploracion;
    bool tieneCiclo;

    void dfs(Digrafo const& g, int v) {
        visit[v] = true;
        enExploracion[v] = true;
        for (int w : g.ady(v)) {
            if (!visit[w]) {
                dfs(g, w);
            }
            else if (enExploracion[w]) {
                tieneCiclo = true;  // Se encontró un ciclo
                return;
            }
        }
        enExploracion[v] = false;
        _orden.push_front(v);
        
    }
};

bool resuelveCaso() {
    // leer los datos de la entrada
    int N, M;
    cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo dg(N);
    int v, w;

    for (int i = 0; i < M; i++) {
        cin >> v >> w;
        dg.ponArista(v - 1, w - 1);
    }

    OrdenTopologico ot(dg);

    if (ot.hayCiclo()) {
        cout << "Imposible" << endl;
    }
    else {
        auto ordenTop = ot.orden();
        auto it = ordenTop.begin();
        while (it != ordenTop.end()) {
            cout << *it + 1;
            ++it;
            if (it != ordenTop.end()) {
                cout << " ";
            }
        }
        cout << endl;
    }

    return true;
}

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
