/*@ <authors>
 *
 * Alejandro Vida Ram�rez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

#include "DigrafoValorado.h"
#include "IndexPQ.h"

/*@ <answer>

Enfoque de la Soluci�n:

La soluci�n implementa un enfoque voraz para asignar pueblos a las plantas de manera eficiente. Primero, calculamos las distancias m�nimas desde las plantas a todos los pueblos utilizando el algoritmo de Dijkstra. 
Luego, ordenamos los pueblos en funci�n de la distancia m�s corta entre las dos plantas.La asignaci�n de pueblos se realiza siguiendo un enfoque voraz. Seleccionamos los pueblos en orden ascendente seg�n la distancia m�s corta entre las plantas. 
Cada pueblo se asigna a la planta que ofrezca la distancia m�s corta. Mantenemos un equilibrio, asegur�ndonos de que cada planta suministre a la mitad de los pueblos ((N - 2)/ 2). Esta estrategia minimiza el coste total de transporte, ya que elegimos los pueblos m�s cercanos a cada planta en cada paso.
Adem�s, garantizamos que se cumplan las restricciones de suministro equitativo entre las dos plantas.

Supongamos que una solucion voraz V asigna los pueblos de manera voraz y O es una asignaci�n �ptima que minimiza el coste total. Definimos D como la diferencia de coste total entre las soluciones O y V (es decir, D = Coste (O) -  Coste(V))

Ahora, queremos demostrar que la diferencia D es igual a cero, es decir, que la soluci�n voraz es �ptima. La soluci�n voraz asigna cada pueblo a la planta que ofrece el menor coste, manteniendo un equilibrio en la asignaci�n. Si O tambi�n asigna pueblos manteniendo un equilibrio, entonces la diferencia en el n�mero de pueblos asignados por cada planta debe ser cero.
La soluci�n voraz ordena los pueblos seg�n la distancia m�s corta a alguna de las plantas y luego asigna pueblos en orden ascendente. Si O asigna pueblos de una manera que no sigue este orden, podr�a haber oportunidades de mejorar la asignaci�n y reducir el coste total por lo que O no seria optima.

Coste de la Soluci�n:

El coste de la soluci�n se desglosa de la siguiente manera:

1. Algoritmo de Dijkstra: El coste es del orden de O(A log V) donde A es el numero de aristas(carreteras) y V es el numero de vertices(pueblos + plantas)
2. Ordenamiento de pueblos: El ordenamiento de los pueblos tiene coste O(V log V) donde V es el n�mero de pueblos.
3. Iteraci�n sobre pueblos para asignar y calcular el coste: Iterar sobre los pueblos y calcular el coste es del orden de O(V)
4. Operaciones como las de IndexPQ que no influyen en el coste total ya que son mas peque�as que las mencionadas arriba.

En resumen, el coste del algoritmo ser� O(A log V) debido al algoritmo de dijkstra ya que adem�s en estos grafos O(A log V) es mas grande que O(V log V) suponiendo problemas de grafos densos.
Y en cuanto a espacio adicional O(V)


 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>



//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

using lli = long long int;

template <typename Valor>
class Dijkstra {
public:
    Dijkstra(const DigrafoValorado<Valor>& grafo, int origen) : dist(grafo.V(), numeric_limits<Valor>::max()), pq(grafo.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : grafo.ady(v))
                relajar(a);
        }
    }

    vector<lli> costes() const {
        return dist;
    }


private:
    vector<lli> dist;
    IndexPQ<Valor> pq;

    void relajar(const AristaDirigida<Valor>& a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }
};


vector<vector<lli>> calcularCostes(const DigrafoValorado<int>& grafo, int N) { // O(A log V)

    Dijkstra<int> dijkstraNorte(grafo, 0);
    vector<lli> costesDesdeNorte = dijkstraNorte.costes();

    Dijkstra<int> dijkstraSur(grafo, N - 1);
    vector<lli> costesDesdeSur = dijkstraSur.costes();

    return {costesDesdeNorte, costesDesdeSur };
}

struct Pueblo {
    lli costeNorte;
    lli costeSur;
    int indice;   
};

bool compararPueblos(const Pueblo& uno, const Pueblo& otro) {
    // Priorizar pueblos con costes diferentes
    if (uno.costeNorte != uno.costeSur && otro.costeNorte != otro.costeSur) {
        return min(uno.costeNorte, uno.costeSur) < min(otro.costeNorte, otro.costeSur);
    }
    if (uno.costeNorte == uno.costeSur && otro.costeNorte != otro.costeSur) {
        return false; // Poner pueblos con costes iguales al final
    }
    if (uno.costeNorte != uno.costeSur && otro.costeNorte == otro.costeSur) {
        return true; // Poner pueblos con costes iguales al final
    }
    // Si ambos tienen costes iguales, usar el índice para desempatar
    return uno.indice < otro.indice;
}

lli asignarPueblosYCalcularCoste(const vector<lli>& distNorte, const vector<lli>& distSur, int V) {
    int pueblosPorPlanta = (V - 2) / 2;
    vector<Pueblo> pueblosOrdenados;
    for (int i = 1; i < V - 1; ++i) {
        pueblosOrdenados.push_back({ distNorte[i], distSur[i], i });
    }

    sort(pueblosOrdenados.begin(), pueblosOrdenados.end(), compararPueblos);

    lli costeTotal = 0;
    int pueblosAsignadosNorte = 0;
    int pueblosAsignadosSur = 0;

    // Primero procesar pueblos con costes diferentes
    for (const auto& pueblo : pueblosOrdenados) {
        if (pueblo.costeNorte != pueblo.costeSur) {
            if (pueblosAsignadosNorte < pueblosPorPlanta && (pueblo.costeNorte < pueblo.costeSur || pueblosAsignadosSur == pueblosPorPlanta)) {
                costeTotal += pueblo.costeNorte;
                pueblosAsignadosNorte++;
            }
            else {
                costeTotal += pueblo.costeSur;
                pueblosAsignadosSur++;
            }
        }
    }

    // Luego asignar pueblos con costes iguales
    for (const auto& pueblo : pueblosOrdenados) {
        if (pueblo.costeNorte == pueblo.costeSur) {
            if (pueblosAsignadosNorte < pueblosPorPlanta) {
                costeTotal += pueblo.costeNorte;
                pueblosAsignadosNorte++;
            }
            else {
                costeTotal += pueblo.costeSur;
                pueblosAsignadosSur++;
            }
        }
    }

    return costeTotal * 2; // Multiplicar por 2 para incluir el viaje de vuelta
}

bool resuelveCaso() {
    int N, M;
    cin >> N >> M;
    if (!cin) return false;

    DigrafoValorado<int> grafo(N);
    for (int i = 0; i < M; ++i) {
        int v, w, valor;
        cin >> v >> w >> valor;
        grafo.ponArista({ v - 1, w - 1, valor });
        grafo.ponArista({ w - 1, v - 1, valor });
    }

    auto costes = calcularCostes(grafo, N);
    lli costeTotal = asignarPueblosYCalcularCoste(costes[0], costes[1], N);

    cout << costeTotal << endl;

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