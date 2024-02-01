
/*@ <authors>
 *
 * Alejandro Vida Ram�rez de Arellano TAIS71
 * Gabriel Torres Mart�n TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;

#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"


/*@ <answer>

El algoritmo tiene un costo de O(A log A) ya que recorremos todas las aristas (A) y realizamos operaciones de extracci�n (pop) en una priority_queue,
lo cual a�ade un costo de O(log A) por cada extracci�n. En cuanto al espacio adicional, adem�s de O(A) para crear la cola de aristas,
ya que la priority_queue recibe un vector y construye un mont�culo a partir de �l, con un tiempo proporcional al n�mero de elementos, que en este caso son las aristas.

Utilizamos el algoritmo de Kruskal para recorrer el grafo valorado, en el cual los v�rtices representan las ciudades y las aristas representan las carreteras.
De esta manera, obtenemos el �rbol de Recubrimiento M�nimo (ARM) del grafo. Si el grafo no es conexo, podemos determinarlo f�cilmente observando el n�mero de conjuntos disjuntos (que corresponde al n�mero de �rboles).
Nuestro objetivo es encontrar la arista con el mayor valor en el ARM, ya que esto nos proporciona directamente la longitud m�xima (autonom�a m�nima) que un coche tendr�a que recorrer para poder viajar por todas las ciudades.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

class AutonomiaMinima {

public:

    AutonomiaMinima(GrafoValorado<int> const& g) : autonomiaMinima(0), contVisit(1) { // O(A log A) y espacio adicional O(A)
        PriorityQueue<Arista<int>> pq(g.aristas()); // Tenemos las aristas ordenadas de menor a mayor valor.
        ConjuntosDisjuntos cjtos(g.V());  // Utilizamos ConjuntosDisjuntos para mantener un seguimiento de las componentes conexas.

        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);

            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                contVisit++;
                if (contVisit == g.V()) {
                    autonomiaMinima = a.valor();// Si ya tenemos V - 1 aristas ya tenemos el ARM.
                    break;
                }
            }
        }
        numCompConexas = cjtos.num_cjtos();
    }

    int getAutonomiaMinima() const {
        return autonomiaMinima;
    }
  
    bool esConexo() {
        return numCompConexas == 1;
    }

private:
    int contVisit;
    int numCompConexas;
    int autonomiaMinima;
};

bool resuelveCaso() {

    // leer los datos de la entrada

    int N, M;
    cin >> N >> M;

    if (!std::cin)  // fin de la entrada
        return false;
    int x, y, c;
    GrafoValorado<int> g(N);
    for (int i = 0; i < M; i++)
    {
        cin >> x >> y >> c;
        g.ponArista({ x - 1,y - 1,c });

    }
    AutonomiaMinima arm(g);

    if (arm.esConexo()) {
        cout << arm.getAutonomiaMinima() << endl;
    }
    else {
        cout << "Imposible" << endl;
    }
    

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
