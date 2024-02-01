
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;


/*@ <answer>

Utilizamos una cola de prioridad de maximos para almacenar las candidaturas las cuales tienen un numero de escaños, un numero de votos
un coeficiente calculado como dice en el enunciado y un timestamp utilizado para desempates. Para cada escaño sacamos de la cola la
candidatura con mayor coeficiente y le asignamos un escaño mas. Antes de introducir la candidatura otra vez a la cola, recalculamos el
coeficiente para poder mantener el orden deseado en la cola de prioridad. Para desglosar el coste podemos fijarnos en los diferentes bucles
del codigo. La lectura de las candidaturas tiene coste O(C log C) ya que también las añadimos a la cola de prioridad. El reparto de escaños
tiene coste O(N log C) debido a que repartimos N escaños y realizamos operaciones de pop y push sobre la cola. Por ultimo para rellenar el
vector auxiliar que nos permite imprimir el numero de escaños por candidatura en el orden en el que entraron necesitamos un vector auxiliar
O(C) y vaciar la cola de prioridad por tanto O(C log C). En resumen, el coste total del programa juntando todos estos será del orden de
O((N + C)log C).

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Candidatura {
    int esc;
    int votos;
    double coeficiente;
    int timestamp;
};

struct cand_comp {
    bool operator()(const Candidatura& c1, const Candidatura& c2) {
        if (c1.coeficiente == c2.coeficiente) {
            if (c1.votos == c2.votos)
                return c1.timestamp > c2.timestamp; // Doble empate, el que antes entra tiene prioridad
            return c2.votos > c1.votos; // Mayor numero de votos tiene prioridad
        }
        return c2.coeficiente > c1.coeficiente; // Mayor coeficiente tiene prioridad
    }
};


bool resuelveCaso() {
    int C, N;
    
    cin >> C >> N;
    if (C == 0 && N == 0)
        return false;
    priority_queue<Candidatura, vector<Candidatura>, cand_comp> pq;
    int nVotos;
    for (int i = 0; i < C; i++) // O(C log C)
    {
        cin >> nVotos;
        Candidatura c;
        c.votos = nVotos;
        c.esc = 0;
        c.timestamp = i;
        c.coeficiente = (double) c.votos / (1 + c.esc);
        pq.push(c); 
    }
    for (int i = 0; i < N; i++) // O(N log C)
    {
        Candidatura c = pq.top(); pq.pop(); 
        c.esc++;
        c.coeficiente = (double) c.votos / (1 + c.esc);
        pq.push(c); 
    }

    vector<int> candidaturas(C, 0);
    while (!pq.empty()) { // O(C log C)
        Candidatura c = pq.top(); pq.pop(); 
        candidaturas[c.timestamp] = c.esc;
    }

    for (int i = 0; i < C; i++) { // O(C)
        cout << candidaturas[i] << " ";
    }
    cout << "\n";

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
