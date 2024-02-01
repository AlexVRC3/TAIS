
/*@ <authors>
 *
 * Alejandro Vida Ramírez de Arellano TAIS71
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


/*@ <answer>

NOTACIONES
----------
N = numero de peliculas emitidas
Di = duracion en minutos de cada pelicula

RECURSION
---------

maxDuracion(i) = maximo tiempo en minutos que se puede pasar viendo pelis si estan disponibles las peliculas de la i a la N - 1.

maxDuracion(i) = max(maxDuracion(i+1), maxDuracion(j) + Di), donde j es la primera pelicula que no solapa con la i ( j = N si no existe tal pelicula)

EXPLICACION Y COSTE
-------------------

Se utiliza programación dinamica ascendente y de esta manera se va rellenando el vector de derecha a izquierda ya que para la posicion i necesitaremos la posicion i + 1 y la j que será siempre mayor que i.
La solucion quedará almacenada en la primera posición del vector. Para calcular la primera pelicula que no solapa con i se utiliza lower_bound que devuelve el primer indice en el cual si se introduce esa peli
no se pierde el orden o de otra manera, la primera pelicula que no solapa con i.

En cuanto al coste:
   - El coste en tiempo esta en el orden de O(N log N) debido al uso de quicksort aunque además hay que realizar una busqueda binaria O(log N) para cada posicion.
   - El coste en espacio esta en el orden de O(N), por el vector donde guardamos las soluciones de los subproblemas.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Pelicula {
    int ini;
    int fin;
    int duracion;
};

bool operator<(const Pelicula& p1, const Pelicula& p2) {
    return p1.ini < p2.ini;
}

int cine_romantico(vector<Pelicula>& peliculas) {
    int N = peliculas.size();
    sort(peliculas.begin(), peliculas.end()); // quicksort O(N log N)
    vector<int> v(N + 1, 0);
    for (int i = N - 1; i >= 0; i--)
    {
        int tiempoInicio = peliculas[i].fin + 10; 
        Pelicula p = { tiempoInicio, 0, 0 };
        auto it = lower_bound(peliculas.begin() + i, peliculas.end(), p); 
        int j = it - peliculas.begin(); 

        v[i] = max(v[i + 1], v[j] + peliculas[i].duracion);
    }
    return v[0];
}


bool resuelveCaso() {

    int N;
    cin >> N;
    if (N == 0)
        return false;
    vector<Pelicula> peliculas(N);
    int h, m, dur;
    char aux;
    for (int i = 0; i < N; i++)
    {
        cin >> h >> aux >> m >> dur;
        int ini = h * 60 + m;
        peliculas[i] = { ini,ini + dur, dur };
    }

    cout << cine_romantico(peliculas) << endl;
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
