
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

Utilizo una cola de prioridad de maximos aunque implemento el operador < para que funcione como una cola de minimos y me ordene las baterias de manera que las que antes pueden agotarse esten en la cabeza
de la cola. Utilizo un vector para almacenar las baterias que nos servirán para recargar las baterias de la base. En el bucle vamos recorriendo la cola de pilas recargando las que se agotan porque
su tiempo es menor que el instante T que queremos comprobar y cuando el tiempo de duracion de una pila que esta en la primera en la cola ya es mayor que el instante T o cuando ya no tenemos pilas dejamos de
recorrer. En cuanto al coste el numero de vueltas del bucle en el caso peor podria acercarse a T y por lo tanto el coste del algoritmo seria del orden de O(T log B). La lectura de las baterias se realiza en
un bucle que da B vueltas y realiza operaciones de push sobre la cola de prioridad y por tanto es de coste O(B log B) que es menor que O(T log B) debido a que B < T.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


struct Bateria {
    int tiempo;
    int id;
    int capacidad;
};


bool operator<(const Bateria& b1, const Bateria& b2) {
    return b2.tiempo < b1.tiempo || (b1.tiempo == b2.tiempo && b2.id < b1.id);
}

int procesarBaterias(int B, priority_queue<Bateria>& baterias, vector<Bateria>& recargas, int Z, int T) {
    int contRepuesto = 0;
    int tiempo = 0;
    while (!baterias.empty() && baterias.top().tiempo <= T) {
        Bateria b = baterias.top();
        baterias.pop();
        tiempo = b.tiempo;
        b.capacidad -= Z;
        b.tiempo = b.tiempo + b.capacidad;
        if (b.capacidad > 0) {
            baterias.push(b);
        }
        else if (contRepuesto < recargas.size()) {
            recargas[contRepuesto].tiempo = tiempo + recargas[contRepuesto].tiempo;
            baterias.push(recargas[contRepuesto]);
            contRepuesto++;
        }
    }

    return baterias.size();
}

bool resuelveCaso() {
    int B, R, Z, T;
    cin >> B;
    if (!cin) return false;

    priority_queue<Bateria> baterias;
    vector<Bateria> recargas;
    Bateria temp;
    int id = 1;

    for (int i = 0; i < B; i++) {
        cin >> temp.tiempo;
        temp.id = id;
        id++;
        temp.capacidad = temp.tiempo;
        baterias.push(temp);
    }

    cin >> R;
    for (int i = 0; i < R; i++) {
        cin >> temp.tiempo;
        temp.id = id;
        id++;
        temp.capacidad = -1;
        recargas.push_back(temp);
    }

    cin >> Z >> T;

    int tam = procesarBaterias(B, baterias, recargas, Z, T);

    if (tam == 0)
        cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";
    else if (tam < B)
        cout << "FALLO EN EL SISTEMA\n";
    else
        cout << "CORRECTO\n";

    while (!baterias.empty()) {
        cout << baterias.top().id << " " << baterias.top().tiempo << "\n";
        baterias.pop();
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
