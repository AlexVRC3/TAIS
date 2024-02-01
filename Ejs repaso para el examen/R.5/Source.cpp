
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

#include "Grafo.h"

/*@ <answer>

Utilizamos un dfs para recorrer todas las componentes conexas del grafo y para cada una de ellas calculamos el menor coste para comprar un rollo de papel higiénico. Utilizo un
vector componentesConexas de tamaño g.V() que tiene en cada posicion el representante de cada componente conexa para asi de esta manera con un solo dfs podemos tener toda la informacion
necesaria para contestar a las preguntas del enunciado. Esto es mas eficiente que realizar varios bfs ya que además no nos piden el camino mas corto hasta algun supermercado.
El coste de la solucion es del orden de O(V + A) siendo V el numero de vertices del grafo y A el numero de aristas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Solucion {
private:
    vector<bool> visit; 
    vector<int> supermercados;
    vector<int> precioComponente;
    vector<int> componentesConexas;
    int contComp;
    int min;
    void dfs(Grafo const& G, int v) {
        visit[v] = true;
        componentesConexas[v] = contComp;
        if (supermercados[v] != -1) {
            if (supermercados[v] < min)
                min = supermercados[v];
        }
            
        for (int w : G.ady(v)) {
            if (!visit[w]) {
                dfs(G, w);
            }
        }
    }
public:
    Solucion(Grafo const& g, const vector<int> &supermercados) : visit(g.V(), false), min(INT_MAX), supermercados(supermercados), componentesConexas(g.V()), contComp(0) {
        for (int i = 0; i < g.V(); i++)
        {
            if (!visit[i]) {
                dfs(g, i);
                precioComponente.push_back(min);
                contComp++;
                min = INT_MAX;
            }
        }
    }
    int getPrecioMin(int v) const {
        return precioComponente[componentesConexas[v]];
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
    int S;
    cin >> S;
    vector<int> supermercados(N, -1);
    int loc, precio;
    for (int i = 0; i < S; i++)
    {
        cin >> loc >> precio;
        supermercados[loc - 1] = precio;
    }

    Solucion sol(g, supermercados); // O(V + A) por dfs
    
    int K;
    cin >> K;
    for (int i = 0; i < K; i++)
    {
        cin >> loc;
        
        if (sol.getPrecioMin(loc - 1) != INT_MAX)
            cout << sol.getPrecioMin(loc - 1) << "\n";
        else
            cout << "MENUDO MARRON\n";
    }
    cout << "---\n";

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
