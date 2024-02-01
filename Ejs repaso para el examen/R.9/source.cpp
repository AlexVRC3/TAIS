
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
bool resuelveCaso() {

    int B;
    cin >> B;
    if (!std::cin)  // fin de la entrada
        return false;
    priority_queue<Bateria> baterias;
    
    int duracion;
    int id = 1;
    for (int i = 0; i < B ; i++)
    {
        cin >> duracion;
        baterias.push({ duracion,id, duracion});
        id++;
    }
    int R;
    cin >> R;
    vector<Bateria> recargas;
    for (int i = 0; i < R ; i++)
    {
        cin >> duracion;
        recargas.push_back({ duracion,id, -1 });
        id++;
    }
    int Z, T;
    cin >> Z >> T;
    int contRepuesto = 0;
    int tiempo = 0;
    while (!baterias.empty() && baterias.top().tiempo <= T) {
        Bateria b = baterias.top();
        baterias.pop(); // O(log B)
        tiempo = b.tiempo;
        b.capacidad -= Z;
        b.tiempo = b.tiempo + b.capacidad;
        if (b.capacidad > 0) { // En caso de que podamos recargar y la capacidad aun no se agote
            baterias.push(b); // O(log B)
        }
        else if (contRepuesto < R) { // Si se agota la capacidad y hay recargas disponibles recargamos
            recargas[contRepuesto].tiempo = tiempo + recargas[contRepuesto].tiempo;
            baterias.push(recargas[contRepuesto]); // O(log B)
            contRepuesto++;
        }
    }

    if (baterias.empty())
        cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";
    else if (baterias.size() < B)
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
