
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 * Gabriel Torres Martín TAIS64
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


/*@ <answer>

La estrategia voraz considera los trabajos en orden creciente según el momento en el que empiezan y escoge el que termine mas tarde entre los que permitan cubrir el intervalo[L,...) siendo L el ultimo punto
que se ha cubierto en un momento dado.

Sea V la solución voraz y O una solución optima cualquiera distinta de V. Entonces habrá un momento en el que las soluciones difieran. En primer lugar sabemos que el trabajo elegido por la
solucion voraz termina mas tarde que el de la solución optima, porque el algoritmo toma el que termine mas tarde de entre los que no dejan huecos.

Se propone escoger el trabajo de la solución voraz en lugar del que ha elegido la optima. Comprobamos que sigue siendo solución ya que no dejamos delante ningún hueco porque si no la solución
voraz no sería solucion y no dejamos ningun hueco detras porque estamos eligiendo un trabajo que termina mas tarde. Ademas siguie siendo optima porque el numero de trabajos es el mismo.

Este cambio puede ser repetido hasta igualar ambas soluciones y con ello hemos convertido una solucion optima cualquiera en nuestra solución voraz por lo que esta es optima.

El doble bucle tiene coste O(N) ya qué la instrucción i++ se ejecutará a lo sumo N veces puesto que pasamos una unica vez por cada elemento del vector y hacemos operaciones constantes sobre ellos.

Pero como antes de recorrer el vector utilizamos el metodo sort que utiliza un quicksort en el caso promedio tiene coste O(N log N) y ese es tambien el coste del programa.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Trabajo {
    int inicio;
    int fin;
};

bool operator<(const Trabajo& a, const Trabajo& b) {
    return a.inicio < b.inicio;
}

void resolver(const vector<Trabajo>& trabajos, int C , int F) { // O(N)
    int ultTrabajo = C, i = 0, nTrabajos = 0;
    bool haySol = true;

    while (haySol && ultTrabajo < F) { // mientras haya una solucion que cubra todo el intervalo
        int mejorFin = -1;
        if (i >= trabajos.size() || trabajos[i].inicio > ultTrabajo) // hay un hueco que no se puede cubrir
            haySol = false;
        while (haySol && i < trabajos.size() && trabajos[i].inicio <= ultTrabajo) {
            if (trabajos[i].fin > ultTrabajo && trabajos[i].fin > mejorFin) // Se elige el trabajo que termine mas tarde
                mejorFin = trabajos[i].fin;
            ++i;
        }
        if (mejorFin == -1) // ningun trabajo termina mas tarde
            haySol = false;
        ultTrabajo = mejorFin;
        ++nTrabajos;
    }
    if (haySol) {
        cout << nTrabajos << endl;
    }
    else
        cout << "Imposible\n";
}

bool resuelveCaso() {
    int C, F, N;

    cin >> C >> F >> N;
    // leer los datos de la entrada

    if (C == 0 && F == 0 && N == 0)  // fin de la entrada
        return false;


    vector<Trabajo> trabajos(N);

    for (int i = 0; i < N; ++i) {
        std::cin >> trabajos[i].inicio >> trabajos[i].fin;
    }

    sort(trabajos.begin(), trabajos.end());

    resolver(trabajos,C, F);
   


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
