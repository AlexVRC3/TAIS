#include <iostream>
#include <fstream>
#include <vector>
#include "ConjuntosDisjuntos.h"

using namespace std;

bool resuelveCaso() {
    int F, C;
    if (!(cin >> F >> C))  // fin de la entrada
        return false;

    vector<string> grid(F);
    for (int i = 0; i < F; i++) {
        cin >> grid[i];
    }

    ConjuntosDisjuntos dsu(F * C);

    auto index = [&](int i, int j) {
        return i * C + j;
        };

    int maxMarea = 0;
    vector<int> tamanosMareas;

    for (int i = 0; i < F; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == '#') {
                maxMarea = max(maxMarea, 1);

                int dr[] = { 1, -1, 0, 0, 1, 1, -1, -1 };
                int dc[] = { 0, 0, 1, -1, 1, -1, 1, -1 };

                for (int k = 0; k < 8; k++) {
                    int ni = i + dr[k];
                    int nj = j + dc[k];

                    if (ni >= 0 && ni < F && nj >= 0 && nj < C && grid[ni][nj] == '#') {
                        int curr = dsu.buscar(index(i, j));
                        int neighbor = dsu.buscar(index(ni, nj));

                        if (curr != neighbor) {
                            dsu.unir(curr, neighbor);
                            maxMarea = max(maxMarea, dsu.cardinal(curr));
                        }
                    }
                }
            }
            tamanosMareas.push_back(maxMarea);
        }
    }

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int r, c;
        cin >> r >> c;
        r--;
        c--;

        if (grid[r][c] == '#') {
            tamanosMareas.push_back(maxMarea);
        }
        else {
            grid[r][c] = '#';

            int curr = index(r, c);
            maxMarea = max(maxMarea, 1);

            int dr[] = { 1, -1, 0, 0, 1, 1, -1, -1 };
            int dc[] = { 0, 0, 1, -1, 1, -1, 1, -1 };

            for (int k = 0; k < 8; k++) {
                int ni = r + dr[k];
                int nj = c + dc[k];

                if (ni >= 0 && ni < F && nj >= 0 && nj < C && grid[ni][nj] == '#') {
                    int neighbor = dsu.buscar(index(ni, nj));
                    dsu.unir(curr, neighbor);
                    maxMarea = max(maxMarea, dsu.cardinal(curr));
                }
            }
            tamanosMareas.push_back(maxMarea);
        }
    }

    for (int i = 0; i < tamanosMareas.size(); i++) {
        if (i > 0) cout << " ";
        cout << tamanosMareas[i];
    }
    cout << endl;

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
