/*@ <authors>
 *

Alejandro Vida Ramírez de Arellano TAIS71
Gabriel Torres Martín TAIS64


*@ </authors>
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.




 Empezamos definiendo una estructura Partido que tiene tres campos:

    votos: número de votos que recibió el partido.
    escaños: número de escaños asignados al partido.
    id: un identificador único para el partido (posicion de la entrada) que usamos para desempatar en caso de que dos partidos tengan el mismo coeficiente.
    También sobrecargamos el operador < para esta estructura, de manera que nos permita ordenar los partidos en una cola de prioridad según el coeficiente D'Hondt.

    Dentro de la estructura, definimos una función coeficiente() que calcula el coeficiente D'Hondt para el partido basado en la fórmula dada.

    Leemos el número C de candidaturas y el número N de escaños a repartir. Si ambos son 0, terminamos el programa. Luego, para cada candidatura, leemos el número de votos
    y los añadimos a una cola de prioridad.

    Procedemos a asignar escaños iterando N veces (el número total de escaños a repartir). En cada iteración, hacemos lo siguiente:

    Extraemos el partido con el mayor coeficiente de la cola de prioridad (esto es automático gracias a la sobrecarga del operador < en nuestra estructura).
    Le asignamos un escaño adicional al partido.
    Volvemos a insertar el partido en la cola de prioridad (ahora con un escaño más, por lo que su coeficiente habrá cambiado).

    Lo primero es insertar en la cola de prioridad, esto tiene un coste de O(C log C)
    Para cada escaño a repartir, se extrae el partido con mayor coeficiente y luego lo reinsertamos (cada operacion es O(log C)), como hacemos esto N veces el coste total es O(N log C).

    Si juntamos los 2 pasos, realmente el coste es O((N+C) log C)

 @ </answer>*/


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


struct Partido {
    int votos;
    int escanos;

    int id;  // para resolver el empate por índice

    // Calculamos el coeficiente D'Hondt
    double coeficiente() const {
        return (double)votos / (1 + escanos);
    }

    // Sobrecargamos el operador para la prioridad en la cola
    bool operator<(const Partido& otro) const {
        if (coeficiente() == otro.coeficiente()) {
            if (votos == otro.votos)
                return id > otro.id; // Menor índice tiene prioridad
            return votos < otro.votos; // Mayor votos tiene prioridad
        }
        return coeficiente() < otro.coeficiente(); // Mayor coeficiente tiene prioridad
    }
};

bool resuelveCaso() {
    int C, N;
    cin >> C >> N;

    if (C == 0 && N == 0)
        return false;

    priority_queue<Partido> cola;

    for (int i = 0; i < C; i++) {
        int votos;
        cin >> votos;
        cola.push({ votos, 0, i });
    }

    for (int i = 0; i < N; i++) {
        Partido p = cola.top(); cola.pop();  // Obtenemos el partido con mayor coeficiente
        p.escanos++;  // Le asignamos un escaño
        cola.push(p);  // Lo devolvemos a la cola con el escaño adicional
    }

    vector<int> escanos_vector(C, 0);
    while (!cola.empty()) {
        Partido p = cola.top(); cola.pop();
        escanos_vector[p.id] = p.escanos;
    }

    for (int i = 0; i < C; i++) {
        cout << escanos_vector[i] << " ";
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