
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


/*@ <answer>

Se utilizan dos colas de prioridad: en la de las actividades usamos una cola de prioridad de minimos en la cual ordenamos las actividades por orden de inicio y en la de compañeros guardamos
los momentos en los que nosotros o los compañeros quedan libres una vez han terminado la actividad. Por ello para cada actividad procesada si su inicio es antes de que haya alguien libre para
realizar la actividad se necesitara alguien para realizarla y añadiremos el tiempo de finalizacion de la actividad a la cola. Si no, se actualiza el momento en el que el compañero
quedará libre ya que debe realizar la nueva actividad. Es necesaria la segunda cola ya que si solo cogemos el minimo tiempo de dos a dos actividades podemos tener errores en la solucion. Con la cola
siempre tendremos la actividad que termina antes aunque haya mas de 2.

Al final se devuelve el tamaño de la cola de compañeros - 1 debido a que nos piden el numero sin tenernos en cuenta a nosotros. 
El coste de la solucion es del orden de O(A log A) donde A es el numero de actividades ya que el programa da A vueltas en el bucle de la lectura y para cada una de las vueltas realiza
push O(log A). En resolver el coste tambien da A vueltas y realiza operaciones de coste O(log A).

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Actividad {
    int ini;
    int fin;
};

bool operator<(const Actividad& a1, const Actividad& a2) { // Se ordenan por momento de inicio
    return a2.ini < a1.ini;
}

int resolver(priority_queue<Actividad>& pq) {
    priority_queue<int, vector<int>, greater<int>> companeros;
    while (!pq.empty()) {
        Actividad a = pq.top(); pq.pop(); // O(log A)
        if (companeros.empty() || companeros.top() > a.ini)
            companeros.push(a.fin);
        else {
            companeros.pop();
            companeros.push(a.fin);
        } 
    }
    return companeros.size() - 1;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    cin >> N;

    if (N == 0)  // fin de la entrada
        return false;

    priority_queue<Actividad> pq;
    int ini, fin;
    for (int i = 0; i < N; i++)
    {
        cin >> ini >> fin;
        pq.push({ ini,fin });
    }
    
    cout << resolver(pq) << endl;

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
